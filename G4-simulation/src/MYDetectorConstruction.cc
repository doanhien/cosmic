#include "MYDetectorConstruction.hh"
#include "MYTrackerSD.hh"
#include "MYScintTrigSD.hh"

#include "G4MaterialFactory.h"
#include "MaterialFactory.h"
#include "BessMagnet.h"
#include "P1DetectorParts.h"
#include "P1DetectorMagnet.h"
#include "PMagneticField.h"
#include "params_common.h"

#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VSolid.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVReplica.hh"

#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4FieldManager.hh"
#include "G4SDManager.hh"

#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"
#include "G4UIcommand.hh"


#include "G4AutoDelete.hh"

#include <cmath>
#include <iostream>  
#include <sstream>  

using namespace std;
using namespace P1Detector;


MYDetectorConstruction::MYDetectorConstruction()
  :G4VUserDetectorConstruction(),
   fMagneticLogical(0)
{

  // ------- material definition ---------
  DefineMaterials();

  //-------- size of the detector--------
  ComputeParameters();

  checkOverlaps = true;

  //G4cout << "done constructing class" << G4endl;

}

MYDetectorConstruction::~MYDetectorConstruction()
{
}


void MYDetectorConstruction::DefineMaterials() 
{

  //G4cout << "define material used later!!!!!!" << G4endl;
  G4NistManager* nistManager = G4NistManager::Instance();

  air = nistManager->FindOrBuildMaterial("G4_AIR");
  Si = nistManager->FindOrBuildMaterial("G4_Si");
  Pb = nistManager->FindOrBuildMaterial("G4_Pb");
  //Pb = nistManager->FindOrBuildMaterial("G4_AIR");
  Vacuum = nistManager->FindOrBuildMaterial("G4_Galactic");

  //plastic scintillator
  G4double fractionmass;
  G4NistManager *man = G4NistManager::Instance();
  G4Element *elH = man->FindOrBuildElement("H");
  G4Element *elC = man->FindOrBuildElement("C");

  G4double d_PolyVinylToluene = 0.57*g/cm3;
  G4double d_Anthracene = 1.28*g/cm3;
  G4double d_BBHodo_Scinti = 1.023*g/cm3;
  G4Material* PolyVinylToluene = new G4Material( "PolyVinylToluene", d_PolyVinylToluene, 2 );
  PolyVinylToluene->AddElement(elC, fractionmass = 0.91471);
  PolyVinylToluene->AddElement(elH, fractionmass = 0.08529);

  G4Material* Anthracene = new G4Material( "Anthracene", d_Anthracene, 2 );
  Anthracene->AddElement(elC, fractionmass = 0.943447);
  Anthracene->AddElement(elH, fractionmass = 0.056553);
  
  BBHodo_Scinti = new G4Material( "BBHodo_Scinti", d_BBHodo_Scinti,  2 );
  BBHodo_Scinti->AddMaterial(PolyVinylToluene, fractionmass = 0.36);
  BBHodo_Scinti->AddMaterial(Anthracene, fractionmass = 0.64);

}


void MYDetectorConstruction::ComputeParameters()
{

  //define size of detector

  //world volume
  halfWorldLength = 5.*m;

  // ------- tube contain BESS magnet ----------
  rmin_tube = 0.*cm;
  rmax_tube = 44.81*cm;
  length_tube = 70.*cm;
  phimin_tube = 0.;
  dphi_tube = 360.*deg;

  //size of tracker
  LayerThickness = 0.15*mm;
  LayerLength = 700.*mm;
  LayerWidth = 0.*mm; //define later in ConstructTracker();

  //strip
  stripWidth = 1.*mm;

  noOfSensors = 20;


  //-------- TOF -------------
  TOF_width  = 400.*mm;
  TOF_thickness  = 10.*mm;
  TOF_length = 700.*mm;

  nTOFSegment_X = 8;
  nTOFSegment_Z = 14;


  //sample calorimeter
  Calo_width             = 400.*mm;
  Calo_thickness         = 10.*mm;
  Calo_length            = 700.*mm;

  nSegment_calo = 8;
  nCell_calo = 4;

  //absorber

  ab_width      = 400.*mm;
  ab_length     = 700.*mm;
  ab_thickness  = 2.5*cm;

  //position of time of flight
  posFirstUpperTOF  = G4ThreeVector(0., 600.*mm, 0.);
  posSecondUpperTOF = G4ThreeVector(0., 570.*mm, 0.);
  posFirstBelowTOF  = G4ThreeVector(0., -570.*mm, 0.);
  posSecondBelowTOF = G4ThreeVector(0., -600.*mm, 0.);


  nLayer = 5;
  //string name
  for (G4int i = 0; i< nLayer; i++) {
    stringstream ss;
    ss << i;
    string index;
    ss >> index;

    G4String layername  = "logicLayer" + index;
    G4String sensorname = "logicSensor" + index;
    G4String stripname   = "logicStrip" + index;

    LayerLogName.push_back(layername);
    SensorLogName.push_back(sensorname);
    StripLogName.push_back(stripname);


    ypos.push_back((-150.*i) + 300.);
  }


  nCalo = 3;

  for (G4int i = 0; i< nCalo; i++) {
    stringstream ss;
    ss << i;
    string index;
    ss >> index;

    G4String caloname = "logicCalo" + index;
    G4String segmentname = "logicCaloStrip" + index;
    G4String cellname = "logicCaloCell" + index;

    CaloLogName.push_back(caloname);
    CaloSegmentLogName.push_back(segmentname);
    CaloCellLogName.push_back(cellname);
  }

  //name for time of flight

}



