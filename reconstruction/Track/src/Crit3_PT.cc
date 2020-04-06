#include "Crit3_PT.h"

#include <cmath>
#include <sstream>

#include "SimpleCircle.h"

Crit3_PT::Crit3_PT( float ptMin , float ptMax , float Bz ){

  _ptMin = ptMin;
  _ptMax = ptMax;
  _Bz = Bz;
   
  _name = "Crit3_PT";
  _type = "3Hit";
   
  _saveValues = false;
   
}

bool Crit3_PT::areCompatible( Segment* parent , Segment* child ) {

  if (( parent->getHits().size() == 2 )&&( child->getHits().size() == 2 )){ //a criterion for 2-segments

    IHit* a = child->getHits()[0];
    IHit* b = child->getHits()[1];
    IHit* c = parent-> getHits()[1];
      
    float ax = a->getX();
    float ay = a->getY();
     
    float bx = b->getX();
    float by = b->getY();
      
    float cx = c->getX();
    float cy = c->getY();


    try{
      SimpleCircle circle ( ax , ay , bx , by , cx , cy );

      double R = circle.getRadius();

      const double K= 0.00029979; //K depends on the used units

      double pt = R * K * _Bz;

      if (_saveValues) _map_name_value["Crit3_PT"] =  pt;

      if ( pt < _ptMin ) return false;
      if ( pt > _ptMax ) return false;
    }
    //catch ( InvalidParameter ){
    catch (const std::string& ex) {

      if (_saveValues) _map_name_value["Crit3_PT"] =  0.;
    }

  }
  else {
    std::stringstream s;
    s << "Crit3_PT::This criterion needs 2 segments with 2 hits each, passed was a "
      <<  parent->getHits().size() << " hit segment (parent) and a "
      <<  child->getHits().size() << " hit segment (child).";
      
    //throw BadSegmentLength( s.str() );
    //throw "bad segment length!";
        
  }

  return true;

}