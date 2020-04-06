#include <iostream>
#include <sstream>

#include "SectorSystemTracker.h"


SectorSystemTracker::SectorSystemTracker( unsigned nLayers , unsigned nModules , unsigned nSensors ):

  _nModules( nModules ),
  _nSensors( nSensors )

{
   
  _nLayers = nLayers;
  _sectorMax = 2*nLayers*nModules*nSensors - 1;
   
}


int SectorSystemTracker::getSector( unsigned layer , unsigned module , unsigned sensor )const {


  if ( layer >= _nLayers ){

    std::stringstream s; 
    s << "Layer " << layer << " is too big, the outermost layer is layer " << _nLayers - 1;
    //throw "Out Of Range";

  }

  if ( module >= _nModules ){

    std::stringstream s; 
    s << "Module " << module << " is too big, the highest module is module " << _nModules - 1;
    //throw "Out Of Range";

  }


  if ( sensor >= _nSensors ){

    std::stringstream s;
    s << "Sensor " << sensor << " is too big, the highest sensor is sensor " << _nSensors - 1;
    //throw OutOfRange( s.str() );
    //throw "Out Of Range";

  }


  unsigned multiplicator=1;

  int sector = sensor;
  multiplicator *= _nSensors; //there are nSensors possible values for sensor

  sector += module * multiplicator;
  multiplicator *= _nModules;
   
  sector += layer * multiplicator;
  multiplicator *= _nLayers;
   

  sector += multiplicator;

  return sector;

}


int SectorSystemTracker::getSector( unsigned layer , double x , double z ) const {

  double halfZ = 700.; //half-length in Z-axis of detector
  double zwidth = 70.;
  int module = int ((z+halfZ) / zwidth);

  double halfX = 0.;
  int xwidth = 2; //width of silicon is 2 mm

  if (layer == 0 || layer == 4) halfX = 332.049;
  else if (layer == 1 || layer == 3) halfX = 421.611;
  else if (layer == 2) halfX = 447.5;

  else {
    std::cout << "Layer" << layer << "does not exist" << std::endl;
    return -1;
  }

  int sensor = int ((x + halfX) / xwidth);

  //int sector = SectorSystemTracker::getSector(layer, module, sensor);
  //int sector = getSector(layer, module, sensor);

  if ( layer >= _nLayers ){

    std::stringstream s; 
    s << "Layer " << layer << " is too big, the outermost layer is layer " << _nLayers - 1;
    //throw "Out Of Range";

  }

  if ( module >= _nModules ){

    std::stringstream s; 
    s << "Module " << module << " is too big, the highest module is module " << _nModules - 1;
    //throw "Out Of Range";

  }


  if ( sensor >= _nSensors ){

    std::stringstream s;
    s << "Sensor " << sensor << " is too big, the highest sensor is sensor " << _nSensors - 1;
    //throw OutOfRange( s.str() );
    //throw "Out Of Range";

  }


  unsigned multiplicator=1;

  int sector = sensor;
  multiplicator *= _nSensors; //there are nSensors possible values for sensor

  sector += module * multiplicator;
  multiplicator *= _nModules;
   
  sector += layer * multiplicator;
  multiplicator *= _nLayers;
   

  sector += multiplicator;


  return sector;

}

unsigned SectorSystemTracker::getLayer( int sector ) const {

  checkSectorIsInRange( sector );

  unsigned layer = ( sector / (  _nSensors * _nModules ) ) % _nLayers; //this is an integerdivision --> we will get the floor authomatically

  return layer;

}


unsigned SectorSystemTracker::getModule( int sector ) const {

  checkSectorIsInRange( sector );

  unsigned module = ( sector / ( _nSensors ) ) % _nModules; //this is an integerdivision --> we will get the floor authomatically

  return module;

}


unsigned SectorSystemTracker::getModule(double z ) const {

  double halfZ = 700.; //half-length in Z-axis of detector
  double zwidth = 70.;

  if ( abs(z) > halfZ) {

    std::cout << "Z position " << z << "is outside of detector " << std::endl;
    return -1;
  }

  unsigned module = unsigned ((z+halfZ) / zwidth);

  return module;

}


unsigned SectorSystemTracker::getSensor( int sector ) const {

  checkSectorIsInRange( sector );

  unsigned sensor = ( sector ) % _nSensors;

  return sensor;
   
}


unsigned SectorSystemTracker::getSensor( int layer , double x ) const {

  double halfX = 0.;
  int xwidth = 2; //width of silicon is 2 mm

  if (layer == 0 || layer == 4) halfX = 332.049;
  else if (layer == 1 || layer == 3) halfX = 421.611;
  else if (layer == 2) halfX = 447.5;

  else {
    std::cout << "Layer" << layer << "does not exist" << std::endl;
    return -1;
  }

  if ( abs(x) > halfX) {
    std::cout << "X position " << x << "is outside of detector" << std::endl;
    return -1;
  }

  unsigned sensor = unsigned ((x + halfX) / xwidth);

  return sensor;

}



void SectorSystemTracker::checkSectorIsInRange( int sector ) const {

  if ( sector > _sectorMax ){

    std::stringstream s;
    s << "SectorSystemTracker:\n Sector " 
      << sector << " is too big, the highest possible number for a sector in this configuration of TrackerSegRepresentation is"
      << _sectorMax 
      << ".\nThe configuration is: nLayers = " << _nLayers
      << ", nModules = " << _nModules
      << ", nSensors = " << _nSensors 
          << _nLayers << "*"  
      << _nModules << "*"
      << _nSensors << " -1 = " << 2*_nLayers*_nModules*_nSensors -1 ;
    //throw OutOfRange( s.str() );
    //throw "Out Of Range";
      
  }  

}


std::string SectorSystemTracker::getInfoOnSector( int sector ) const{

  std::stringstream s;
  s << ",la" << getLayer(sector)
    << ",mo" << getModule(sector) 
    << ",se" << getSensor(sector) 
    << ")";

  return s.str();

}


SectorSystemTracker& SectorSystemTracker::operator  = (const SectorSystemTracker& sectorsystem) {
  
  //check for self assigment

  if(this != &sectorsystem) {
    _nModules = sectorsystem._nModules; 
    _nSensors = sectorsystem._nSensors;
  }
  
  return *this; 
} 