G4VPhysicalVolume* MYDetectorConstruction::Construct()
{

  //------------------------
  //world
  //------------------------

  G4GeometryManager::GetInstance()->SetWorldMaximumExtent(2.*halfWorldLength);
  G4cout << "Computed tolerance = "
	 << G4GeometryTolerance::GetInstance()->GetSurfaceTolerance()/m
	 << " m" << G4endl;

  
  G4VSolid *worldS = new G4Box("worldS", halfWorldLength, halfWorldLength, halfWorldLength);
  logicWorld = new G4LogicalVolume(worldS, air, "world");
  //logicWorld = new G4LogicalVolume(worldS, Vacuum, "world");
  G4VPhysicalVolume* physicWorld = new G4PVPlacement(0, G4ThreeVector(),  logicWorld, "world", 0, false, 0, checkOverlaps);
  

  //Bess Magnet
  G4MaterialFactory *G4MFactory = new G4MaterialFactory();
  MaterialFactory* mfactory = G4MFactory;
  mfactory->Initialize();
  
  Magnet *BSolenoid = new Magnet();
  BSolenoid->Initialize(logicWorld, mfactory);
  
  //construction of the tube containing BESS magnet
  //and silicon tracker inside

  ConstructTracker();

  //construct TOF
  ConstructTOF();

  //construct Calorimeter
  ConstructCalorimeter();


  return physicWorld;

}


G4VPhysicalVolume* MYDetectorConstruction::ConstructTracker()
{


  G4cout << "\n \n constructing TRACKER !!!!!!!!!! \n" << G4endl;
  //dummy logical volume to contain the silicon detector  
  G4VSolid *tubeS = new G4Tubs("tubeS", rmin_tube, rmax_tube, length_tube, phimin_tube, dphi_tube);

  logictube = new G4LogicalVolume(tubeS, air, "tubeLV");
  //logictube = new G4LogicalVolume(tubeS, Vacuum, "tubeLV");

  physicTube = new G4PVPlacement(0,  G4ThreeVector(), logictube, "logicVolume_tube", logicWorld, false, 0, checkOverlaps);
  fMagneticLogical = logictube;

  //add silicon inside the solenoid
  //with 5 layers at 300, 150, 0, -150, -300mm
  //each layer has sensor, each sensor contains strip

  for (G4int ilayer = 0; ilayer < nLayer; ilayer++) {
    //for (G4int ilayer = 0; ilayer < 1; ilayer++) {

    //layer
    G4double rmax = 44.75*cm;
    G4ThreeVector pos(0., ypos[ilayer], 0.);
    G4double xlength = sqrt(pow(rmax,2)-pow(ypos[ilayer],2)); //x direction
    LayerWidth = xlength;
    G4cout << "SiWidth = " << LayerWidth << G4endl;

    G4VSolid *solidTracker = new G4Box("solidTracker", LayerWidth, LayerThickness, LayerLength);
    logicTracker = new G4LogicalVolume(solidTracker, Si, LayerLogName[ilayer]);
    //new G4PVPlacement(0, pos,  logicTracker, "logicTracker", logictube, false, 0, checkOverlaps);
    new G4PVPlacement(0, pos,  logicTracker, "logicTracker", logictube, false, ilayer, checkOverlaps);


    //sensor in layer
    //G4double SensorWidth  = LayerWidth;
    //G4double SensorThickness  = LayerThickness;
    //G4double SensorLength = LayerLength/noOfSensors;

    G4double sensorDepth = 2*LayerLength/noOfSensors;

    G4cout << "layer and sensor thickness: " << LayerThickness << G4endl;

    G4VSolid *solidSensor = new G4Box("solidSensor",  LayerWidth, LayerThickness, LayerLength/noOfSensors);
    G4LogicalVolume* logicSensor = new G4LogicalVolume(solidSensor, Si, SensorLogName[ilayer]);
    new G4PVReplica("physicSensor", logicSensor, logicTracker, kZAxis, noOfSensors, sensorDepth);

    //strip in sensor
    //G4double stripThickness = LayerThickness;
    //G4double stripLength = SensorLength;

    G4int nStrip = LayerWidth/stripWidth;
    G4double stripDepth = 2*stripWidth;

    G4cout << "number of silicon strip: " << nStrip << G4endl;

    //G4VSolid *solidStrip = new G4Box("solidStrip", stripWidth, stripThickness, stripLength);
    G4VSolid *solidStrip = new G4Box("solidStrip", stripWidth, LayerThickness, LayerLength/noOfSensors);
    logicStrip = new G4LogicalVolume(solidStrip, Si, StripLogName[ilayer]);
    new G4PVReplica("physicStrip", logicStrip, logicSensor, kXAxis, nStrip, stripDepth);

    //sensor in strip

  }

  return physicTube;

}


