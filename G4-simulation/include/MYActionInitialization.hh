#ifndef MYActionInitialization_h
#define MYActionInitialization_h 1


#include "G4VUserActionInitialization.hh"

class MYActionInitialization : public G4VUserActionInitialization
{

 public:
  MYActionInitialization();
  virtual ~MYActionInitialization();

  virtual void Build() const;
  virtual void BuildForMaster() const;

};

#endif
