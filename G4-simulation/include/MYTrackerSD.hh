#ifndef MYTrackerSD_h
#define MYTrackerSD_h 1

#include "G4VSensitiveDetector.hh"
#include "MYTrackerHit.hh"


class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class MYTrackerSD : public G4VSensitiveDetector
{
public:
  MYTrackerSD(const G4String& name,
	      const G4String& hitsCollectionName);
  //G4int ntupleID);
  virtual ~MYTrackerSD();

  virtual void   Initialize(G4HCofThisEvent* hce);
  virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
  virtual void   EndOfEvent(G4HCofThisEvent* hce);



private:
  MYTrackerHitsCollection* fHitsCollection;
  //G4int fNtupleId;

};

#endif
