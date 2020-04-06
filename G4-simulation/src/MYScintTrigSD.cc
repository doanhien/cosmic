#include "MYScintTrigSD.hh"
#include "MYAnalysis.hh"

#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4VTouchable.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MYScintTrigSD::MYScintTrigSD(const G4String& name, 
			     const G4String& hitsCollectionName)
  //G4int ntupleId)
 : G4VSensitiveDetector(name),
   fHitsCollection(0)
   //fNtupleId(ntupleId)
{
  collectionName.insert(hitsCollectionName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MYScintTrigSD::~MYScintTrigSD()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MYScintTrigSD::Initialize(G4HCofThisEvent* hce)
{
  fHitsCollection 
    = new MYScintTrigHitsCollection(SensitiveDetectorName, collectionName[0]);

  // Add this collection in hce
  G4int hcID 
    = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection( hcID, fHitsCollection ); 

  /*
  for (G4int i=0; i<32; ++i) {
    MYScintTrigHit* newHit = new MYScintTrigHit();
    newHit->SetLayerNumber(i);
    fHitsCollection->insert(newHit);
  } 
  */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool MYScintTrigSD::ProcessHits(G4Step* step,
                                      G4TouchableHistory* /*history*/)
{
  // energy deposit
  G4double edep = step->GetTotalEnergyDeposit();
  if (edep==0.) return false;

  G4ParticleDefinition* particleType = step->GetTrack()->GetDefinition();
  G4String particleName = particleType->GetParticleName();
  /*
  G4double stepl = 0.;
  if (particleType->GetPDGCharge() != 0.)
    stepl = aStep->GetStepLength();

  if ((edep==0.)&&(stepl==0.)) return false;
  */

  const G4VTouchable* touchable = step->GetPreStepPoint()->GetTouchable();
  //G4VPhysicalVolume* layerPV = touchable->GetVolume();
  //G4int layerNumber = layerPV->GetCopyNo();
  G4int layerNumber = touchable->GetReplicaNumber(1);
  //G4int stripNumber = touchable->GetReplicaNumber(0);

  //G4cout << "TOF and Calorimeter infor, strip: " << touchable->GetReplicaNumber(0) << "\t sensor: " 
  //	 << touchable->GetReplicaNumber(1) << "\t layer: " << touchable->GetReplicaNumber(2) << G4endl;

  //G4cout << "name of physical volume: " << layerPV->GetName() << G4endl;
  //G4cout << "multiplicity of physical volume: " << layerPV->GetMultiplicity() << G4endl;


  //MYScintTrigHit* hit = (*fHitsCollection)[layerNumber];
  MYScintTrigHit *hit = new MYScintTrigHit();
  if ( ! hit ) {
    G4cerr << "Cannot access hit " << layerNumber << G4endl;
    exit(1);
  }         

  hit->SetLayerNumber(layerNumber);  
  hit->AddEdep(edep);

  fHitsCollection->insert(hit);

  //G4cout << "number of step: " << step->GetTrack()->GetCurrentStepNumber() << G4endl;
  //G4cout << "particle ID: " << particleName << G4endl;

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MYScintTrigSD::EndOfEvent(G4HCofThisEvent* /*hce*/)
{
  /*
  // Suppress heavy print:
  // G4cout << "\n-------->" <<  fHitsCollection->GetName() 
  //        << ": in this event: " << G4endl;

  //G4Event *event;
  //G4int eventID = event->GetID()
  G4cout << "hits collection in scintillator: " << G4endl;
  G4int nofHits = fHitsCollection->entries();
  for ( G4int i=0; i<nofHits; i++ ) (*fHitsCollection)[i]->Print();
  */  

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
