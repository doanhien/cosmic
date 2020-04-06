#ifndef TrackerNeighborPetalSecCon_h
#define TrackerNeighborPetalSecCon_h

#include "ISectorConnector.h"

#include "SectorSystemTracker.h"

class TrackerNeighborPetalSecCon : public ISectorConnector{
      
      
 public:

  TrackerNeighborPetalSecCon ( const SectorSystemTracker* sectorSystemTracker );
      
  virtual std::set <int>  getTargetSectors ( int sector );
      
  virtual ~TrackerNeighborPetalSecCon(){};
      
 private:
      
  const SectorSystemTracker* _sectorSystemTracker;

};


#endif
