#include "MYEventAction.hh"

//#include "MYRunAction.hh"
#include "MYPrimaryGeneratorAction.hh"

#include "MYTrackerHit.hh"
#include "MYScintTrigHit.hh"
#include "MYAnalysis.hh"

#include "ScintDigit.hh"
#include "TrackerDigit.hh"

#include "ScintDigitizer.hh"
#include "TrackerDigitizer.hh"

#include "G4Event.hh"
#include "G4GenericMessenger.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "G4RunManager.hh"
#include "G4Threading.hh"

#include <fstream>
#include <iomanip>
#include <iostream>

#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "G4DigiManager.hh"


using namespace std;
class RootSaver;


MYEventAction::MYEventAction()
:G4UserEventAction(),
 rootSaver(0),
 fVerbose(true),
 runAct(0),genAction(0)
 
{

  //hit collection names
  TrackerHitsCollName1 = "TrackerLayer1HitsCollection";
  TrackerHitsCollName2 = "TrackerLayer2HitsCollection";
  TrackerHitsCollName3 = "TrackerLayer3HitsCollection";
  TrackerHitsCollName4 = "TrackerLayer4HitsCollection";
  TrackerHitsCollName5 = "TrackerLayer5HitsCollection";

  TOFHitsCollName1 = "TOFCollectionUpper1";
  TOFHitsCollName2 = "TOFCollectionUpper2";

  CaloHitsCollName1 = "Calorimeter1";
  CaloHitsCollName2 = "Calorimeter2";
  CaloHitsCollName3 = "Calorimeter3";

  //digit collection names
  TrackerDigiCollName1 = "TrackerDigiLayer1";
  TrackerDigiCollName2 = "TrackerDigiLayer2";
  TrackerDigiCollName3 = "TrackerDigiLayer3";
  TrackerDigiCollName4 = "TrackerDigiLayer4";
  TrackerDigiCollName5 = "TrackerDigiLayer5";

  TOFDigiCollName1 = "TOFDigi1";
  TOFDigiCollName2 = "TOFDigi2";

  CaloDigiCollName1 = "CaloDigi1";
  CaloDigiCollName2 = "CaloDigi2";
  CaloDigiCollName3 = "CaloDigi3";



  G4cout << "messenger of event action" << G4endl;

  //Generic messenger
  fMessenger = new G4GenericMessenger(this, "/BessMagnet/event/", "Primary generator control");
  fMessenger->DeclareProperty("setVerbose", fVerbose, "Activate/Inactivate verbose option");

  // hits collections
  TrackerCollID1 = -1;
  TrackerCollID2 = -1;
  TrackerCollID3 = -1;
  TrackerCollID4 = -1;
  TrackerCollID5 = -1;

  CalorimeterID1 = -1;
  CalorimeterID2 = -1;
  CalorimeterID3 = -1;

  UpperTOFxID = -1;
  UpperTOFzID = -1;
  LowerTOFxID = -1;
  LowerTOFzID = -1;


  event_id = -1;
  energy_pri = 0;


  TrackerDigitizer* TRKdigitizer_layer1 = new TrackerDigitizer("trackerDigitizer_layer1", TrackerHitsCollName1);
  TrackerDigitizer* TRKdigitizer_layer2 = new TrackerDigitizer("trackerDigitizer_layer2", TrackerHitsCollName2);
  TrackerDigitizer* TRKdigitizer_layer3 = new TrackerDigitizer("trackerDigitizer_layer3", TrackerHitsCollName3);
  TrackerDigitizer* TRKdigitizer_layer4 = new TrackerDigitizer("trackerDigitizer_layer4", TrackerHitsCollName4);
  TrackerDigitizer* TRKdigitizer_layer5 = new TrackerDigitizer("trackerDigitizer_layer5", TrackerHitsCollName5);

  ScintDigitizer* TOFdigitizer_layer1 = new ScintDigitizer("tofDigitizer_layer1", TOFHitsCollName1);
  ScintDigitizer* TOFdigitizer_layer2 = new ScintDigitizer("tofDigitizer_layer2", TOFHitsCollName2);

  ScintDigitizer* CALOdigitizer_layer1 = new ScintDigitizer("caloDigitizer_layer1", CaloHitsCollName1);
  ScintDigitizer* CALOdigitizer_layer2 = new ScintDigitizer("caloDigitizer_layer2", CaloHitsCollName2);
  ScintDigitizer* CALOdigitizer_layer3 = new ScintDigitizer("caloDigitizer_layer3", CaloHitsCollName3);


  G4DigiManager* digiManager = G4DigiManager::GetDMpointer();
  digiManager->AddNewModule(TRKdigitizer_layer1);
  digiManager->AddNewModule(TRKdigitizer_layer2);
  digiManager->AddNewModule(TRKdigitizer_layer3);
  digiManager->AddNewModule(TRKdigitizer_layer4);
  digiManager->AddNewModule(TRKdigitizer_layer5);

  digiManager->AddNewModule(TOFdigitizer_layer1);
  digiManager->AddNewModule(TOFdigitizer_layer2);

  digiManager->AddNewModule(CALOdigitizer_layer1);
  digiManager->AddNewModule(CALOdigitizer_layer2);
  digiManager->AddNewModule(CALOdigitizer_layer3);




}

