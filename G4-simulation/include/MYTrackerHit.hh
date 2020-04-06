#ifndef MYTrackerHit_h
#define MYTrackerHit_h

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class MYTrackerHit : public G4VHit
{
public:
  MYTrackerHit(const G4int layer, const G4int module, const G4int strip);
  virtual ~MYTrackerHit();
  MYTrackerHit(const MYTrackerHit& right);
  const MYTrackerHit& operator=(const MYTrackerHit& right);
  int operator==(const MYTrackerHit &right) const;
  
  inline void* operator new(size_t);
  inline void  operator delete(void* hit);
  
  virtual void Print();
  virtual void Draw();

  //setter methods
  //void SetLayerNumber(G4int number) { fLayerNumber = number; }
  void SetGlobalTime(G4double time)             { fTime = time; }
  void SetPosition(G4ThreeVector position)      { fPosition = position; }
  void SetMomentum(G4ThreeVector momentum)      { fMomentum = momentum; }
  void SetEdep(G4double edep)                   { fEdep = edep; }
  void SetTrackID( G4int trackID )              { fTrackID = trackID; }
  void SetTrackName( G4String trackname )       { ftrackname = trackname; }
  void SetMotherID( G4int parentID )            { fparentID = parentID; }
  void SetParticleType (G4int trackPDGencode )  { ftrackPDGencode = trackPDGencode;}


  //getter methods
  G4int          GetLayerNumber() const   { return fLayerNumber;}
  G4int          GetModule() const        { return fModule;}
  G4int          GetStrip() const         { return fStrip;}
  G4double       GetGlobalTime() const    { return fTime; }
  G4ThreeVector  GetPosition() const      { return fPosition; }
  G4int          GetTrackID() const       { return fTrackID; };
  G4int          GetChamberNb() const     { return fChamberNb; };
  G4double       GetEdep() const          { return fEdep; }
  G4String       GetTrackName () const    { return ftrackname; }
  G4int          GetMotherID () const     { return fparentID; }
  G4int          GetParticleType () const { return ftrackPDGencode; }
  G4ThreeVector  GetMomentum() const      {return fMomentum;}


private:
  //data members
  G4int          fLayerNumber;
  G4int          fModule;
  G4int          fStrip;
  G4double       fTime;
  G4ThreeVector  fPosition;
  G4int          fChamberNb;
  G4double       fEdep;
  G4int          fTrackID;
  G4String       ftrackname;
  G4int          fparentID;
  G4int          ftrackPDGencode;
  G4ThreeVector  fMomentum;

};

typedef G4THitsCollection<MYTrackerHit> MYTrackerHitsCollection;

extern G4ThreadLocal G4Allocator<MYTrackerHit>* MYTrackerHitAllocator;

inline void* MYTrackerHit::operator new(size_t)
{
  if (! MYTrackerHitAllocator)
    MYTrackerHitAllocator = new G4Allocator<MYTrackerHit>;
  return (void*)MYTrackerHitAllocator->MallocSingle();
}

inline void MYTrackerHit::operator delete(void* hit)
{
  MYTrackerHitAllocator->FreeSingle((MYTrackerHit*) hit);
}



#endif
