//save hits and energy in root file
//follow the procedure from 
//https://github.com/seladoor/Geant_simulations/blob/master/ESERCIZI/task2/task2a/include/RootSaver.hh


#ifndef ROOTSAVER_HH_
#define ROOTSAVER_HH_

#include <string>
#include <iostream>
#include <TTree.h>

#include "MYTrackerHit.hh"
#include "MYScintTrigHit.hh"
#include "ScintDigit.hh"
#include "TrackerDigit.hh"

using namespace std;

class TFile;

class RootSaver
{
public:

  RootSaver();

  virtual ~RootSaver();

  /*! \brief Open a TFile and create ROOT TTree.
   *
   * Each time that a /run/beamOn command is issued
   * this method should be called
   * Every time this method is called the run counter
   * is incremented and the file name is modified accordingly:
   * tree_run<n>.root
   * \sa CloseTree()
   * @param fileName : The ROOT file name prefix
   * @param treeName : The name of the TTree
   */


  virtual void CreateTree( const std::string& fileName = "fileout", const std::string& treeName = "ntuple" );

  virtual void CloseTree();

  //add hits to the tree

  virtual void AddEvent( const G4int evID, const vector<MYTrackerHitsCollection*> TrackerHits, 
			 const vector<MYScintTrigHitsCollection*> TOFHits, const vector<MYScintTrigHitsCollection*> CaloHits);

  virtual void AddEvent( const G4int evID, const G4double energy, const vector<MYTrackerHitsCollection*> TrackerHits, 
			 const vector<MYScintTrigHitsCollection*> TOFHits, const vector<MYScintTrigHitsCollection*> CaloHits,
			 vector<const TrackerDigitCollection*> TrackerDigi, vector<const ScintDigitCollection*> TOFDigi, 
			 vector<const ScintDigitCollection*> CaloDigi);


private:
  TTree* rootTree; 

  unsigned int runCounter;

  //position and energy of hits in tracker
  G4int EventID;
  G4double Ene_par;

  G4int nHits_Layer1;
  G4int nHits_Layer2;
  G4int nHits_Layer3;
  G4int nHits_Layer4;
  G4int nHits_Layer5;

  std::vector<G4double>  Xpos_layer1;
  std::vector<G4double>  Xpos_layer2;
  std::vector<G4double>  Xpos_layer3;
  std::vector<G4double>  Xpos_layer4;
  std::vector<G4double>  Xpos_layer5;

  std::vector<G4double>  Ypos_layer1;
  std::vector<G4double>  Ypos_layer2;
  std::vector<G4double>  Ypos_layer3;
  std::vector<G4double>  Ypos_layer4;
  std::vector<G4double>  Ypos_layer5;

  std::vector<G4double>  Zpos_layer1;
  std::vector<G4double>  Zpos_layer2;
  std::vector<G4double>  Zpos_layer3;
  std::vector<G4double>  Zpos_layer4;
  std::vector<G4double>  Zpos_layer5;

  std::vector<G4double>  Px_layer1;
  std::vector<G4double>  Px_layer2;
  std::vector<G4double>  Px_layer3;
  std::vector<G4double>  Px_layer4;
  std::vector<G4double>  Px_layer5;

  std::vector<G4double>  Py_layer1;
  std::vector<G4double>  Py_layer2;
  std::vector<G4double>  Py_layer3;
  std::vector<G4double>  Py_layer4;
  std::vector<G4double>  Py_layer5;

  std::vector<G4double>  Pz_layer1;
  std::vector<G4double>  Pz_layer2;
  std::vector<G4double>  Pz_layer3;
  std::vector<G4double>  Pz_layer4;
  std::vector<G4double>  Pz_layer5;

  std::vector<G4double>  Edep_layer1;
  std::vector<G4double>  Edep_layer2;
  std::vector<G4double>  Edep_layer3;
  std::vector<G4double>  Edep_layer4;
  std::vector<G4double>  Edep_layer5;

  std::vector<G4int>     TrackID_layer1;
  std::vector<G4int>     TrackID_layer2;
  std::vector<G4int>     TrackID_layer3;
  std::vector<G4int>     TrackID_layer4;
  std::vector<G4int>     TrackID_layer5;

  std::vector<G4int>     ParentID_layer1;
  std::vector<G4int>     ParentID_layer2;
  std::vector<G4int>     ParentID_layer3;
  std::vector<G4int>     ParentID_layer4;
  std::vector<G4int>     ParentID_layer5;

  std::vector<G4int>     ParType_layer1;
  std::vector<G4int>     ParType_layer2;
  std::vector<G4int>     ParType_layer3;
  std::vector<G4int>     ParType_layer4;
  std::vector<G4int>     ParType_layer5;

  std::vector<G4int>     Sensor_layer1;
  std::vector<G4int>     Sensor_layer2;
  std::vector<G4int>     Sensor_layer3;
  std::vector<G4int>     Sensor_layer4;
  std::vector<G4int>     Sensor_layer5;

  std::vector<G4int>     Strip_layer1;
  std::vector<G4int>     Strip_layer2;
  std::vector<G4int>     Strip_layer3;
  std::vector<G4int>     Strip_layer4;
  std::vector<G4int>     Strip_layer5;

  std::vector<G4double>     Edep_digi_layer1;
  std::vector<G4double>     Edep_digi_layer2;
  std::vector<G4double>     Edep_digi_layer3;
  std::vector<G4double>     Edep_digi_layer4;
  std::vector<G4double>     Edep_digi_layer5;

  std::vector<G4int>     Sensor_digi_layer1;
  std::vector<G4int>     Sensor_digi_layer2;
  std::vector<G4int>     Sensor_digi_layer3;
  std::vector<G4int>     Sensor_digi_layer4;
  std::vector<G4int>     Sensor_digi_layer5;

  std::vector<G4int>     Strip_digi_layer1;
  std::vector<G4int>     Strip_digi_layer2;
  std::vector<G4int>     Strip_digi_layer3;
  std::vector<G4int>     Strip_digi_layer4;
  std::vector<G4int>     Strip_digi_layer5;

  std::vector<G4double>     GlbTime_layer1;
  std::vector<G4double>     GlbTime_layer2;
  std::vector<G4double>     GlbTime_layer3;
  std::vector<G4double>     GlbTime_layer4;
  std::vector<G4double>     GlbTime_layer5;

  //std::vector<G4String>     ParName_layer1;
  //std::vector<G4String>     ParName_layer2;
  //std::vector<G4String>     ParName_layer3;
  //std::vector<G4String>     ParName_layer4;
  //std::vector<G4String>     ParName_layer5;

  G4double Edep_TOFUpper1;
  G4double Edep_TOFUpper2;
  G4double Edep_TOFBelow1;
  G4double Edep_TOFBelow2;

  G4double Edep_Calo1;
  G4double Edep_Calo2;
  G4double Edep_Calo3;

  Float_t Edep_digi_TOFUpper1;
  Float_t Edep_digi_TOFUpper2;
  Float_t Edep_digi_TOFBelow1;
  Float_t Edep_digi_TOFBelow2;

  Float_t Edep_digi_Calo1;
  Float_t Edep_digi_Calo2;
  Float_t Edep_digi_Calo3;




};

#endif



