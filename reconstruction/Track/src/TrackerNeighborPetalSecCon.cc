#include "TrackerNeighborPetalSecCon.h"


TrackerNeighborPetalSecCon::TrackerNeighborPetalSecCon( const SectorSystemTracker* sectorSystemTracker ){
   
  _sectorSystemTracker = sectorSystemTracker;
     
}



std::set< int > TrackerNeighborPetalSecCon::getTargetSectors ( int sector ){
   
   
   
  std::set <int> targetSectors;
   
   
  unsigned layer = _sectorSystemTracker->getLayer( sector );
  unsigned petal = _sectorSystemTracker->getModule( sector );
  //    unsigned sensor = _sectorSystemTracker->getSensor( sector );
   
  //    unsigned nLayers = _sectorSystemTracker->getNumberOfLayers();
  unsigned nPetals = _sectorSystemTracker->getNumberOfModules();
  unsigned nSensors = _sectorSystemTracker->getNumberOfSensors();
   
   
  unsigned petalToTheLeft = petal - 1; //the names left and right are arbitrary, as it of course depends on from where one looks.
  unsigned petalToTheRight = petal + 1;
   
  //Now we have to make sure that we didn't leave the petal range 0 to nPetals-1
  if (petal == 0) petalToTheLeft = nPetals - 1;
  if (petal == nPetals - 1) petalToTheRight = 0;
   
   
   
  for ( unsigned iSensor=0; iSensor < nSensors ; iSensor++ ){ //over all sensors
      
      
    targetSectors.insert( _sectorSystemTracker->getSector ( layer ,petalToTheLeft, iSensor ) ); 
    targetSectors.insert( _sectorSystemTracker->getSector ( layer ,petalToTheRight, iSensor ) );
      
  }
   
   
   
  return targetSectors;
   
   
}