MYEventAction::~MYEventAction()
{
}

void MYEventAction::BeginOfEventAction(const G4Event* event)
{

  //G4cout << "beginning of event" << G4endl;

  //thread-local run action

  //if (!runAct)
  //runAct = dynamic_cast<const MYRunAction*> (G4RunManager::GetRunManager()->GetUserRunAction());

  if (!genAction)
    genAction = dynamic_cast<const MYPrimaryGeneratorAction*> (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());

  //energy of primary
  energy_pri = genAction->GetEnergyPrimary();

  event_id = event->GetEventID();

  //G4cout << "begin event: " << event_id << G4endl;

  //get ID for silicon hits collection

  /*
  if (TrackerCollID1==-1 || UpperTOFxID==-1) {
    G4SDManager *SDman = G4SDManager::GetSDMpointer();

    UpperTOFxID = SDman->GetCollectionID("TOFCollectionUpper1");
    UpperTOFzID = SDman->GetCollectionID("TOFCollectionUpper2");
  
    TrackerCollID1 = SDman->GetCollectionID("TrackerLayer1HitsCollection");
    TrackerCollID2 = SDman->GetCollectionID("TrackerLayer2HitsCollection");
    TrackerCollID3 = SDman->GetCollectionID("TrackerLayer3HitsCollection");
    TrackerCollID4 = SDman->GetCollectionID("TrackerLayer4HitsCollection");
    TrackerCollID5 = SDman->GetCollectionID("TrackerLayer5HitsCollection");
  
    CalorimeterID1 = SDman->GetCollectionID("Calorimeter1");
    CalorimeterID2 = SDman->GetCollectionID("Calorimeter2");
    CalorimeterID3 = SDman->GetCollectionID("Calorimeter3");

  }
  */

  //get ID for tracker hits
  if (TrackerCollID1==-1 || TrackerCollID2==-1 || TrackerCollID3==-2 || TrackerCollID4==-1 || TrackerCollID5 ==-1) {

    G4SDManager *SDman = G4SDManager::GetSDMpointer();
    TrackerCollID1 = SDman->GetCollectionID(TrackerHitsCollName1);
    TrackerCollID2 = SDman->GetCollectionID(TrackerHitsCollName2);
    TrackerCollID3 = SDman->GetCollectionID(TrackerHitsCollName3);
    TrackerCollID4 = SDman->GetCollectionID(TrackerHitsCollName4);
    TrackerCollID5 = SDman->GetCollectionID(TrackerHitsCollName5);
  }


  //ID for TOF hits
  if (UpperTOFxID==-1 || UpperTOFzID==-1) {

    G4SDManager *SDman = G4SDManager::GetSDMpointer();
    UpperTOFxID = SDman->GetCollectionID(TOFHitsCollName1);
    UpperTOFzID = SDman->GetCollectionID(TOFHitsCollName2);
  }


  //ID for calorimeter hits
  if (CalorimeterID1==-1 || CalorimeterID2==-1 || CalorimeterID3==-1) {

    G4SDManager *SDman = G4SDManager::GetSDMpointer();
    CalorimeterID1 = SDman->GetCollectionID(CaloHitsCollName1);
    CalorimeterID2 = SDman->GetCollectionID(CaloHitsCollName2);
    CalorimeterID3 = SDman->GetCollectionID(CaloHitsCollName3);

  }

}

