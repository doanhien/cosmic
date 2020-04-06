#ifndef TrackerSectorConnector_h
#define TrackerSectorConnector_h

#include "ISectorConnector.h"

#include "SectorSystemTracker.h"


/** Used to connect two sectors on the Tracker.
 * 
 * 
 * Allows:
 * 
 * - going to layers on the inside (how far see constructor)
 * - going to same petal or petals around (how far see constructor)
 * - jumping to the IP (from where see constructor)
 */   
class TrackerSectorConnector : public ISectorConnector{
      
      
 public:

  /** @param layerStepMax the maximum distance of the next layer on the inside
   * 
   *  @param petalStepMax the maximum distance of the next petal (in + and - direction )
   * 
   *  @param lastLayer the highest layer
   */

  TrackerSectorConnector ( const SectorSystemTracker* sectorSystemTracker , unsigned layerStepMax , unsigned petalStepMax , unsigned lastLayer);

  /** @return a set of all sectors that are connected to the passed sector */
  virtual std::set <int>  getTargetSectors ( int sector );

  virtual ~TrackerSectorConnector(){};

 private:
      
  const SectorSystemTracker* _sectorSystemTracker;
      
  unsigned _layerStepMax;
  unsigned _petalStepMax;
  unsigned _lastLayerToIP;
      
      
};
   
#endif


