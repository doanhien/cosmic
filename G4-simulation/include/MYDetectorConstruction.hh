#ifndef MYDetectorConstruction_h
#define MYDetectorConstruction_h

#include "G4VUserDetectorConstruction.hh"
#include "G4ThreeVector.hh"

#include <iostream>


class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class DetectorMessenger;

using namespace std;

class MYDetectorConstruction : public  G4VUserDetectorConstruction
{

 public:
  MYDetectorConstruction();
  virtual ~MYDetectorConstruction();

  virtual G4VPhysicalVolume* Construct();
  virtual void ConstructSDandField();
  virtual void CreateSDandField();


private:
  //! define needed materials
  void DefineMaterials();
  //! initialize geometry parameters
  void ComputeParameters();
  //! Construct geometry of the Tracker
  G4VPhysicalVolume* ConstructTracker();

  //! Construct geometry of the time of flight
  G4VPhysicalVolume* ConstructTOF();

  //! Construct geometry of the calorimeter
  G4VPhysicalVolume* ConstructCalorimeter();


 private:
  G4Material* air;
  G4Material* Si;
  G4Material* Vacuum;
  G4Material* Pb;
  G4Material *BBHodo_Scinti;

  //global mother volume
  G4LogicalVolume * logicWorld;

  //dummy logical volume to contain the silicon detector
  G4LogicalVolume* logictube;

  //tracker layer
  G4LogicalVolume* logicTracker;

  //module in each tracker layer
  G4LogicalVolume* logicModule;

  //strip in module
  G4LogicalVolume* logicStrip;

  G4VPhysicalVolume* physicTube;
  G4VPhysicalVolume* physicTOF_Upper1;
  G4VPhysicalVolume* physicCalo;

  //time of flight detector, 2 layers
  //above and below maget
  G4LogicalVolume* logicTOF1;
  G4LogicalVolume* logicTOF2;


  G4LogicalVolume* logicTOFSegment_Upper1;
  G4LogicalVolume* logicTOFSegment_Upper2;

 
  G4LogicalVolume* fMagneticLogical;
  G4LogicalVolume* BessLogical;


private:

  G4bool checkOverlaps;

  //parameter
  G4double halfWorldLength;

  //dummy tube for magnet
  G4double rmin_tube;
  G4double rmax_tube;
  G4double length_tube;
  G4double phimin_tube;
  G4double dphi_tube;

  //sensor of tracker
  G4int nLayer;
  vector<G4String> LayerLogName;
  vector<G4String> SensorLogName;
  vector<G4String> StripLogName;

  G4double noOfSensors;
  G4double LayerThickness;
  G4double LayerLength;
  G4double LayerWidth;

  G4double stripWidth;

  vector<G4double> ypos;


  //time of flight
  G4double TOF_width;
  G4double TOF_thickness;
  G4double TOF_length;

  G4int nTOFSegment_X;
  G4int nTOFSegment_Z;

  G4ThreeVector posFirstUpperTOF;
  G4ThreeVector posSecondUpperTOF;
  G4ThreeVector posFirstBelowTOF;
  G4ThreeVector posSecondBelowTOF;


  //calorimeter
  vector<G4String> CaloLogName;
  vector<G4String> CaloSegmentLogName;
  vector<G4String> CaloCellLogName;

  G4int nCalo;

  G4double Calo_width;
  G4double Calo_thickness;
  G4double Calo_length;

  G4int nSegment_calo;
  G4int nCell_calo;

  //absorber
  G4double ab_width;
  G4double ab_length;
  G4double ab_thickness;



};
#endif
