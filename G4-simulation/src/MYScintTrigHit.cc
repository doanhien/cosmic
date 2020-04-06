#include "MYScintTrigHit.hh"

#include <G4UnitsTable.hh>

#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal G4Allocator<MYScintTrigHit>* MYScintTrigHitAllocator = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MYScintTrigHit::MYScintTrigHit()
 : G4VHit(),
   fLayerNumber(-1),
   fModuleNumber(-1),
   fSensorNumber(-1),
   fEdep(0.),
   fPosition()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MYScintTrigHit::~MYScintTrigHit()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MYScintTrigHit::MYScintTrigHit(const MYScintTrigHit& /*right*/)
 : G4VHit() 
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const MYScintTrigHit& 
MYScintTrigHit::operator=(const MYScintTrigHit& /*right*/)
{
  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int MYScintTrigHit::operator==(const MYScintTrigHit& /*right*/) const
{
  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MYScintTrigHit::Print()
{
  if ( fEdep > 0. ) {
    G4cout << "scintillator hit in layer: " << fLayerNumber 
           << "  Edep: " << std::setw(7) << G4BestUnit(fEdep,"Energy") 
	   << "  position: " << fPosition << G4endl;
  }          
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


