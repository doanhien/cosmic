#ifndef MYPrimaryGeneratorAction_h
#define MYPrimaryGeneratorAction_h

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4Event;
class G4ParticleGun;
class G4GenericMessenger;


class MYPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{

 public:
  MYPrimaryGeneratorAction();
  virtual ~MYPrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event*);
  G4double GetEnergyPrimary() const  {return energy_pri;};

 private:
  G4GenericMessenger*  fMessenger;
  G4ParticleGun*  fParticleGun;
  G4bool          fRandom;
  G4double energy_pri;

};

#endif
