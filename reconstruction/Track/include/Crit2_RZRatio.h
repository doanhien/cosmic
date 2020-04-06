#ifndef Crit2_RZRatio_h
#define Crit2_RZRatio_h

#include "ICriterion.h"

class Crit2_RZRatio:public ICriterion {

 public:
  Crit2_RZRatio ( float ratioMin, float ratioMax );
      
  virtual bool areCompatible( Segment* parent , Segment* child );
      
  virtual ~Crit2_RZRatio(){};
    
 private:
      
  float _ratioMax{};
  float _ratioMin{};
      
};

#endif
