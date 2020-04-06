#include "MYTrackerHit.hh"

#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4SystemOfUnits.hh"

G4ThreadLocal G4Allocator<MYTrackerHit>* MYTrackerHitAllocator = 0;

MYTrackerHit::MYTrackerHit(const G4int layer, const G4int module, const G4int strip)
  : G4VHit(),
    fLayerNumber(layer),
    fModule(module),
    fStrip(strip),
    fTime(0.),
    fPosition(),
    fChamberNb(-1),
    fEdep(0.),
    fTrackID(-1),
    ftrackname(),
    fparentID(-1),
    ftrackPDGencode(-1),
    fMomentum()
{
}

MYTrackerHit::~MYTrackerHit()
{
}

MYTrackerHit::MYTrackerHit(const MYTrackerHit& right)
  : G4VHit()
{
  fTrackID     = right.fTrackID;
  fChamberNb   = right.fChamberNb;
  fLayerNumber = right.fLayerNumber ;
  fModule      = right.fModule;
  fStrip       = right.fStrip;
  ftrackname   = right.ftrackname;
  fparentID    = right.fparentID;
  ftrackPDGencode = right.ftrackPDGencode;
}

const MYTrackerHit& MYTrackerHit::operator=(const MYTrackerHit& right)
{
  fTrackID     = right.fTrackID;
  fChamberNb   = right.fChamberNb;
  fLayerNumber = right.fLayerNumber ;
  fModule      = right.fModule;
  fStrip       = right.fStrip;
  ftrackname   = right.ftrackname;
  fparentID    = right.fparentID;
  ftrackPDGencode= right.ftrackPDGencode;

  return *this;
}

int MYTrackerHit::operator==(const MYTrackerHit& right) const
{
  return ( this == &right ) ? 1 : 0;
}

void MYTrackerHit::Print()
{
  G4cout << "Chamber hit in layer: " << fLayerNumber
         << "   time [s]: " << fTime/s
         << "   position [mm]: " <<  fPosition/mm 
	 << "   trackID: " << fTrackID << " chamberNb: " << fChamberNb << G4endl;
}


void MYTrackerHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
    {
      G4Circle circle(fPosition);
      circle.SetScreenSize(4.);
      circle.SetFillStyle(G4Circle::filled);
      G4Colour colour(1.,0.,0.);
      G4VisAttributes attribs(colour);
      circle.SetVisAttributes(attribs);
      pVVisManager->Draw(circle);
    }
}