G4VPhysicalVolume* MYDetectorConstruction::ConstructTOF()
{

  //---------------oOo------------//
  //add TOF detector using plastic scintillator, also for trigger
  //thickness = 2cm, length = 140 cm, width = 10cm
  //2 layers placed in perpendicular
  //---------------oOo------------//



  //---TOF above solenoid---/
  G4VSolid* solidTOF_Upper1 = new G4Box("solidTOF1_Upper1", TOF_width, TOF_thickness, TOF_length);
  //logicTOF1 = new G4LogicalVolume(solidTOF_Upper1, BBHodo_Scinti, "solidTOF_Upper1");
  logicTOF1 = new G4LogicalVolume(solidTOF_Upper1, air, "solidTOF_Upper1");


  physicTOF_Upper1 = new G4PVPlacement(0, 
				       posFirstUpperTOF,
				       logicTOF1, 
				       "physicTOF_Upper1", 
				       logicWorld, 
				       false, 
				       0, 
				       checkOverlaps);

  

  //-----------------------------//
  //2nd layer of upper TOF
  //segment in z-axis
  //----------------------------//

  G4VSolid* solidTOF_Upper2 = new G4Box("solidTOF1_Upper2", TOF_width, TOF_thickness, TOF_length);
  //logicTOF2 = new G4LogicalVolume(solidTOF_Upper2, BBHodo_Scinti, "solidTOF_Upper2");
  logicTOF2 = new G4LogicalVolume(solidTOF_Upper2, air, "solidTOF_Upper2");


  G4VPhysicalVolume* physicTOF_Upper2 = new G4PVPlacement(0, 
							  posSecondUpperTOF,
							  logicTOF2, 
							  "physicTOF_Upper2", 
							  logicWorld, 
							  false, 
							  0, 
							  checkOverlaps);



  //------------------------------------//
  //------TOF below magnet-------------//
  //------------------------------------//

  new G4PVPlacement(0, 
		    posFirstBelowTOF,
		    logicTOF1, 
		    "physicTOF_Below1", 
		    logicWorld, 
		    false, 
		    1, 
		    checkOverlaps);


  new G4PVPlacement(0, 
		    posSecondBelowTOF,
		    logicTOF2, 
		    "physicTOF_Below1", 
		    logicWorld, 
		    false, 
		    1, 
		    checkOverlaps);



  //-------------------------//
  //----- segment in TOF ----//

  //each side include nSegment = 8 counters
  G4VSolid* solidTOFSegment_Upper1 = new G4Box("solidTOFSegment_Upper1", TOF_width/nTOFSegment_X, TOF_thickness, TOF_length);

  //logicTOFSegment_Upper1 = new G4LogicalVolume(solidTOFSegment_Upper1, BBHodo_Scinti, "logicTOFSegment_Upper1");
  logicTOFSegment_Upper1 = new G4LogicalVolume(solidTOFSegment_Upper1, air, "logicTOFSegment_Upper1");

  G4double segment_Depth = 2*TOF_width/nTOFSegment_X;
  new G4PVReplica("physicTOFSegment_Upper1", logicTOFSegment_Upper1, physicTOF_Upper1, kXAxis, nTOFSegment_X, segment_Depth);

 
 //each side include nSegment = 14 counters
  G4VSolid* solidTOFSegment_Upper2 = new G4Box("solidTOFSegment_Upper2", TOF_width, TOF_thickness, TOF_length/nTOFSegment_Z);

  //logicTOFSegment_Upper2 = new G4LogicalVolume(solidTOFSegment_Upper2, BBHodo_Scinti, "logicTOFSegment_Upper2");
  logicTOFSegment_Upper2 = new G4LogicalVolume(solidTOFSegment_Upper2, air, "logicTOFSegment_Upper2");

  segment_Depth = 2*TOF_length/nTOFSegment_Z;
  new G4PVReplica("physicTOFSegment_Upper2", logicTOFSegment_Upper2, physicTOF_Upper2, kZAxis, nTOFSegment_Z, segment_Depth);


  return physicTOF_Upper1;
  
}
  


