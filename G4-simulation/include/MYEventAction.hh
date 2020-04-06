#ifndef MYEventAction_h
#define MYEventAction_h

#include "G4UserEventAction.hh"
#include "globals.hh"

#include "MYTrackerHit.hh"
#include "MYScintTrigHit.hh"

#include "ScintDigit.hh"
#include "TrackerDigit.hh"
#include "ScintDigitizer.hh"
#include "TrackerDigitizer.hh"

#include "RootSaver.hh"

class MYRunAction;
class MYPrimaryGeneratorAction;
//class MYEventActionMessenger;
class MYAnalysis;
class G4GenericMessenger;

class MYEventAction : public G4UserEventAction
{

 public:
  MYEventAction();
  virtual ~MYEventAction();

  virtual void BeginOfEventAction(const G4Event* event);
  virtual void EndOfEventAction(const G4Event* event);
  inline void SetRootSaver( RootSaver* saver ) { rootSaver = saver; }

 private:

  RootSaver* rootSaver;
  G4GenericMessenger*  fMessenger;
  G4bool fVerbose;

  G4int event_id;
  G4double energy_pri;
  //G4int UpperScintCollID;
  //G4int LowerScintCollID;
  G4int TrackerCollID1;
  G4int TrackerCollID2;
  G4int TrackerCollID3;
  G4int TrackerCollID4;
  G4int TrackerCollID5;
  G4int CalorimeterID1;
  G4int CalorimeterID2;
  G4int CalorimeterID3;
  G4int UpperTOFxID;
  G4int UpperTOFzID;
  G4int LowerTOFxID;
  G4int LowerTOFzID;


  const MYRunAction*    runAct; //pointer to run action
  const MYPrimaryGeneratorAction* genAction; // pointer to particle generator

  //for hits collection name
  G4String TrackerHitsCollName1;
  G4String TrackerHitsCollName2;
  G4String TrackerHitsCollName3;
  G4String TrackerHitsCollName4;
  G4String TrackerHitsCollName5;

  G4String TOFHitsCollName1;
  G4String TOFHitsCollName2;

  G4String CaloHitsCollName1;
  G4String CaloHitsCollName2;
  G4String CaloHitsCollName3;

  //digit collection name
  G4String TrackerDigiCollName1;
  G4String TrackerDigiCollName2;
  G4String TrackerDigiCollName3;
  G4String TrackerDigiCollName4;
  G4String TrackerDigiCollName5;

  G4String TOFDigiCollName1;
  G4String TOFDigiCollName2;

  G4String CaloDigiCollName1;
  G4String CaloDigiCollName2;
  G4String CaloDigiCollName3;

  /*
  //hit collection ID
  G4String TrackerHitsCollID1;
  G4String TrackerHitsCollID2;
  G4String TrackerHitsCollID3;
  G4String TrackerHitsCollID4;
  G4String TrackerHitsCollID5;

  G4String TOFHitsCollID1;
  G4String TOFHitsCollID2;

  G4String CaloHitsCollID1;
  G4String CaloHitsCollID2;
  G4String CaloHitsCollID3;
  */




};
#endif
