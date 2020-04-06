#include "TrackerSectorConnector.h"

#include <iostream>


TrackerSectorConnector::TrackerSectorConnector( const SectorSystemTracker* sectorSystemTracker , unsigned layerStepMax , unsigned petalStepMax, unsigned lastLayerToIP){

  _sectorSystemTracker = sectorSystemTracker;
  _layerStepMax = layerStepMax;
  _lastLayerToIP = lastLayerToIP;
  _petalStepMax = petalStepMax;
   
}


std::set< int > TrackerSectorConnector::getTargetSectors ( int sector ){

  std::set <int> targetSectors;

  //int side = _sectorSystemTracker->getSide( sector );
  unsigned layer = _sectorSystemTracker->getLayer( sector );
  unsigned module = _sectorSystemTracker->getModule( sector );
  //unsigned sensor = _sectorSystemTracker->getSensor( sector );

  //unsigned nLayers = _sectorSystemTracker->getNumberOfLayers();
  unsigned nModules = _sectorSystemTracker->getNumberOfModules();
  unsigned nSensors = _sectorSystemTracker->getNumberOfSensors();

  //std::cout << "============= layer: " << layer << std::endl;
  for( unsigned layerStep = 1; layerStep <= _layerStepMax; layerStep++ ){

    if ( layer >= layerStep +1 ){ //other wise the we could jump past layer 1, ( layer 0 is covered below)

      unsigned layerTarget = layer - layerStep;

      for ( unsigned iSensor=0; iSensor < nSensors ; iSensor++){ //over all sensors

	for ( int iPetal= int(module) - _petalStepMax; iPetal <= int(module) + int(_petalStepMax) ; iPetal++ ){ 

	  //if iPetal is out of the range from 0 to nModules-1, move it back there. 
	  //And of course use a different variable for that. 
	  //(Or else we would create and endless loop: imagine we have iPetal = 16 and set it back to 0
	  //--> the loop will continue from there until it reaches 16 again and so on...)
	  int iModule = iPetal;
	  while( iModule < 0 ) iModule+= nModules;
	  while( iModule >= int(nModules) ) iModule -= nModules;

	  //targetSectors.insert( _sectorSystemTracker->getSector ( side , layerTarget , iModule , iSensor ) ); 
	  targetSectors.insert( _sectorSystemTracker->getSector ( layerTarget , iModule , iSensor ) ); 
	  //std::cout << "======== target layer of getTargetSector: " << layerTarget << "\n";

	}

      }

    }

  }

  //Allow jumping to layer 0 from layer _lastLayerToIP or less
  if ( ( layer >= 1 )&& ( layer <= _lastLayerToIP ) ){

    unsigned layerTarget = 0;

    for ( unsigned iModule=0; iModule < nModules ; iModule++){ //over all modules
         
      for ( unsigned iSensor=0; iSensor < nSensors ; iSensor++ ){ //over all sensors

	//targetSectors.insert( _sectorSystemTracker->getSector ( side , layerTarget , iModule , iSensor ) ); 
	targetSectors.insert( _sectorSystemTracker->getSector ( layerTarget , iModule , iSensor ) ); 

      }

    }

  }

  return targetSectors;


}
