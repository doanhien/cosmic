#include "MYTrackerSD.hh"
#include "MYAnalysis.hh"

#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4VTouchable.hh"
#include "G4Step.hh"
#include "G4ios.hh"
#include "G4Track.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MYTrackerSD::MYTrackerSD(const G4String& name, 
                         const G4String& hitsCollectionName)
  //G4int ntupleId)
 : G4VSensitiveDetector(name),
   fHitsCollection(0)
   //fNtupleId(ntupleId)
{
  collectionName.insert(hitsCollectionName);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MYTrackerSD::~MYTrackerSD()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MYTrackerSD::Initialize(G4HCofThisEvent* hce)
{

  //G4cout << "Initialize SD" << G4endl;
  fHitsCollection 
    = new MYTrackerHitsCollection(SensitiveDetectorName, collectionName[0]);

  // Add this collection in hce
  G4int hcID
    = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection(hcID, fHitsCollection); 


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool MYTrackerSD::ProcessHits(G4Step* step, 
                                G4TouchableHistory* /*history*/)
{

  G4double charge = step->GetTrack()->GetDefinition()->GetPDGCharge();
  if ( charge == 0. ) return false;
    
  const G4VTouchable* touchable = step->GetPreStepPoint()->GetTouchable();
  //G4TouchableHandle touchable = step->GetPreStepPoint()->GetTouchableHandle();

  // The primary is the track with ID 1 and with no parent
  //G4bool isPrimary = ( step->GetTrack()->GetTrackID() == 1 && step->GetTrack()->GetParentID() == 0 ) ? true : false;

  // Layer number
  // = copy number of mother volume
  G4VPhysicalVolume* motherPhysical = touchable->GetVolume(1); // mother
  G4int copyNo = motherPhysical->GetCopyNo();
  
  //get module and strip
  G4int nStrip  = touchable->GetReplicaNumber(0);
  G4int nModule = touchable->GetReplicaNumber(1);
  G4int nLayer  = touchable->GetReplicaNumber(2);

  //touchable->GetVolume(0)->GetCopyNo() = touchable->GetVolume(1)->GetReplicaNumber();
  //0: this level (this physical volume), 1: level up (mother of this physical volume

  //G4cout << "nstrip: " << nStrip << "\t module: " << nModule << "\t layer number: " << nLayer << "\t copyNo: " << copyNo << G4endl;
  //G4cout << "name of mother physical volume: " << motherPhysical->GetName() << G4endl;
  //G4cout << "GetMultiplicity of physical volume: " << motherPhysical->GetMultiplicity () << G4endl;

  // Create new hit
  MYTrackerHit* newHit = new MYTrackerHit(nLayer, nModule, nStrip);

  //newHit->SetLayerNumber(nLayer);

  G4StepPoint* preStepPoint = step->GetPreStepPoint();

  G4double time = preStepPoint->GetGlobalTime();
  newHit->SetGlobalTime(time);
 
  G4ThreeVector position = preStepPoint->GetPosition();
  newHit->SetPosition(position);

  G4double edep = step->GetTotalEnergyDeposit();
  if ( edep==0. ) return false;
  newHit->SetEdep(edep);
 
  // Add hit in the collection
  fHitsCollection->insert(newHit);

  G4Track* thistrack     = step->GetTrack();
  G4int    thistrackID   = thistrack->GetTrackID();
  G4String trackname     = thistrack->GetDefinition()->GetParticleName();
  G4int    parentID      = thistrack->GetParentID();
  G4int trackPDGencode   = thistrack->GetDefinition()->GetPDGEncoding();
  G4ThreeVector momentum = thistrack->GetMomentum ();
  //G4double globaltime    = thistrack->GetGlobalTime(); 

  newHit->SetTrackID(thistrackID);
  newHit->SetTrackName(trackname);
  newHit->SetMotherID(parentID);
  newHit->SetParticleType(trackPDGencode);
  newHit->SetMomentum(momentum);
  //newHit->SetGlobalTime(globaltime);


  return true;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MYTrackerSD::EndOfEvent(G4HCofThisEvent* /*hce*/)
{
  //G4cout << "\n-------->" <<  fHitsCollection->GetName() 
  //     << ": in this event: " << G4endl;
  
  //G4int nofHits = fHitsCollection->entries();
  //for ( G4int i=0; i<nofHits; i++ ) (*fHitsCollection)[i]->Print();

  //G4cout << "number of Hits in tracker: " << nofHits << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
