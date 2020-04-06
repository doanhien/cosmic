#ifndef Crit2_DeltaY_h
#define Crit2_DeltaY_h


#include "ICriterion.h"

/** Criterion: the difference of the sqrt(x^2 + y^2) of two hits.
 */
class Crit2_DeltaY : public ICriterion{

 public:
  Crit2_DeltaY ( float deltaYMin , float deltaYMax );
      
  virtual bool areCompatible( Segment* parent , Segment* child );
      
  virtual ~Crit2_DeltaY(){};
      
    
 private:
      
  float _deltaYMax{};
  float _deltaYMin{};
      
      
      
};

#endif
