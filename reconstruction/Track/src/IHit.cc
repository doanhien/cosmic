#include "IHit.h"

#include <cmath>
#include <sstream>


float IHit::distTo( IHit* otherHit ){
   
   
   
  float dx = otherHit->getX() - _x;
  float dy = otherHit->getY() - _y;
  float dz = otherHit->getZ() - _z;
      
  return sqrt( dx*dx + dy*dy + dz*dz );
   
}

std::string IHit::getPositionInfo(){
   
  std::stringstream info;
   
  info << "(" << _x << "," << _y << "," << _z << ")";
   
  return info.str();
   
}
