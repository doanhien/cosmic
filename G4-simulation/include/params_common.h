#ifndef __PARAMS_COMMON_H__
#define __PARAMS_COMMON_H__

#include "G4String.hh"

typedef struct _volume_name {
    G4String base;
    G4String solid;
    G4String logical;
    G4String physical;

    _volume_name( void ){ 
        solid = logical = physical = "";
    }

    _volume_name( G4String name ){
        base     = name;
        solid    = "soli" + name;
        logical  = "logi" + name;
        physical = "phys" + name;
    }
} VOLUME_NAME;

#define WORLD_NAME "pWorld"
#define WORLD_X     2.0*m
#define WORLD_Y     2.0*m
#define WORLD_Z     2.0*m
#define WORLD_COL_R 100
#define WORLD_COL_G 100
#define WORLD_COL_B 100

#endif
