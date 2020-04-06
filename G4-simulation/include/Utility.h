#ifndef __UTILITY_H__
#define __UTILITY_H__

#include "G4LogicalVolume.hh"

class Util {
public:
    static void SetColor( G4LogicalVolume*, G4int, G4int, G4int, G4double alpha = 1. );
    static void SolidMode( G4LogicalVolume* );
    static void WireMode ( G4LogicalVolume* );
    static void Invisible( G4LogicalVolume* );
    static void Visible  ( G4LogicalVolume* );
};

#endif