G4VPhysicalVolume* MYDetectorConstruction::ConstructCalorimeter() 
{


  //sample calorimeter below solenoid

  G4double ypos_scin = -800.*mm;

  G4ThreeVector posCalo1(0., -800.*mm, 0.);

  for (G4int icalo = 0; icalo < nCalo; icalo++) {

    //absorber
    G4VSolid* solidAbsorber = new G4Box("solidAbsorber", ab_width, ab_thickness, ab_length);
    G4LogicalVolume* logicAbsorber = new G4LogicalVolume(solidAbsorber, Pb, "logicAbsorber");
    G4double ypos_absorber = ypos_scin - 1.01*(Calo_thickness + ab_thickness);
    if (icalo == 0) ypos_absorber = ypos_scin;

    new G4PVPlacement(0, G4ThreeVector(0, ypos_absorber, 0), logicAbsorber, "physicAbsorber", logicWorld, false, 0, checkOverlaps);
    
    G4double segment_depth = 2*ab_width/nSegment_calo;
    
    G4VSolid* solidAbsorberSeg = new G4Box("solidAbsorberSeg", ab_width/nSegment_calo, ab_thickness, ab_length);
    G4LogicalVolume* logicAbsorberSeg = new G4LogicalVolume(solidAbsorberSeg, Pb, "AbsorberSeg");
    new G4PVReplica("AbsorberSeg", logicAbsorberSeg, logicAbsorber, kXAxis, nSegment_calo, segment_depth);
    
    G4double cell_depth = 2*ab_length/nCell_calo;
    G4VSolid* solidAbsorberCell = new G4Box("solidAbsorberCell",  ab_width/nSegment_calo, ab_thickness, ab_length/nCell_calo);
    G4LogicalVolume* logicAbsorberCell = new G4LogicalVolume(solidAbsorberCell, Pb, "AbsorberCell2");
    new G4PVReplica("AbsorberCell", logicAbsorberCell, logicAbsorberSeg, kZAxis, nCell_calo, cell_depth);

    //----------------------//
    //-----scintillator-----//
    //----------------------//

    ypos_scin = ypos_absorber - 1.01*(Calo_thickness + ab_thickness);
    G4VSolid* solidCalo = new G4Box("solidCalo", Calo_width, Calo_thickness, Calo_length);
    G4LogicalVolume* logicCalo = new G4LogicalVolume(solidCalo, BBHodo_Scinti, CaloLogName[icalo]);
    physicCalo = new G4PVPlacement(0, G4ThreeVector(0, ypos_scin, 0), logicCalo, "physicCalo", logicWorld, false, 0, checkOverlaps);

    segment_depth = 2*Calo_width/nSegment_calo;
    G4VSolid* solidCaloSegment = new G4Box("solidCaloSegment", Calo_width/nSegment_calo, Calo_thickness, Calo_length);
    G4LogicalVolume* logicCaloSegment = new G4LogicalVolume(solidCaloSegment, BBHodo_Scinti, CaloSegmentLogName[icalo]);
    new G4PVReplica("CaloSegment", logicCaloSegment, logicCalo, kXAxis, nSegment_calo, segment_depth);

    cell_depth = 2*Calo_length/nCell_calo;
    G4VSolid* solidCaloCell = new G4Box("solidCalidCell", Calo_width/nSegment_calo, Calo_thickness, Calo_length/nCell_calo);
    G4LogicalVolume* logicCaloCell = new G4LogicalVolume(solidCaloCell, BBHodo_Scinti, CaloCellLogName[icalo]);
    new G4PVReplica("CaloCell", logicCaloCell, logicCaloSegment, kZAxis, nCell_calo, cell_depth);

    //G4cout << "position of absorber: " << ypos_absorber << "\t of calo: " << ypos_scin << G4endl;
  }
  
 
  //G4cout << "finish construct detector" << G4endl;
 return physicCalo;


}


