#include "Crit2_DeltaY.h"

#include <cmath>
#include <sstream>
#include <iostream>

Crit2_DeltaY::Crit2_DeltaY ( float deltaYMin , float deltaYMax ){
   
   
  _deltaYMax = deltaYMax;  
  _deltaYMin = deltaYMin;
   
  _name = "Crit2_DeltaY";
  _type = "2Hit";
   
  _saveValues = false;
   
}



bool Crit2_DeltaY::areCompatible( Segment* parent , Segment* child ){

  if (( parent->getHits().size() == 1 )&&( child->getHits().size() == 1 )){ //a criterion for 1-segments

    IHit* a = parent->getHits()[0];
    IHit* b = child-> getHits()[0];

    //float ax = a->getX();
    float ay = a->getY();

    //float bx = b->getX();
    float by = b->getY();
      
    //the distance to (0,0) in the xy plane
    //float rhoA =  sqrt( ax*ax + ay*ay );
    //float rhoB =  sqrt( bx*bx + by*by );

    float deltaY = abs(ay - by); //using absolute value

    std::cout << "deltaY = " << deltaY << std::endl;
    //first check, if the distance to (0,0) rises --> such a combo could not reach the IP

    if (_saveValues){
      _map_name_value["Crit2_DeltaY_yParent"] = ay;
      _map_name_value["Crit2_DeltaY_yChild"] = by;
      _map_name_value["Crit2_DeltaY"] = deltaY;
    }

    if ( deltaY > _deltaYMax ) return false;
    if ( deltaY < _deltaYMin ) return false;
  }

  else {
    std::stringstream s;
    s << "Crit2_DeltaY::This criterion needs 2 segments with 1 hit each, passed was a "
      <<  parent->getHits().size() << " hit segment (parent) and a "
      <<  child->getHits().size() << " hit segment (child).";
      
    //throw BadSegmentLength( s.str() );
    //throw "Bad Segment Length!";
  }

  return true;
}

