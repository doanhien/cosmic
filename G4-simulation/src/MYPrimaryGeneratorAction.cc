#include "MYPrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4GenericMessenger.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
#include "G4Event.hh"

#include "Randomize.hh"

#include "MYAnalysis.hh"

//G4String particleName = "mu-";

MYPrimaryGeneratorAction::MYPrimaryGeneratorAction()
  :G4VUserPrimaryGeneratorAction(),
   fMessenger(0),
   fParticleGun(0),
   fRandom(true) 
{

  energy_pri=0;

  G4int nofParticle = 1;
  fParticleGun = new G4ParticleGun(nofParticle);

  G4String particleName = "e-";
  //G4double ypos = 70*cm;
  //G4ThreeVector position(0., ypos, 0.);
  //G4ThreeVector momentum(0., 1.*GeV, 0.);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName);
  fParticleGun->SetParticleDefinition(particle);
  //fParticleGun->SetParticlePosition(position);
  //fParticleGun->SetParticleMomentum(momentum);
  
  G4cout << "particle: " << particleName << G4endl;

  //generic messenger
  fMessenger = new G4GenericMessenger(this, "BessMagnet/Primary/", "primary generator control");
  fMessenger->DeclareProperty("setRandom", fRandom, "Active/Inactive random option");

}

MYPrimaryGeneratorAction::~MYPrimaryGeneratorAction()
{
}

void MYPrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{

  /*
  G4String particleName;

  if (fRandom) {
    G4int i = (int) (3.*G4UniformRand());
    switch(i){
    case 0: particleName = "mu+"; break;
    case 1: particleName = "mu-"; break;
    case 2: particleName = "e+"; break;
    case 3: particleName = "e-"; break;
    }
  }
  else particleName = "e-";  

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName);
  fParticleGun->SetParticleDefinition(particle);
  */

  energy_pri=0;
  
  G4double Ekin = 1000.*MeV;
  G4double energy = 0.8*GeV;
  G4int inputState = -1;

  /*
  if (fRandom) {
    while ( inputState < 0) {
      energy = Ekin*G4UniformRand();
      if (energy >= 100.) inputState = 1;
    }
  }
  */

  //G4cout << "kind of particle = " << particleName << "\t energy = " << energy << G4endl; 
  G4cout << "energy = " << energy << G4endl;
  //fParticleGun->SetParticleEnergy(energy);
  fParticleGun->SetParticleMomentum(energy);

  //random direction of particle
  G4double theta, phi;
  G4double xpos, ypos, zpos;

  if (fRandom) {
    //G4double dtheta = 0.*deg;
    G4double dtheta = 70.*deg;
    G4double dphi = 360.*deg;
    theta = G4UniformRand()*dtheta;
    phi = G4UniformRand()*dphi;

    G4double xdir = sin(theta)*sin(phi);
    G4double ydir = cos(theta);
    G4double zdir = sin(theta)*cos(phi);
    if (ydir > 0.) ydir *=-1;
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(xdir, ydir, zdir));

    //fParticleGun->SetParticleMomentumDirection(
    //		  G4ThreeVector(sin(theta)*sin(phi), sin(theta)*cos(phi), cos(theta)));
    //G4cout << "direction of particle in x: " << sin(theta)*sin(phi) << "\t in y: " << sin(theta)*cos(phi) << G4endl;


    G4double dx = 40.*cm;
    G4double dy = 1.5*m;
    G4double dz = 100.*cm;
    xpos = sin(theta)*sin(phi)*dx;
    ypos = dy;
    zpos = sin(theta)*cos(phi)*dz;

    //G4double xpos = dx;
    //G4double zpos = dz;

    //G4double xpos = 0.;
    //G4double zpos = 0.;
    //G4cout << "position of particle in x: " << xpos << "\t in z: " << zpos << "\t phi: " << theta << "\t sin(phi): " << sin(phi) << G4endl;
  
    //fParticleGun->SetParticlePosition(G4ThreeVector(xpos, ypos, zpos));
  }
  else {
    xpos = 0.;
    ypos = 1.5*m;
    zpos = 0.;
    theta = 0.;
    phi = 0.;
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., -1., 0.));
    //fParticleGun->SetParticlePosition(G4ThreeVector(0., 2.*m, 0.));
  }

  //G4cout << "position of source, x: " << xpos << "\t y: " << ypos << "\t z: " << zpos << G4endl;
  fParticleGun->SetParticlePosition(G4ThreeVector(xpos, ypos, zpos));

  fParticleGun->GeneratePrimaryVertex(event);

  energy_pri = fParticleGun->GetParticleEnergy();

  /*
  //save in ntuple
  G4int eventID = event->GetEventID();
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillNtupleIColumn(7, 0, eventID);
  analysisManager->FillNtupleDColumn(7, 1, energy);
  analysisManager->FillNtupleDColumn(7, 2, xpos);
  analysisManager->FillNtupleDColumn(7, 3, ypos);
  analysisManager->FillNtupleDColumn(7, 4, zpos);
  analysisManager->FillNtupleDColumn(7, 5, theta);
  analysisManager->FillNtupleDColumn(7, 6, phi);
  analysisManager->AddNtupleRow(5);
  
  G4cout << "event number: " << eventID << G4endl;
  */

}
