#include "MYRunAction.hh"
#include "MYAnalysis.hh"
//#include "MYEventAction.hh"

#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"

//add some thing for each function
//if want to create output file
//i.e: histogram, ntuple


MYRunAction::MYRunAction(MYEventAction* theEventAction ) :
  eventAction(theEventAction)
{
  eventAction->SetRootSaver( &saver );
}

MYRunAction::~MYRunAction()
{
}


void MYRunAction::BeginOfRunAction(const G4Run* aRun )
{
  G4cout<<"Starting Run: "<<aRun->GetRunID()<<G4endl;
  //For each run a new TTree is created, with default names

  saver.CreateTree();
}

void MYRunAction::EndOfRunAction( const G4Run* /*aRun*/ )
{
  saver.CloseTree();
}


