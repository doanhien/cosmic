#include "TrackerHitSimple.h"


TrackerHitSimple::TrackerHitSimple( float x , float y , float z , unsigned layer , unsigned module, unsigned sensor, const SectorSystemTracker* const sectorSystemTracker ){
   
   
  _sectorSystemTracker = sectorSystemTracker;
   
  _x = x;
  _y = y; 
  _z = z; 
   
  
  _layer  = layer;
  _module = module;
  _sensor = sensor;
   
   
  calculateSector();
   
   
  //We assume a real hit. If it is virtual, this has to be set.
  _isVirtual = false;
   
   
}
