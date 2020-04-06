#include "RootSaver.hh"
#include "MYTrackerHit.hh"
#include "MYScintTrigHit.hh"

#include "TTree.h"
#include "TFile.h"
#include "TMath.h"

#include <sstream>
#include <iostream>
#include <cassert>

RootSaver::RootSaver() :
  rootTree(0),
  runCounter(0),
  EventID(-1)
{
}


RootSaver::~RootSaver()
{
  //Close current file if needed
  if ( rootTree )
    {
      CloseTree();
    }
}


void RootSaver::CreateTree( const std::string& fileName , const std::string& treeName )
{

  if ( rootTree )
    {
      std::cerr<<"TTree already created, first call CloseTree"<<std::endl;
      return;
    }

  std::ostringstream fn;
  fn << fileName << "_run" << runCounter++ << ".root";


  //TFile* rootFile = TFile::Open( fn.str().data() , "recreate" );
  G4cout << "filename: " << fn.str().data() << G4endl;
  TFile* rootFile = new TFile( fn.str().data() , "recreate" );
  if ( rootFile->IsOpen() ) G4cout<< "File opened successfully\n" << G4endl;
  if ( rootFile == 0 || rootFile->IsZombie() )
    {
      G4cerr<<"Error opening the file: "<<fn.str() <<" TTree will not be saved."<<G4endl;
      return;
    }
  rootTree = new TTree( treeName.data() , treeName.data() );


  rootTree->Branch("EventID",        &EventID);
  rootTree->Branch("Ene_par",        &Ene_par);
  rootTree->Branch("nHits_Layer1",   &nHits_Layer1);
  rootTree->Branch("nHits_Layer2",   &nHits_Layer2);
  rootTree->Branch("nHits_Layer3",   &nHits_Layer3);
  rootTree->Branch("nHits_Layer4",   &nHits_Layer4);
  rootTree->Branch("nHits_Layer5",   &nHits_Layer5);
  rootTree->Branch("Xpos_layer1",    &Xpos_layer1);
  rootTree->Branch("Ypos_layer1",    &Ypos_layer1);
  rootTree->Branch("Zpos_layer1",    &Zpos_layer1);
  rootTree->Branch("Px_layer1",      &Px_layer1);
  rootTree->Branch("Py_layer1",      &Py_layer1);
  rootTree->Branch("Pz_layer1",      &Pz_layer1);
  rootTree->Branch("Edep_layer1",    &Edep_layer1);
  rootTree->Branch("TrackID_layer1", &TrackID_layer1);
  rootTree->Branch("ParentID_layer1", &ParentID_layer1);
  rootTree->Branch("ParType_layer1", &ParType_layer1);
  rootTree->Branch("Sensor_layer1",  &Sensor_layer1);
  rootTree->Branch("Strip_layer1",   &Strip_layer1);
  //rootTree->Branch("TotEn_layer1",   &TotEn_layer1);

  rootTree->Branch("Xpos_layer2",    &Xpos_layer2);
  rootTree->Branch("Ypos_layer2",    &Ypos_layer2);
  rootTree->Branch("Zpos_layer2",    &Zpos_layer2);
  rootTree->Branch("Px_layer2",      &Px_layer2);
  rootTree->Branch("Py_layer2",      &Py_layer2);
  rootTree->Branch("Pz_layer2",      &Pz_layer2);
  rootTree->Branch("Edep_layer2",    &Edep_layer2);
  rootTree->Branch("TrackID_layer2", &TrackID_layer2);
  rootTree->Branch("ParentID_layer2", &ParentID_layer2);
  rootTree->Branch("ParType_layer2", &ParType_layer2);
  rootTree->Branch("Sensor_layer2",  &Sensor_layer2);
  rootTree->Branch("Strip_layer2",   &Strip_layer2);

  rootTree->Branch("Xpos_layer3",    &Xpos_layer3);
  rootTree->Branch("Ypos_layer3",    &Ypos_layer3);
  rootTree->Branch("Zpos_layer3",    &Zpos_layer3);
  rootTree->Branch("Px_layer3",      &Px_layer3);
  rootTree->Branch("Py_layer3",      &Py_layer3);
  rootTree->Branch("Pz_layer3",      &Pz_layer3);
  rootTree->Branch("Edep_layer3",    &Edep_layer3);
  rootTree->Branch("TrackID_layer3", &TrackID_layer3);
  rootTree->Branch("ParentID_layer3", &ParentID_layer3);
  rootTree->Branch("ParType_layer3", &ParType_layer3);
  rootTree->Branch("Sensor_layer3",  &Sensor_layer3);
  rootTree->Branch("Strip_layer3",   &Strip_layer3);


  rootTree->Branch("Xpos_layer4",    &Xpos_layer4);
  rootTree->Branch("Ypos_layer4",    &Ypos_layer4);
  rootTree->Branch("Zpos_layer4",    &Zpos_layer4);
  rootTree->Branch("Px_layer4",      &Px_layer4);
  rootTree->Branch("Py_layer4",      &Py_layer4);
  rootTree->Branch("Pz_layer4",      &Pz_layer4);
  rootTree->Branch("Edep_layer4",    &Edep_layer4);
  rootTree->Branch("TrackID_layer4", &TrackID_layer4);
  rootTree->Branch("ParentID_layer4", &ParentID_layer4);
  rootTree->Branch("ParType_layer4", &ParType_layer4);
  rootTree->Branch("Sensor_layer4",  &Sensor_layer4);
  rootTree->Branch("Strip_layer4",   &Strip_layer4);


  rootTree->Branch("Xpos_layer5",    &Xpos_layer5);
  rootTree->Branch("Ypos_layer5",    &Ypos_layer5);
  rootTree->Branch("Zpos_layer5",    &Zpos_layer5);
  rootTree->Branch("Px_layer5",      &Px_layer5);
  rootTree->Branch("Py_layer5",      &Py_layer5);
  rootTree->Branch("Pz_layer5",      &Pz_layer5);
  rootTree->Branch("Edep_layer5",    &Edep_layer5);
  rootTree->Branch("TrackID_layer5", &TrackID_layer5);
  rootTree->Branch("ParentID_layer5", &ParentID_layer5);
  rootTree->Branch("ParType_layer5", &ParType_layer5);
  rootTree->Branch("Sensor_layer5",  &Sensor_layer5);
  rootTree->Branch("Strip_layer5",   &Strip_layer5);


  rootTree->Branch("Edep_TOFUpper1", &Edep_TOFUpper1);
  rootTree->Branch("Edep_TOFUpper2", &Edep_TOFUpper2);
  rootTree->Branch("Edep_TOFBelow1", &Edep_TOFBelow1);
  rootTree->Branch("Edep_TOFBelow2", &Edep_TOFBelow2);

  rootTree->Branch("Edep_Calo1",     &Edep_Calo1);
  rootTree->Branch("Edep_Calo2",     &Edep_Calo2);
  rootTree->Branch("Edep_Calo3",     &Edep_Calo3);

  //energy in digit (number of charges)
  rootTree->Branch("Edep_digi_layer1",    &Edep_digi_layer1);
  rootTree->Branch("Edep_digi_layer2",    &Edep_digi_layer2);
  rootTree->Branch("Edep_digi_layer3",    &Edep_digi_layer3);
  rootTree->Branch("Edep_digi_layer4",    &Edep_digi_layer4);
  rootTree->Branch("Edep_digi_layer5",    &Edep_digi_layer5);

  rootTree->Branch("Edep_digi_TOFUpper1", &Edep_digi_TOFUpper1);
  rootTree->Branch("Edep_digi_TOFUpper2", &Edep_digi_TOFUpper2);
  rootTree->Branch("Edep_digi_TOFBelow1", &Edep_digi_TOFBelow1);
  rootTree->Branch("Edep_digi_TOFBelow2", &Edep_digi_TOFBelow2);

  rootTree->Branch("Edep_digi_Calo1",     &Edep_digi_Calo1);
  rootTree->Branch("Edep_digi_Calo2",     &Edep_digi_Calo2);
  rootTree->Branch("Edep_digi_Calo3",     &Edep_digi_Calo3);

  rootTree->Branch("Sensor_digi_layer1",  &Sensor_digi_layer1);
  rootTree->Branch("Sensor_digi_layer2",  &Sensor_digi_layer2);
  rootTree->Branch("Sensor_digi_layer3",  &Sensor_digi_layer3);
  rootTree->Branch("Sensor_digi_layer4",  &Sensor_digi_layer4);
  rootTree->Branch("Sensor_digi_layer5",  &Sensor_digi_layer5);

  rootTree->Branch("Strip_digi_layer1",  &Strip_digi_layer1);
  rootTree->Branch("Strip_digi_layer2",  &Strip_digi_layer2);
  rootTree->Branch("Strip_digi_layer3",  &Strip_digi_layer3);
  rootTree->Branch("Strip_digi_layer4",  &Strip_digi_layer4);
  rootTree->Branch("Strip_digi_layer5",  &Strip_digi_layer5);

  rootTree->Branch("GlbTime_layer1",     &GlbTime_layer1);
  rootTree->Branch("GlbTime_layer2",     &GlbTime_layer2);
  rootTree->Branch("GlbTime_layer3",     &GlbTime_layer3);
  rootTree->Branch("GlbTime_layer4",     &GlbTime_layer4);
  rootTree->Branch("GlbTime_layer5",     &GlbTime_layer5);


  G4cout << "done creating tree" << G4endl;

}

