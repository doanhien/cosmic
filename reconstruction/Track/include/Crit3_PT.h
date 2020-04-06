#ifndef Crit3_PT_h
#define Crit3_PT_h

#include "ICriterion.h"

class Crit3_PT : public ICriterion {

 public:

  Crit3_PT ( float ptMin , float ptMax , float Bz );
      
  virtual bool areCompatible( Segment* parent , Segment* child );
      
  virtual ~Crit3_PT(){};
      
      
 private:
      
  float _ptMin{};
  float _ptMax{};
  float _Bz{};
      

};

#endif
