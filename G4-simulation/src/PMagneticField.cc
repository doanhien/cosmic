#include "PMagneticField.h"
#include "P1DetectorMagnet.h"
#include "BessMagnet.h"

#include "MessageManager.h"

#include <iostream>
#include <iomanip>

using namespace std;

PMagneticField::PMagneticField( void )
{
    bMagnet = new BessMagnet;
    /*
    const int    nr   = 100;
    const int    nz   = 100;
    const double rmax = 500.;
    const double zmax = 550.;
    */

    const int    nr   = 400;
    const int    nz   = 400;
    //const double rmax = 1000.;
    //const double zmax = 550.;
    const double rmax = 2000.;
    const double zmax = 2000.;

    const double dr   = rmax / nr;
    const double dz   = zmax / nz;
    bMagnet->MakeTable( nr, nz, dr, dz );
    //G4cout << "---------done constructing PMagneticField-------------" << G4endl;
}

PMagneticField::~PMagneticField()
{
    delete bMagnet;
}

void PMagneticField::GetFieldValue( const G4double point[4], G4double *bField ) const
{
  //G4cout << "getting field value from PMagneticField" << G4endl;
    const G4double x = point[0];
    const G4double y = point[1];
    const G4double z = point[2];
    const G4double r = sqrt( x*x + y*y );

    //if( r < 45*cm && z < 50.0*cm && z > -50.0*cm )
    //if( r < 90.0*cm && z < 50.0*cm && z > -50.0*cm )
    if( sqrt(r*r+z*z) < 200.0*cm )
    {
      //Double_t br, bz;
        G4double br, bz;
        bMagnet->GetField( r/mm, z/mm, br, bz );
        br = -br;
        bz = -bz;

        bField[0] = br*x/r * tesla;
        bField[1] = br*y/r * tesla;
        bField[2] = bz     * tesla;

	//for testing
	//bField[0] = bField[1] = bField[2] = 0.;
	/*
	if ( r < 400.) {
	  G4cout << std::setprecision(5) << std::fixed << G4endl;
	  G4cout << "magnetic field bz =: " << bField[2] << "\t bx = " << bField[0] 
		 << "\t by = " << bField[1] << G4endl;
	  G4cout << "position of field, x= :" << x/mm << "\t y = " << y/mm << "\t z= " << z/mm << G4endl;
	}
	*/
    }
    else
    {
        bField[0] = bField[1] = bField[2] = 0;
    }
}