void RootSaver::CloseTree()
{

  //Check if ROOT TTree exists,
  //in case get the associated file and close it.

  if ( rootTree )
    {
      G4cout<<"Writing ROOT TTree: "<<rootTree->GetName()<<G4endl;
      TFile* currentFile = rootTree->GetCurrentFile();

      if ( currentFile == 0 || currentFile->IsZombie() )
	{
	  G4cerr<<"Error closing TFile "<<G4endl;
	  return;
	}

      //rootTree->Print();
      currentFile->cd();
      rootTree->Write();
      G4cout << "done writing tree" << G4endl;
      //TFile* currentFile = rootTree->GetCurrentFile();
      //G4cout << "checking outfile" << G4endl;
      currentFile->Write();
      currentFile->Close();

      rootTree = 0;
    }

}


void RootSaver::AddEvent(const G4int evID, const std::vector<MYTrackerHitsCollection*> TrackerHits,
                         const std::vector<MYScintTrigHitsCollection*> TOFHits, const std::vector<MYScintTrigHitsCollection*> CaloHits)

{


  //G4cout << "running addevent in rootsaver class" << G4endl;
  EventID = -1;

  nHits_Layer1 = 0;
  nHits_Layer2 = 0;
  nHits_Layer3 = 0;
  nHits_Layer4 = 0;
  nHits_Layer5 = 0;

  Xpos_layer1.clear();
  Ypos_layer1.clear();
  Zpos_layer1.clear();
  Edep_layer1 .clear();
  TrackID_layer1.clear();
  ParentID_layer1.clear();
  ParType_layer1.clear();
  Sensor_layer1.clear();
  Strip_layer1.clear();


  Xpos_layer2.clear();
  Ypos_layer2.clear();
  Zpos_layer2.clear();
  Edep_layer2 .clear();
  TrackID_layer2.clear();
  ParentID_layer2.clear();
  ParType_layer2.clear();
  Sensor_layer2.clear();
  Strip_layer2.clear();


  Xpos_layer3.clear();
  Ypos_layer3.clear();
  Zpos_layer3.clear();
  Edep_layer3 .clear();
  TrackID_layer3.clear();
  ParentID_layer3.clear();
  ParType_layer3.clear();
  Sensor_layer3.clear();
  Strip_layer3.clear();


  Xpos_layer4.clear();
  Ypos_layer4.clear();
  Zpos_layer4.clear();
  Edep_layer4 .clear();
  TrackID_layer4.clear();
  ParentID_layer4.clear();
  ParType_layer4.clear();
  Sensor_layer4.clear();
  Strip_layer4.clear();


  Xpos_layer5.clear();
  Ypos_layer5.clear();
  Zpos_layer5.clear();
  Edep_layer5 .clear();
  TrackID_layer5.clear();
  ParentID_layer5.clear();
  ParType_layer5.clear();
  Sensor_layer5.clear();
  Strip_layer5.clear();


  Edep_TOFUpper1 = 0.;
  Edep_TOFUpper2 = 0.;
  Edep_TOFBelow1 = 0.;
  Edep_TOFBelow2 = 0.;

  Edep_Calo1 = 0.;
  Edep_Calo2 = 0.;
  Edep_Calo3 = 0.;


  //if (rootTree) G4cout << "roottree name: " << rootTree->GetName() << G4endl;
  if ( rootTree == 0 )
    {
      return;
    }

  //G4cout << "after checking root tree available" << G4endl;
  if (evID < 0)
    {
      return;
    }
  else {
    EventID = evID;
  }

  //G4cout << "storing hits from tracker" << G4endl;
  //store hits from tracker to root tree
  if (TrackerHits.size() > 0) {

    G4int nLayer = TrackerHits.size();

    nHits_Layer1 = TrackerHits[0]->entries();
    nHits_Layer2 = TrackerHits[1]->entries();
    nHits_Layer3 = TrackerHits[2]->entries();
    nHits_Layer4 = TrackerHits[3]->entries();
    nHits_Layer5 = TrackerHits[4]->entries();

    for (G4int iLayer = 0; iLayer < nLayer; iLayer++) {
      G4int nHits = TrackerHits[iLayer]->entries();
      for (G4int i = 0; i < nHits; i++) {

	MYTrackerHit* hit = (*TrackerHits[iLayer])[i];

	G4ThreeVector localPos = hit->GetPosition();
	G4double edep = hit->GetEdep();

	//G4cout << "module: " << hit->GetModule() << "\t strip: " << hit->GetStrip() << G4endl;

	if (iLayer == 0) {

	  Xpos_layer1.push_back(localPos.x());
	  Ypos_layer1.push_back(localPos.y());
	  Zpos_layer1.push_back(localPos.z());
	  Edep_layer1.push_back(edep);
	  TrackID_layer1.push_back(hit->GetTrackID());
	  ParType_layer1.push_back(hit->GetParticleType());
	  Sensor_layer1.push_back(hit->GetModule());
	  Strip_layer1.push_back(hit->GetStrip());

	}

	else if (iLayer == 1) {
	  Xpos_layer2.push_back(localPos.x());
	  Ypos_layer2.push_back(localPos.y());
	  Zpos_layer2.push_back(localPos.z());
	  Edep_layer2.push_back(edep);
	  TrackID_layer2.push_back(hit->GetTrackID());
	  ParType_layer2.push_back(hit->GetParticleType());
	  Sensor_layer2.push_back(hit->GetModule());
	  Strip_layer2.push_back(hit->GetStrip());

	}

	else if (iLayer == 2) {
	  Xpos_layer3.push_back(localPos.x());
	  Ypos_layer3.push_back(localPos.y());
	  Zpos_layer3.push_back(localPos.z());
	  Edep_layer3.push_back(edep);
	  TrackID_layer3.push_back(hit->GetTrackID());
	  ParType_layer3.push_back(hit->GetParticleType());
	  Sensor_layer3.push_back(hit->GetModule());
	  Strip_layer3.push_back(hit->GetStrip());

	}

	else if (iLayer == 3) {
	  Xpos_layer4.push_back(localPos.x());
	  Ypos_layer4.push_back(localPos.y());
	  Zpos_layer4.push_back(localPos.z());
	  Edep_layer4.push_back(edep);
	  TrackID_layer4.push_back(hit->GetTrackID());
	  ParType_layer4.push_back(hit->GetParticleType());
	  Sensor_layer4.push_back(hit->GetModule());
	  Strip_layer4.push_back(hit->GetStrip());


	}

	else if (iLayer == 4) {
	  Xpos_layer5.push_back(localPos.x());
	  Ypos_layer5.push_back(localPos.y());
	  Zpos_layer5.push_back(localPos.z());
	  Edep_layer5.push_back(edep);
	  TrackID_layer5.push_back(hit->GetTrackID());
	  ParType_layer5.push_back(hit->GetParticleType());
	  Sensor_layer5.push_back(hit->GetModule());
	  Strip_layer5.push_back(hit->GetStrip());


	}

      }

    }

  } //done for tracker hit

  //G4cout << "storing hits from TOF" << G4endl;

  //store hits from TOF
  if (TOFHits.size() > 0 )
    {

      G4int nTOF = TOFHits.size();
      //G4cout << "TOF size: " << nTOF << G4endl;  
      for (G4int iTOF = 0; iTOF < nTOF; iTOF++) {

	//G4cout << "entries of TOFHits: " << (TOFHits[iTOF]->entries()) << G4endl;
	for (G4int i = 0; i < TOFHits[iTOF]->entries(); i++ ) {

	  MYScintTrigHit* hit = (*TOFHits[iTOF])[i];
	  G4int nLayer = hit->GetLayerNumber();
	  G4double eDep = hit->GetEdep();

	  if (iTOF == 0 ) {
	    if ( nLayer == 0 ) {
	      Edep_TOFUpper1 += eDep;
	    }
	    else if (nLayer == 1) {
	      Edep_TOFUpper2 += eDep;
            }
	  }

	  else if (iTOF == 1) {
	    if ( nLayer == 0 ) {
	      Edep_TOFBelow1 += eDep;
	    }
	    else if (nLayer == 1) {
	      Edep_TOFBelow2 += eDep;
            }
	  }

	}

      }

    } //done hits in TOF


  //G4cout << "storing hits from Calorimeter" << G4endl;

  //store hits in Calorimeter
  if (CaloHits.size() > 0 )
    {

      G4int nCalo = CaloHits.size();
      
      for (G4int iCalo = 0; iCalo < nCalo; iCalo++) {

	for (G4int i = 0; i < CaloHits[iCalo]->entries(); i ++ ) {

	  MYScintTrigHit* hit = (*CaloHits[iCalo])[i];
	  //G4int nLayer = hit->GetLayerNumber();
	  G4double eDep = hit->GetEdep();

	  if ( iCalo == 0 ) {
	    Edep_Calo1 += eDep;
	  }
	  else if (iCalo == 1) {
	    Edep_Calo2 += eDep;
	  }
	  else if (iCalo == 2) {
	    Edep_Calo3 += eDep;
	  }
	}
      }

    } //done hits in Calorimeter


  //G4cout << "filling ROOT TREE" << G4endl;
  //fill to the tree
  rootTree->Fill();

  //G4cout << "done filling ROOT TREE" << G4endl;



}



