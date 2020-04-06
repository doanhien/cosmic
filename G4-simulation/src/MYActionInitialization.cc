#include "MYActionInitialization.hh"
#include "MYPrimaryGeneratorAction.hh"
#include "MYEventAction.hh"
#include "MYRunAction.hh"

MYActionInitialization::MYActionInitialization()
  :G4VUserActionInitialization()
{
}

MYActionInitialization::~MYActionInitialization()
{
}

void MYActionInitialization::BuildForMaster() const
{
  MYEventAction* theEventAction = new MYEventAction();
  SetUserAction(new MYRunAction(theEventAction));
}

void MYActionInitialization::Build() const
{
 
  G4cout << "--------- MYPrimaryGeneratorAction --------- " << G4endl;
  SetUserAction(new MYPrimaryGeneratorAction);
  G4cout << "--------- MYRunAction --------- " << G4endl;
  MYEventAction* theEventAction = new MYEventAction();
  SetUserAction(new MYRunAction(theEventAction));
  G4cout << "--------- MYEventAction --------- " << G4endl;
  //SetUserAction(new MYEventAction);
  SetUserAction(theEventAction);
}
