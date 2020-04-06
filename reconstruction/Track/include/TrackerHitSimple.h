#ifndef TrackerHitSimple_h
#define TrackerHitSimple_h

#include "IHit.h"

#include "SectorSystemTracker.h"


/** A hit 
 */   
class TrackerHitSimple : public IHit {
      
      
 public:
      
  TrackerHitSimple( float x , float y , float z , unsigned layer , unsigned module, unsigned sensor, const SectorSystemTracker* const sectorSystemTracker );
      
      
      
  virtual const ISectorSystem* getSectorSystem() const { return _sectorSystemTracker; };
      
  virtual ~TrackerHitSimple(){}
      
 private:
      
  unsigned _layer;
  unsigned _module;
  unsigned _sensor;
      
  const SectorSystemTracker* _sectorSystemTracker;
      
  void calculateSector(){ _sector = _sectorSystemTracker->getSector( _layer , _module , _sensor ); }
      
};
 


#endif