//store hits and digits
void RootSaver::AddEvent(const G4int evID, const G4double energy, const std::vector<MYTrackerHitsCollection*> TrackerHits,
                         const std::vector<MYScintTrigHitsCollection*> TOFHits, const std::vector<MYScintTrigHitsCollection*> CaloHits,
			 vector<const TrackerDigitCollection*> TrackerDigi,     vector<const ScintDigitCollection*> TOFDigi,
			 vector<const ScintDigitCollection*> CaloDigi )

{


  G4cout << "running addevent in rootsaver class" << G4endl;
  EventID = -1;
  Ene_par = 0.;

  nHits_Layer1 = 0;
  nHits_Layer2 = 0;
  nHits_Layer3 = 0;
  nHits_Layer4 = 0;
  nHits_Layer5 = 0;

  Xpos_layer1    .clear();
  Ypos_layer1    .clear();
  Zpos_layer1    .clear();
  Px_layer1      .clear();
  Py_layer1      .clear();
  Pz_layer1      .clear();
  Edep_layer1    .clear();
  TrackID_layer1 .clear();
  ParentID_layer1.clear();
  ParType_layer1 .clear();
  Sensor_layer1  .clear();
  Strip_layer1   .clear();
  //TotEn_layer1   .clear();


  Xpos_layer2    .clear();
  Ypos_layer2    .clear();
  Zpos_layer2    .clear();
  Px_layer2      .clear();
  Py_layer2      .clear();
  Pz_layer2      .clear();
  Edep_layer2    .clear();
  TrackID_layer2 .clear();
  ParentID_layer2.clear();
  ParType_layer2 .clear();
  Sensor_layer2  .clear();
  Strip_layer2   .clear();


  Xpos_layer3    .clear();
  Ypos_layer3    .clear();
  Zpos_layer3    .clear();
  Px_layer3      .clear();
  Py_layer3      .clear();
  Pz_layer3      .clear();
  Edep_layer3    .clear();
  TrackID_layer3 .clear();
  ParentID_layer3.clear();
  ParType_layer3 .clear();
  Sensor_layer3  .clear();
  Strip_layer3   .clear();


  Xpos_layer4    .clear();
  Ypos_layer4    .clear();
  Zpos_layer4    .clear();
  Px_layer4      .clear();
  Py_layer4      .clear();
  Pz_layer4      .clear();
  Edep_layer4    .clear();
  TrackID_layer4 .clear();
  ParentID_layer4.clear();
  ParType_layer4 .clear();
  Sensor_layer4  .clear();
  Strip_layer4   .clear();


  Xpos_layer5    .clear();
  Ypos_layer5    .clear();
  Zpos_layer5    .clear();
  Px_layer5      .clear();
  Py_layer5      .clear();
  Pz_layer5      .clear();
  Edep_layer5    .clear();
  TrackID_layer5 .clear();
  ParentID_layer5.clear();
  ParType_layer5 .clear();
  Sensor_layer5  .clear();
  Strip_layer5   .clear();


  Edep_digi_layer1.clear();
  Edep_digi_layer2.clear();
  Edep_digi_layer3.clear();
  Edep_digi_layer4.clear();
  Edep_digi_layer5.clear();

  Sensor_digi_layer1.clear();
  Sensor_digi_layer2.clear();
  Sensor_digi_layer3.clear();
  Sensor_digi_layer4.clear();
  Sensor_digi_layer5.clear();

  Strip_digi_layer1.clear();
  Strip_digi_layer2.clear();
  Strip_digi_layer3.clear();
  Strip_digi_layer4.clear();
  Strip_digi_layer5.clear();

  GlbTime_layer1.clear();
  GlbTime_layer2.clear();
  GlbTime_layer3.clear();
  GlbTime_layer4.clear();
  GlbTime_layer5.clear();


  Edep_digi_TOFUpper1 = 0.;
  Edep_digi_TOFUpper2 = 0.;
  Edep_digi_TOFBelow1 = 0.;
  Edep_digi_TOFBelow2 = 0.;

  Edep_digi_Calo1 = 0.;
  Edep_digi_Calo2 = 0.;
  Edep_digi_Calo3 = 0.;

  Edep_TOFUpper1 = 0.;
  Edep_TOFUpper2 = 0.;
  Edep_TOFBelow1 = 0.;
  Edep_TOFBelow2 = 0.;

  Edep_Calo1 = 0.;
  Edep_Calo2 = 0.;
  Edep_Calo3 = 0.;


  if (rootTree) G4cout << "roottree name: " << rootTree->GetName() << G4endl;
  if ( rootTree == 0 )
    {
      return;
    }

  G4cout << "after checking root tree available" << G4endl;
  if (evID < 0)
    {
      return;
    }
  else {
    EventID = evID;
  }

  Ene_par = energy;

  G4cout << "storing hits from tracker" << G4endl;
  //store hits from tracker to root tree
  if (TrackerHits.size() > 0) {

    G4int nLayer = TrackerHits.size();

    nHits_Layer1 = TrackerHits[0]->entries();
    nHits_Layer2 = TrackerHits[1]->entries();
    nHits_Layer3 = TrackerHits[2]->entries();
    nHits_Layer4 = TrackerHits[3]->entries();
    nHits_Layer5 = TrackerHits[4]->entries();

    for (G4int iLayer = 0; iLayer < nLayer; iLayer++) {
      G4int nHits = TrackerHits[iLayer]->entries();
      for (G4int i = 0; i < nHits; i++) {

	MYTrackerHit* hit = (*TrackerHits[iLayer])[i];

	G4ThreeVector localPos = hit->GetPosition();
	G4ThreeVector momentum = hit->GetMomentum();
	G4double edep = hit->GetEdep();

	//G4cout << "module: " << hit->GetModule() << "\t strip: " << hit->GetStrip() << G4endl;

	if (iLayer == 0) {

	  Xpos_layer1.push_back(localPos.x());
	  Ypos_layer1.push_back(localPos.y());
	  Zpos_layer1.push_back(localPos.z());
	  Edep_layer1.push_back(edep);
	  Px_layer1.push_back(momentum.x());
	  Py_layer1.push_back(momentum.y());
	  Pz_layer1.push_back(momentum.z());
	  TrackID_layer1.push_back(hit->GetTrackID());
	  ParentID_layer1.push_back(hit->GetMotherID());
	  ParType_layer1.push_back(hit->GetParticleType());
	  Sensor_layer1.push_back(hit->GetModule());
	  Strip_layer1.push_back(hit->GetStrip());
	  //TotEn_layer1.push_back(hit->

	}

	else if (iLayer == 1) {
	  Xpos_layer2.push_back(localPos.x());
	  Ypos_layer2.push_back(localPos.y());
	  Zpos_layer2.push_back(localPos.z());
	  Edep_layer2.push_back(edep);
	  Px_layer2.push_back(momentum.x());
	  Py_layer2.push_back(momentum.y());
	  Pz_layer2.push_back(momentum.z());
	  TrackID_layer2.push_back(hit->GetTrackID());
	  ParentID_layer2.push_back(hit->GetMotherID());
	  ParType_layer2.push_back(hit->GetParticleType());
	  Sensor_layer2.push_back(hit->GetModule());
	  Strip_layer2.push_back(hit->GetStrip());

	}

	else if (iLayer == 2) {
	  Xpos_layer3.push_back(localPos.x());
	  Ypos_layer3.push_back(localPos.y());
	  Zpos_layer3.push_back(localPos.z());
	  Edep_layer3.push_back(edep);
	  Px_layer3.push_back(momentum.x());
	  Py_layer3.push_back(momentum.y());
	  Pz_layer3.push_back(momentum.z());
	  TrackID_layer3.push_back(hit->GetTrackID());
	  ParentID_layer3.push_back(hit->GetMotherID());
	  ParType_layer3.push_back(hit->GetParticleType());
	  Sensor_layer3.push_back(hit->GetModule());
	  Strip_layer3.push_back(hit->GetStrip());

	}

	else if (iLayer == 3) {
	  Xpos_layer4.push_back(localPos.x());
	  Ypos_layer4.push_back(localPos.y());
	  Zpos_layer4.push_back(localPos.z());
	  Edep_layer4.push_back(edep);
	  Px_layer4.push_back(momentum.x());
	  Py_layer4.push_back(momentum.y());
	  Pz_layer4.push_back(momentum.z());
	  TrackID_layer4.push_back(hit->GetTrackID());
	  ParentID_layer4.push_back(hit->GetMotherID());
	  ParType_layer4.push_back(hit->GetParticleType());
	  Sensor_layer4.push_back(hit->GetModule());
	  Strip_layer4.push_back(hit->GetStrip());


	}

	else if (iLayer == 4) {
	  Xpos_layer5.push_back(localPos.x());
	  Ypos_layer5.push_back(localPos.y());
	  Zpos_layer5.push_back(localPos.z());
	  Edep_layer5.push_back(edep);
	  Px_layer5.push_back(momentum.x());
	  Py_layer5.push_back(momentum.y());
	  Pz_layer5.push_back(momentum.z());
	  TrackID_layer5.push_back(hit->GetTrackID());
	  ParentID_layer5.push_back(hit->GetMotherID());
	  ParType_layer5.push_back(hit->GetParticleType());
	  Sensor_layer5.push_back(hit->GetModule());
	  Strip_layer5.push_back(hit->GetStrip());


	}

      }

    }

  } //done for tracker hit

  //G4cout << "storing hits from TOF" << G4endl;

  //store hits from TOF
  if (TOFHits.size() > 0 )
    {

      G4int nTOF = TOFHits.size();
      //G4cout << "TOF size: " << nTOF << G4endl;  
      for (G4int iTOF = 0; iTOF < nTOF; iTOF++) {

	//G4cout << "entries of TOFHits: " << (TOFHits[iTOF]->entries()) << G4endl;
	for (G4int i = 0; i < TOFHits[iTOF]->entries(); i++ ) {

	  MYScintTrigHit* hit = (*TOFHits[iTOF])[i];
	  G4int nLayer = hit->GetLayerNumber();
	  G4double eDep = hit->GetEdep();

	  if (iTOF == 0 ) {
	    if ( nLayer == 0 ) {
	      Edep_TOFUpper1 += eDep;
	    }
	    else if (nLayer == 1) {
	      Edep_TOFUpper2 += eDep;
            }
	  }

	  else if (iTOF == 1) {
	    if ( nLayer == 0 ) {
	      Edep_TOFBelow1 += eDep;
	    }
	    else if (nLayer == 1) {
	      Edep_TOFBelow2 += eDep;
            }
	  }

	}

      }

    } //done hits in TOF


  //G4cout << "storing hits from Calorimeter" << G4endl;

  //store hits in Calorimeter
  if (CaloHits.size() > 0 )
    {

      G4int nCalo = CaloHits.size();
      
      for (G4int iCalo = 0; iCalo < nCalo; iCalo++) {

	for (G4int i = 0; i < CaloHits[iCalo]->entries(); i ++ ) {

	  MYScintTrigHit* hit = (*CaloHits[iCalo])[i];
	  G4int nLayer = hit->GetLayerNumber();
	  G4double eDep = hit->GetEdep();

	  if ( nLayer == 0 ) {
	    Edep_Calo1 += eDep;
	  }
	  else if (nLayer == 1) {
	    Edep_Calo2 += eDep;
	  }
	  else if (nLayer == 2) {
	    Edep_Calo3 += eDep;
	  }
	}
      }

    } //done hits in Calorimeter


  /************************************/
  //store information of digi
  /***********************************/

  G4cout << "staring store digit information" << G4endl;

  if (TrackerDigi.size()<=0 || TrackerDigi.size()>5 ) return;
  if (TrackerDigi.size()>0 ) {

    G4int nLayer = TrackerDigi.size();
    G4cout << "nLayer: " << nLayer << G4endl;
    nHits_Layer1 = TrackerDigi[0]->entries();
    nHits_Layer2 = TrackerDigi[1]->entries();
    nHits_Layer3 = TrackerDigi[2]->entries();
    nHits_Layer4 = TrackerDigi[3]->entries();
    nHits_Layer5 = TrackerDigi[4]->entries();

    if (nHits_Layer4 <=0 && nHits_Layer5 <=0 ) return;
    G4cout << "entries of hits: " << nHits_Layer1 << G4endl;

    for (G4int iLayer = 0; iLayer < nLayer; iLayer++) {
      G4int nDigits = TrackerDigi[iLayer]->entries();

      G4cout << "number of digits: " << nDigits << G4endl;
      for (G4int i = 0; i < nDigits; i++) {

	const TrackerDigit* Digi = static_cast<const TrackerDigit*>( (TrackerDigi[iLayer])->GetDigi( i ) );

	if (iLayer==0) {
	  Sensor_digi_layer1  .push_back(Digi->GetModuleNumber());
	  Strip_digi_layer1   .push_back(Digi->GetStripNumber());
	  Edep_digi_layer1    .push_back(Digi->GetCharge());
	  GlbTime_layer1      .push_back(Digi->GetGlobalTime());
	}

	else if (iLayer==1) {
	  Sensor_digi_layer2  .push_back(Digi->GetModuleNumber());
	  Strip_digi_layer2   .push_back(Digi->GetStripNumber());
	  Edep_digi_layer2    .push_back(Digi->GetCharge());
	  GlbTime_layer2      .push_back(Digi->GetGlobalTime());
	}

	else if (iLayer==2) {
	  Sensor_digi_layer3  .push_back(Digi->GetModuleNumber());
	  Strip_digi_layer3   .push_back(Digi->GetStripNumber());
	  Edep_digi_layer3    .push_back(Digi->GetCharge());
	  GlbTime_layer3      .push_back(Digi->GetGlobalTime());
	}

	else if (iLayer==3) {
	  Sensor_digi_layer4  .push_back(Digi->GetModuleNumber());
	  Strip_digi_layer4   .push_back(Digi->GetStripNumber());
	  Edep_digi_layer4    .push_back(Digi->GetCharge());
	  GlbTime_layer4      .push_back(Digi->GetGlobalTime());
	}

	else {
	  Sensor_digi_layer5  .push_back(Digi->GetModuleNumber());
	  Strip_digi_layer5   .push_back(Digi->GetStripNumber());
	  Edep_digi_layer5    .push_back(Digi->GetCharge());
	  GlbTime_layer5      .push_back(Digi->GetGlobalTime());
	}

      } //loop on number of hits

    }  //loop on layer

  }  //check if tracker digi is availabe


  //************************************//
  //G4cout << "digit of TOF" << G4endl;
  //***********************************//
  G4int nTOFDigi = TOFDigi.size();

  if (nTOFDigi > 1) {
    //G4cout << "size of iTOF: " << TOFDigi[0]->entries() << "\t " << TOFDigi[1]->entries() << G4endl;

    //sensor align in X-axis
    for (G4int i = 0; i < TOFDigi[0]->entries(); i++ ) {
      const ScintDigit* Digi = static_cast<const ScintDigit*>( TOFDigi[0]->GetDigi( i ));
      G4int iLayer = Digi->GetLayerNumber();
      Float_t eDep = Digi->GetCharge();

      if ( iLayer == 0 ) {
	Edep_digi_TOFUpper1 += eDep;
      }
      else {
	Edep_digi_TOFBelow1 += eDep;
      }
    }

    //sensor align in Z-axis
    for (G4int i = 0; i < TOFDigi[1]->entries(); i++ ) {

      const ScintDigit* Digi = static_cast<const ScintDigit*>( TOFDigi[1]->GetDigi( i ));
      G4int iLayer = Digi->GetLayerNumber();
      Float_t eDep = Digi->GetCharge();

      if ( iLayer == 0 ) {
	Edep_digi_TOFUpper2 += eDep;
      }
      else {
	Edep_digi_TOFBelow2 += eDep;
      }
    }
  }


  //******************************************//
  //G4cout << "digit of calorimeter" << G4endl;
  //digi in calorimeter
  //*****************************************//

  G4int nCaloDigi = CaloDigi.size();

  if (nCaloDigi > 0) {

    for (G4int iCalo = 0; iCalo < nCaloDigi; iCalo++) {

      for (G4int i = 0; i < CaloDigi[iCalo]->entries(); i++ ) {

	const ScintDigit* Digi = static_cast<const ScintDigit*>( (CaloDigi[iCalo])->GetDigi( i ) );

	Float_t eDep = Digi->GetCharge();

	  if (iCalo == 0 ) {
	    Edep_digi_Calo1 += eDep;
	    }
	    else if (iCalo == 1) {
	      Edep_digi_Calo2 += eDep;
            }
	  else {
	      Edep_digi_Calo3 += eDep;
	  }
      }
    }
  }



  //G4cout << "filling ROOT TREE" << G4endl;
  //fill to the tree
  rootTree->Fill();

  //G4cout << "done filling ROOT TREE" << G4endl;



}



