#ifndef MYScintTrigSD_h
#define MYScintTrigSD_h 1

#include "G4VSensitiveDetector.hh"
#include "MYScintTrigHit.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class MYScintTrigSD : public G4VSensitiveDetector
{
  public:
    MYScintTrigSD(const G4String& name, 
		  const G4String& hitsCollectionName);
  //G4int ntupleID);
    virtual ~MYScintTrigSD();

    virtual void   Initialize(G4HCofThisEvent* hce);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    virtual void   EndOfEvent(G4HCofThisEvent* hce);

  private:
    MYScintTrigHitsCollection* fHitsCollection;
  //G4int fNtupleId;
};




#endif