void MYEventAction::EndOfEventAction(const G4Event* event)
{

  G4HCofThisEvent* hce = event->GetHCofThisEvent();
  if (!hce)
    {
      G4ExceptionDescription msg;
      msg << "No hits collection of this event found." << G4endl;
      G4Exception("MYEventAction::EndOfEventAction()",
		  "BessCode", JustWarning, msg);
      return;
    }


  //check the hits in upper scintillator
  //or first 3 layers of silicon
  if ( (UpperTOFxID < 0) || (UpperTOFzID < 0) ) return;
  if ( (TrackerCollID1<0) || (TrackerCollID2<0) || (TrackerCollID3<0) || (TrackerCollID4<0) || (TrackerCollID5<0)) return;
  if ( (CalorimeterID1<0) || (CalorimeterID2<0) || (CalorimeterID3<0) ) return;
 
  
  //G4cout << "get tracker and calorimeter collection" << G4endl;
  //get tracker collection
  MYTrackerHitsCollection* TrackerHC1 
    = static_cast<MYTrackerHitsCollection*>(hce->GetHC(TrackerCollID1));
  MYTrackerHitsCollection* TrackerHC2 
    = static_cast<MYTrackerHitsCollection*>(hce->GetHC(TrackerCollID2));
  MYTrackerHitsCollection* TrackerHC3 
    = static_cast<MYTrackerHitsCollection*>(hce->GetHC(TrackerCollID3));
  MYTrackerHitsCollection* TrackerHC4 
    = static_cast<MYTrackerHitsCollection*>(hce->GetHC(TrackerCollID4));
  MYTrackerHitsCollection* TrackerHC5 
    = static_cast<MYTrackerHitsCollection*>(hce->GetHC(TrackerCollID5));

  //get TOF scintillartor collection
  MYScintTrigHitsCollection* UpperScintHCx
    = static_cast<MYScintTrigHitsCollection*>(hce->GetHC(UpperTOFxID));
  MYScintTrigHitsCollection* UpperScintHCz
    = static_cast<MYScintTrigHitsCollection*>(hce->GetHC(UpperTOFzID));


  //get calorimeter collection
  MYScintTrigHitsCollection* CalorimeterHC1 = static_cast <MYScintTrigHitsCollection*> (hce->GetHC(CalorimeterID1));
  MYScintTrigHitsCollection* CalorimeterHC2 = static_cast <MYScintTrigHitsCollection*> (hce->GetHC(CalorimeterID2));
  MYScintTrigHitsCollection* CalorimeterHC3 = static_cast <MYScintTrigHitsCollection*> (hce->GetHC(CalorimeterID3));

  //G4cout << "hits of calorimeter: " << CalorimeterHC1->entries() << G4endl;
  vector<MYTrackerHitsCollection*> TrackerHits;

  TrackerHits.push_back(TrackerHC1);
  TrackerHits.push_back(TrackerHC2);
  TrackerHits.push_back(TrackerHC3);
  TrackerHits.push_back(TrackerHC4);
  TrackerHits.push_back(TrackerHC5);
  
  
  vector<MYScintTrigHitsCollection*> TOFHits;

  TOFHits.push_back(UpperScintHCx);
  TOFHits.push_back(UpperScintHCz);


  vector<MYScintTrigHitsCollection*> CaloHits;
  CaloHits.push_back(CalorimeterHC1);
  CaloHits.push_back(CalorimeterHC2);
  CaloHits.push_back(CalorimeterHC3);

  //G4cout << "tracker collection ID: " << TrackerCollID1 << "\t " << TrackerCollID2 << "\t" << TrackerCollID3 << G4endl;  


  if ( (!TrackerHC1) || (!TrackerHC2) || (!TrackerHC3) || (!TrackerHC4) || (!TrackerHC5) 
       || (!UpperScintHCx) || (!UpperScintHCz) )
    {
      G4ExceptionDescription msg;
      msg << "Some of hits collections of this event not found." << G4endl;
      G4Exception("MYEventAction::EndOfEventAction()",
		  "BessMagnet", JustWarning, msg);
      return;
    }


  //**************************//
  //digitize
  G4DigiManager* digiManager = G4DigiManager::GetDMpointer();

  TrackerDigitizer* TRKdigiModule_layer1 = static_cast<TrackerDigitizer*> (digiManager->FindDigitizerModule("trackerDigitizer_layer1"));
  TrackerDigitizer* TRKdigiModule_layer2 = static_cast<TrackerDigitizer*> (digiManager->FindDigitizerModule("trackerDigitizer_layer2"));
  TrackerDigitizer* TRKdigiModule_layer3 = static_cast<TrackerDigitizer*> (digiManager->FindDigitizerModule("trackerDigitizer_layer3"));
  TrackerDigitizer* TRKdigiModule_layer4 = static_cast<TrackerDigitizer*> (digiManager->FindDigitizerModule("trackerDigitizer_layer4"));
  TrackerDigitizer* TRKdigiModule_layer5 = static_cast<TrackerDigitizer*> (digiManager->FindDigitizerModule("trackerDigitizer_layer5"));
  
  ScintDigitizer* TOFdigiModule_layer1  = static_cast<ScintDigitizer*> (digiManager->FindDigitizerModule("tofDigitizer_layer1"));
  ScintDigitizer* TOFdigiModule_layer2  = static_cast<ScintDigitizer*> (digiManager->FindDigitizerModule("tofDigitizer_layer2"));
  
  ScintDigitizer* CALOdigiModule_layer1 = static_cast<ScintDigitizer*> (digiManager->FindDigitizerModule("caloDigitizer_layer1"));
  ScintDigitizer* CALOdigiModule_layer2 = static_cast<ScintDigitizer*> (digiManager->FindDigitizerModule("caloDigitizer_layer2"));
  ScintDigitizer* CALOdigiModule_layer3 = static_cast<ScintDigitizer*> (digiManager->FindDigitizerModule("caloDigitizer_layer3"));

  if (TRKdigiModule_layer1) { TRKdigiModule_layer1->Digitize(); G4cout << "Digitization of tracker1" << G4endl;}
  if (TRKdigiModule_layer2) { TRKdigiModule_layer2->Digitize(); G4cout << "Digitization of tracker2" << G4endl;}
  if (TRKdigiModule_layer3) TRKdigiModule_layer3->Digitize();
  if (TRKdigiModule_layer4) TRKdigiModule_layer4->Digitize();
  if (TRKdigiModule_layer5) TRKdigiModule_layer5->Digitize();

  if (TOFdigiModule_layer1) TOFdigiModule_layer1->Digitize();
  if (TOFdigiModule_layer2) TOFdigiModule_layer2->Digitize();

  if (CALOdigiModule_layer1) CALOdigiModule_layer1->Digitize();
  if (CALOdigiModule_layer2) CALOdigiModule_layer2->Digitize();
  if (CALOdigiModule_layer3) CALOdigiModule_layer3->Digitize();


  if (rootSaver) {
    G4cout << "running rootsaver" << G4endl;
    //rootSaver->AddEvent(event_id, TrackerHits, TOFHits, CaloHits);

    G4int TRKdigiCollID_layer1 = digiManager->GetDigiCollectionID("trackerDigitizer_layer1" );
    G4int TRKdigiCollID_layer2 = digiManager->GetDigiCollectionID("trackerDigitizer_layer2" );
    G4int TRKdigiCollID_layer3 = digiManager->GetDigiCollectionID("trackerDigitizer_layer3" );
    G4int TRKdigiCollID_layer4 = digiManager->GetDigiCollectionID("trackerDigitizer_layer4" );
    G4int TRKdigiCollID_layer5 = digiManager->GetDigiCollectionID("trackerDigitizer_layer5" );

    G4int TOFdigiCollID_X = digiManager->GetDigiCollectionID( "tofDigitizer_layer1" );
    G4int TOFdigiCollID_Z = digiManager->GetDigiCollectionID("tofDigitizer_layer2");

    G4int CALOdigiCollID_layer1 = digiManager->GetDigiCollectionID( "caloDigitizer_layer1" );
    G4int CALOdigiCollID_layer2 = digiManager->GetDigiCollectionID( "caloDigitizer_layer2" );
    G4int CALOdigiCollID_layer3 = digiManager->GetDigiCollectionID( "caloDigitizer_layer3" );

    if (TRKdigiCollID_layer1 < 0) return;
    //G4cout << "ID of TOF in Z: " << TOFdigiCollID_Z << G4endl;

    const TrackerDigitCollection* TrackerDC1 = static_cast<const TrackerDigitCollection*> ( digiManager->GetDigiCollection(TRKdigiCollID_layer1) );
    const TrackerDigitCollection* TrackerDC2 = static_cast<const TrackerDigitCollection*> ( digiManager->GetDigiCollection(TRKdigiCollID_layer2) );
    const TrackerDigitCollection* TrackerDC3 = static_cast<const TrackerDigitCollection*> ( digiManager->GetDigiCollection(TRKdigiCollID_layer3) );
    const TrackerDigitCollection* TrackerDC4 = static_cast<const TrackerDigitCollection*> ( digiManager->GetDigiCollection(TRKdigiCollID_layer4) );
    const TrackerDigitCollection* TrackerDC5 = static_cast<const TrackerDigitCollection*> ( digiManager->GetDigiCollection(TRKdigiCollID_layer5) );

    const ScintDigitCollection* TOFDC1 = static_cast<const ScintDigitCollection*> ( digiManager->GetDigiCollection(TOFdigiCollID_X) );
    const ScintDigitCollection* TOFDC2 = static_cast<const ScintDigitCollection*> ( digiManager->GetDigiCollection(TOFdigiCollID_Z) );

    const ScintDigitCollection* CaloDC1 = static_cast<const ScintDigitCollection*> ( digiManager->GetDigiCollection(CALOdigiCollID_layer1) );
    const ScintDigitCollection* CaloDC2 = static_cast<const ScintDigitCollection*> ( digiManager->GetDigiCollection(CALOdigiCollID_layer2) );
    const ScintDigitCollection* CaloDC3 = static_cast<const ScintDigitCollection*> ( digiManager->GetDigiCollection(CALOdigiCollID_layer3) );

    //G4cout << "ID of digit: " << TRKdigiCollID_layer1 << "\t " << TRKdigiCollID_layer2 << "\t " << TOFdigiCollID_X << "\t" << TOFdigiCollID_Z << G4endl;
    //G4cout << "checking before running rootsaver, entries of tracker digi: " << TOFDC2->entries() << G4endl;


    std::vector<const TrackerDigitCollection*> TrackerDigi;
    TrackerDigi.push_back(TrackerDC1);
    TrackerDigi.push_back(TrackerDC2);
    TrackerDigi.push_back(TrackerDC3);
    TrackerDigi.push_back(TrackerDC4);
    TrackerDigi.push_back(TrackerDC5);

    std::vector<const ScintDigitCollection*> TOFDigi;
    TOFDigi.push_back(TOFDC1);
    TOFDigi.push_back(TOFDC2);

    std::vector<const ScintDigitCollection*> CaloDigi;
    CaloDigi.push_back(CaloDC1);
    CaloDigi.push_back(CaloDC2);
    CaloDigi.push_back(CaloDC3);

    rootSaver->AddEvent(event_id, energy_pri, TrackerHits, TOFHits, CaloHits, TrackerDigi, TOFDigi, CaloDigi);



  }



  G4cout << "End of Events" << G4endl;


}