void MYDetectorConstruction::ConstructSDandField()
{
  

  //sensitive detector
  MYTrackerSD* tracker1SD
    = new MYTrackerSD("Tracker1SD", "TrackerLayer1HitsCollection");
  G4SDManager::GetSDMpointer()->AddNewDetector(tracker1SD);
  SetSensitiveDetector(StripLogName[0], tracker1SD);
  //logicStrip->SetSensitiveDetector(tracker1SD);
  
  MYTrackerSD* tracker2SD
  = new MYTrackerSD("Tracker2SD", "TrackerLayer2HitsCollection");
  G4SDManager::GetSDMpointer()->AddNewDetector(tracker2SD);
  SetSensitiveDetector(StripLogName[1], tracker2SD);
  
  MYTrackerSD* tracker3SD
    = new MYTrackerSD("Tracker3SD", "TrackerLayer3HitsCollection");
  G4SDManager::GetSDMpointer()->AddNewDetector(tracker3SD);
  SetSensitiveDetector(StripLogName[2], tracker3SD);

  MYTrackerSD* tracker4SD
    = new MYTrackerSD("Tracker4SD", "TrackerLayer4HitsCollection");
  G4SDManager::GetSDMpointer()->AddNewDetector(tracker4SD);
  SetSensitiveDetector(StripLogName[3], tracker4SD);

  MYTrackerSD* tracker5SD
    = new MYTrackerSD("Tracker5SD", "TrackerLayer5HitsCollection");
  G4SDManager::GetSDMpointer()->AddNewDetector(tracker5SD);
  SetSensitiveDetector(StripLogName[4], tracker5SD);
  

  //--------------------------------------//
  //sensitive detector for time of flight
  G4cout << "sensitive detector for TOF " << G4endl;

  MYScintTrigSD* TOFUpper1 = new MYScintTrigSD("TOFUpper1", "TOFCollectionUpper1");
  G4SDManager::GetSDMpointer()->AddNewDetector(TOFUpper1);
  //SetSensitiveDetector(TOFSegmentLogName[0], TOFUpper1);
  logicTOFSegment_Upper1->SetSensitiveDetector(TOFUpper1);

  MYScintTrigSD* TOFUpper2 = new MYScintTrigSD("TOFUpper2", "TOFCollectionUpper2");
  G4SDManager::GetSDMpointer()->AddNewDetector(TOFUpper2);
  //SetSensitiveDetector(TOFSegmentLogName[1], TOFUpper2);
  logicTOFSegment_Upper2->SetSensitiveDetector(TOFUpper2);

  /*
  MYScintTrigSD* TOFLower1 = new MYScintTrigSD("TOFLower1", "TOFCollectionLower1");
  G4SDManager::GetSDMpointer()->AddNewDetector(TOFLower1);
  SetSensitiveDetector(TOFSegmentLogName[2], TOFLower1);

  MYScintTrigSD* TOFLower2 = new MYScintTrigSD("TOFLower2", "TOFCollectionLower2");
  G4SDManager::GetSDMpointer()->AddNewDetector(TOFLower2);
  SetSensitiveDetector(TOFSegmentLogName[3], TOFLower2);
  */

  //--------------------------------------//
  //sensitive detector for calorimeter

  G4cout << "sensitive detector for Calorimeter " << G4endl;
  MYScintTrigSD* Calorimeter1 = new MYScintTrigSD("Calorimeter1", "Calorimeter1");
  G4SDManager::GetSDMpointer()->AddNewDetector(Calorimeter1);
  SetSensitiveDetector(CaloCellLogName[0], Calorimeter1);

  MYScintTrigSD* Calorimeter2 = new MYScintTrigSD("Calorimeter2", "Calorimeter2");
  G4SDManager::GetSDMpointer()->AddNewDetector(Calorimeter2);
  SetSensitiveDetector(CaloCellLogName[1], Calorimeter2);

  MYScintTrigSD* Calorimeter3 = new MYScintTrigSD("Calorimeter3", "Calorimeter3");
  G4SDManager::GetSDMpointer()->AddNewDetector(Calorimeter3);
  SetSensitiveDetector(CaloCellLogName[2], Calorimeter3);


  PMagneticField* magField = new PMagneticField();  
  G4FieldManager* fieldManager = new G4FieldManager();
  fieldManager->SetDetectorField(magField);
  fieldManager->CreateChordFinder(magField);

  G4bool forceToAllDaughters = true;
  fMagneticLogical->SetFieldManager(fieldManager, forceToAllDaughters);

  G4AutoDelete::Register(magField);
  G4AutoDelete::Register(fieldManager);


}


void MYDetectorConstruction::CreateSDandField()
{

}
