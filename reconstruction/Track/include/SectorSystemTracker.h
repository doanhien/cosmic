#ifndef SectorSystemTracker_h
#define SectorSystemTracker_h

#include "ISectorSystem.h"

/** A Sector System class.
 * 
 * It calculates sectors from the layer, sensor and module and vice versa.
 * 
 * @param layer: layer of Tracker: 0 is the layer of the IP, 1 is the first Tracker disk and so on.
 * 
 * @param module: module
 * 
 * @param sensor: the sensor on the module
 * 
 */

class SectorSystemTracker : public ISectorSystem{
      
      
 public:

  /**Constructor
   * 
   * @param nLayers the number of possible layers. The layers from 0 to n-1 will be available. Keep in mind,
   * that layer 0 is used for the IP.
   * 
   * @param nModules the number of modules per disk.
   * 
   * @param nSensors the number of sensors on one module.
   */

  SectorSystemTracker( unsigned nLayers , unsigned nModules , unsigned nSensors );
      
      
  /** Calculates the sector number corresponding to the passed parameters
   */
  int getSector( unsigned layer , unsigned module , unsigned sensor ) const ;

  int getSector( unsigned layer , double x, double z ) const ;
      
      
  /** Virtual, because this method is demanded by the Interface ISectorSystem
   * 
   * @return the layer corresponding to the passed sector number
   */
  virtual unsigned getLayer( int sector ) const ;
      
      
  /** @return some information on the sector as string */
  virtual std::string getInfoOnSector( int sector ) const;
      
  /** @return the module of the sector
   */
  unsigned getModule( int sector ) const ; 

  unsigned getModule( double z ) const ; 
      
  /** @return the sensor of the sector
   */
  unsigned getSensor( int sector ) const ;

  unsigned getSensor( int layer, double pos ) const ;
      
      
  unsigned getNumberOfModules() const { return _nModules; }
  unsigned getNumberOfSensors() const { return _nSensors; }

  SectorSystemTracker & operator = (const SectorSystemTracker &sectorsystem);


  virtual ~SectorSystemTracker(){}
      
 private:
      
  unsigned _nModules;
  unsigned _nSensors;
      
  int _sectorMax;
      
  void checkSectorIsInRange( int sector ) const ;
      
};


#endif




