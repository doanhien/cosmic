#ifndef MYRunAction_h
#define MYRunAction_h

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "MYEventAction.hh"
#include "RootSaver.hh"

class G4Run;

class MYRunAction : public G4UserRunAction
{

  /*
 public:
  MYRunAction();
  virtual ~MYRunAction();

  virtual void BeginOfRunAction(const G4Run*);
  virtual void EndOfRunAction(const G4Run*);
  */

public:
  MYRunAction( MYEventAction* evAct );
  virtual ~MYRunAction();

  virtual void BeginOfRunAction(const G4Run*);
  virtual void EndOfRunAction(const G4Run*);

private:
  RootSaver saver;
  MYEventAction* eventAction;




};

#endif
