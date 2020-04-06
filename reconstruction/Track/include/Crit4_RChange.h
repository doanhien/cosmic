#ifndef Crit4_RChange_h
#define Crit4_RChange_h

#include "ICriterion.h"

class Crit4_RChange : public ICriterion{


 public:

  Crit4_RChange ( float changeMin , float changeMax );
      
  virtual bool areCompatible( Segment* parent , Segment* child );
      
  virtual ~Crit4_RChange(){};
      
 private:
      
  float _changeMin{};
  float _changeMax{};
      
};

#endif
