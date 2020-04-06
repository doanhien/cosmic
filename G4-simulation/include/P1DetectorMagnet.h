#ifndef __P1_MAGNET_H__
#define __P1_MAGNET_H__

#include "P1DetectorParts.h"

namespace P1Detector{

static const char     SOLN_NAME[] = "Solenoid";
static const G4double SOLN_RMIN   =  44.81*cm;
static const G4double SOLN_RMAX   =  45.16*cm;
static const G4double SOLN_DZ     =  140*cm;
static const G4double SOLN_X      =  0;
static const G4double SOLN_Y      =  0;
static const G4double SOLN_Z      =  0;

static const char     STR_NAME[] = "Strip";
static const G4double STR_RMIN   =  44.98*cm;
static const G4double STR_RMAX   =  45.02*cm;

static const char     CND1_NAME[] = "Conductor1";
static const G4double CND1_RMIN   =  44.84*cm;
static const G4double CND1_RMAX   =  44.96*cm;

static const char     CND2_NAME[] = "Conductor2";
static const G4double CND2_RMIN   =  45.04*cm;
static const G4double CND2_RMAX   =  45.13*cm;

static const char     IN11_NAME[] = "Inner1";
static const G4double IN11_RMIN   =  44.82*cm;
static const G4double IN11_RMAX   =  44.84*cm;

static const char     IN12_NAME[] = "Inner2";
static const G4double IN12_RMIN   =  44.96*cm;
static const G4double IN12_RMAX   =  44.98*cm;

static const char     IN13_NAME[] = "Inner3";
static const G4double IN13_RMIN   =  45.02*cm;
static const G4double IN13_RMAX   =  45.04*cm;

static const char     IN14_NAME[] = "Inner4";
static const G4double IN14_RMIN   =  45.13*cm;
static const G4double IN14_RMAX   =  45.15*cm;

static const char     PUR1_NAME[] = "Strip1";
static const G4double PUR1_RMIN   =  44.82*cm;
static const G4double PUR1_RMAX   =  44.84*cm;

static const char     PUR2_NAME[] = "Strip2";
static const G4double PUR2_RMIN   =  45.15*cm;
static const G4double PUR2_RMAX   =  45.16*cm;

class Magnet : public P1DetectorParts {
public:
    void Initialize( G4LogicalVolume *mother, MaterialFactory *mfactory );
};

}

#endif
