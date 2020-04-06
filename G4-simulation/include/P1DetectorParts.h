#ifndef __P1_DETECTOR_PARTS_H__
#define __P1_DETECTOR_PARTS_H__

#include "G4VSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include <G4SystemOfUnits.hh>

#include "MaterialFactory.h"
#include "params_common.h"


class P1DetectorParts {
protected:
    G4VSolid          *solid;
    G4LogicalVolume   *logical_volume;
    G4VPhysicalVolume *physical_volume;

    VOLUME_NAME       *name;

    bool               check_overlap;

public:
    P1DetectorParts( void );
    virtual ~P1DetectorParts();

    G4VSolid          *Solid         ( void ){ return solid; }
    G4LogicalVolume   *LogicalVolume ( void ){ 
      G4cout << ">>>>>>>> return logical volume of solenoid" << G4endl;
      return logical_volume; }
    G4VPhysicalVolume *PhysicalVolume( void ){ return physical_volume; }
    
    VOLUME_NAME       *GetName( void ){ 
      G4cout << "getting volume_name" << G4endl;
      return name; }

    virtual void Initialize( G4LogicalVolume *mother, MaterialFactory *mfactory ) = 0;

    void SetOverlapCheck  ( bool chk = true ){ check_overlap = chk;  }
    void UnsetOverlapCheck( void )           { check_overlap = false; }
};

#endif
