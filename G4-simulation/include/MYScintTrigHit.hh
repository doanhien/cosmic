#ifndef MYScintTrigHit_h
#define MYScintTrigHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class MYScintTrigHit : public G4VHit
{
  public:
    MYScintTrigHit();
    virtual ~MYScintTrigHit();
    MYScintTrigHit(const MYScintTrigHit& right);
    const MYScintTrigHit& operator=(const MYScintTrigHit& right);
    int operator==(const MYScintTrigHit& right) const;

    inline void* operator new(size_t);
    inline void  operator delete(void* hit);

    virtual void Print();

    // add setter/getter methods
    void SetLayerNumber(G4int number) { fLayerNumber = number; }
    void AddEdep(G4double edep)       { fEdep += edep; }

    G4int    GetLayerNumber() const { return fLayerNumber;}
    G4int    GetModule() const { return fModuleNumber;}
    G4int    GetSensor() const { return fSensorNumber;}
    G4double GetEdep() const        { return fEdep; }

  private:
    // add data members
    G4int     fLayerNumber;
    G4int     fModuleNumber;
    G4int     fSensorNumber;
    G4double  fEdep;
    G4ThreeVector  fPosition;
};

typedef G4THitsCollection<MYScintTrigHit> MYScintTrigHitsCollection;

extern G4ThreadLocal G4Allocator<MYScintTrigHit>* MYScintTrigHitAllocator;

inline void* MYScintTrigHit::operator new(size_t)
{
  if (! MYScintTrigHitAllocator)
        MYScintTrigHitAllocator = new G4Allocator<MYScintTrigHit>;
  return (void*)MYScintTrigHitAllocator->MallocSingle();
}

inline void MYScintTrigHit::operator delete(void* hit)
{
  MYScintTrigHitAllocator->FreeSingle((MYScintTrigHit*) hit);
}

#endif


