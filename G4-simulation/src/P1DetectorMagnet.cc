#include "P1DetectorMagnet.h"
#include "params_common.h"
#include "MessageManager.h"
#include "Utility.h"

#include "G4VSolid.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

namespace P1Detector {

void Magnet::Initialize( G4LogicalVolume *mother, MaterialFactory *mfactory )
{
  PMessage( "Solenoid Magnet\n" );

    const G4double dz   = SOLN_DZ;
    const G4double sphi = 0*deg;
    const G4double dphi = 360*deg;

    // Dummy volume
    VOLUME_NAME soln( SOLN_NAME );
    solid = new G4Tubs( soln.solid, 
                        SOLN_RMIN, 
                        SOLN_RMAX,
                        dz/2.,
                        sphi,
                        dphi );
    logical_volume = new G4LogicalVolume( 
            solid,
            mfactory->GetMaterial( MaterialFactory::M_VACUUM ),
            soln.logical,
            0, 0, 0 );
    //Util::Invisible( logical_volume );
    //Util::SetColor(logical_volume, 120., 0., 0., 0.2);
    //Util::SolidMode(logical_volume);
    G4ThreeVector pos( SOLN_X, SOLN_Y, SOLN_Z );
    physical_volume = new G4PVPlacement( 
            0, pos, logical_volume, soln.physical,
            mother, 0, check_overlap ); 

    //G4cout << "solenoid logical name: " << soln.logical << G4endl;
    // Solenoid magnet
    const int n_parts = 9;
    const G4String det_name[n_parts] = { STR_NAME,  CND1_NAME, CND2_NAME, 
                                     IN11_NAME, IN12_NAME, IN13_NAME,
                                     IN14_NAME, PUR1_NAME, PUR2_NAME };
    const G4double rmin[n_parts] = { STR_RMIN,  CND1_RMIN, CND2_RMIN, 
                                     IN11_RMIN, IN12_RMIN, IN13_RMIN,
                                     IN14_RMIN, PUR1_RMIN, PUR2_RMIN };
    const G4double rmax[n_parts] = { STR_RMAX,  CND1_RMAX, CND2_RMAX, 
                                     IN11_RMAX, IN12_RMAX, IN13_RMAX,
                                     IN14_RMAX, PUR1_RMAX, PUR2_RMAX };
    /*    const G4int mat[n_parts] = { MaterialFactory::M_VACUUM,
                               MaterialFactory::M_ALUMINIUM,
                               MaterialFactory::M_MAG_CONDUCTOR,
                               MaterialFactory::M_MAG_CONDUCTOR,
                               MaterialFactory::M_MYLAR,
                               MaterialFactory::M_MYLAR,
                               MaterialFactory::M_MYLAR,
                               MaterialFactory::M_MYLAR,
                               MaterialFactory::M_ALUMINIUM };
    */
    const G4int mat[n_parts] = { MaterialFactory::M_VACUUM,
                               MaterialFactory::M_VACUUM,
                               MaterialFactory::M_VACUUM,
                               MaterialFactory::M_VACUUM,
                               MaterialFactory::M_VACUUM,
                               MaterialFactory::M_VACUUM,
                               MaterialFactory::M_VACUUM,
                               MaterialFactory::M_VACUUM,
                               MaterialFactory::M_VACUUM };
    

    for( int i = 0; i < n_parts; i++ )
    {
      //G4cout << "material ith: " << mat[i] << G4endl;
        VOLUME_NAME pname( det_name[i] );
        G4VSolid *msolid = new G4Tubs( pname.solid, 
                                       rmin[i], 
                                       rmax[i], 
                                       dz/2., 
                                       sphi,
                                       dphi );
        G4LogicalVolume *log = new G4LogicalVolume( msolid, 
                                                    mfactory->GetMaterial( mat[i] ),
                                                    pname.logical,
                                                    0, 0, 0 );
	//Util::SetColor(log, 120., 0., 0., 0.2);
	//Util::SolidMode(log);
        new G4PVPlacement( 0, pos, log, pname.physical, logical_volume, 0, check_overlap );
    }

}

}
