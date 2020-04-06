#include "G4MaterialFactory.h"
#include "material.h"
#include <G4SystemOfUnits.hh>

void G4MaterialFactory::DefineElements( void )
{

    AddElement( E_C,  new G4Element( "C",  "C",  6,  12.01*g/mole ) );
    AddElement( E_H,  new G4Element( "H",  "H",  1,   1.01*g/mole ) );
    AddElement( E_N,  new G4Element( "N",  "N",  7,  14.01*g/mole ) );
    AddElement( E_O,  new G4Element( "O",  "O",  8,  16.01*g/mole ) );
    AddElement( E_NB, new G4Element( "Nb", "Nb", 41, 92.91*g/mole ) );
    AddElement( E_TI, new G4Element( "Ti", "Ti", 22, 47.88*g/mole ) );
    AddElement( E_CU, new G4Element( "Cu", "Cu", 29, 63.55*g/mole ) );
    AddElement( E_AL, new G4Element( "Al", "Al", 13, 26.98*g/mole ) );
    AddElement( E_SI, new G4Element( "Si", "Si", 14, 28.09*g/mole ) );
}

void G4MaterialFactory::DefineMaterials( void )
{
    G4Material *material;

    G4int    wi;
    G4double wd;

    //G4cout << "define materials in G4MaterialFactory" << G4endl;

    material = new G4Material( VACUUM, VACUUM_D, 2 );
    material->AddElement( GetElement( E_N ), .7 );
    material->AddElement( GetElement( E_O ), .3 );
    AddMaterial( M_VACUUM, material );

    material = new G4Material( AIR, AIR_D, 2 );
    material->AddElement( GetElement( E_N ), .7 );
    material->AddElement( GetElement( E_O ), .3 );
    AddMaterial( M_AIR, material );

    material = new G4Material( ALUMINIUM, ALUMINIUM_Z, ALUMINIUM_A, ALUMINIUM_D );
    AddMaterial( M_ALUMINIUM, material );
    
    material = new G4Material( COPPER, COPPER_Z, COPPER_A, COPPER_D );
    AddMaterial( M_COPPER, material );

    material = new G4Material( MYLAR, MYLAR_D, MYLAR_NC );
    material->AddElement( GetElement( E_C ), wi=MYLAR_ATOM_C );
    material->AddElement( GetElement( E_H ), wi=MYLAR_ATOM_H );
    material->AddElement( GetElement( E_O ), wi=MYLAR_ATOM_O );
    AddMaterial( M_MYLAR, material );

    material = new G4Material( MAGCND, MAGCND_D, MAGCND_NC );
    material->AddElement( GetElement( E_NB ), wd=MAGCND_ATOM_NB );
    material->AddElement( GetElement( E_TI ), wd=MAGCND_ATOM_TI );
    material->AddElement( GetElement( E_CU ), wd=MAGCND_ATOM_CU );
    material->AddElement( GetElement( E_AL ), wd=MAGCND_ATOM_AL );
    material->AddElement( GetElement( E_C  ), wd=MAGCND_ATOM_C  );
    material->AddElement( GetElement( E_H  ), wd=MAGCND_ATOM_H  );
    material->AddElement( GetElement( E_O  ), wd=MAGCND_ATOM_O  );
    AddMaterial( M_MAG_CONDUCTOR, material );


    material = new G4Material( ZYLON, ZYLON_D, ZYLON_NC );
    material->AddElement( GetElement( E_C ), wi=ZYLON_ATOM_C );
    material->AddElement( GetElement( E_H ), wi=ZYLON_ATOM_H );
    material->AddElement( GetElement( E_O ), wi=ZYLON_ATOM_O );
    material->AddElement( GetElement( E_N ), wi=ZYLON_ATOM_N );
    AddMaterial( M_ZYLON, material );

    material = new G4Material( ROHACELL, ROHACELL_D, ROHACELL_NC );
    material->AddElement( GetElement( E_C ), wi=ROHACELL_ATOM_C );
    material->AddElement( GetElement( E_H ), wi=ROHACELL_ATOM_H );
    material->AddElement( GetElement( E_O ), wi=ROHACELL_ATOM_O );
    material->AddElement( GetElement( E_N ), wi=ROHACELL_ATOM_N );
    AddMaterial( M_ROHACELL, material );

    material = new G4Material( SCINTI, SCINTI_D, SCINTI_NC );
    material->AddElement( GetElement( E_C ), wi=SCINTI_ATOM_C );
    material->AddElement( GetElement( E_H ), wi=SCINTI_ATOM_H );
    AddMaterial( M_SCINTILATOR, material );

    //material = new G4Material( IDCGAS, IDCGAS_D, IDCGAS_NC, kStateGas );
    material = new G4Material( IDCGAS, IDCGAS_D_P2, IDCGAS_NC, kStateGas );
    material->AddElement( GetElement( E_C ), wi=IDCGAS_ATOM_C );
    material->AddElement( GetElement( E_O ), wi=IDCGAS_ATOM_O );
    AddMaterial( M_IDC_GAS, material );

    material = new G4Material( GFRPG10, GFRPG10_D, GFRPG10_NC );
    material->AddElement( GetElement( E_C  ), wd=GFRPG10_ATOM_C  );
    material->AddElement( GetElement( E_H  ), wd=GFRPG10_ATOM_H  );
    material->AddElement( GetElement( E_O  ), wd=GFRPG10_ATOM_O  );
    material->AddElement( GetElement( E_SI ), wd=GFRPG10_ATOM_Si );
    AddMaterial( M_GFRPG10, material );

    material = new G4Material( GLUE, GLUE_D, GLUE_NC );
    material->AddElement( GetElement( E_C ), wi=GLUE_ATOM_C );
    material->AddElement( GetElement( E_H ), wi=GLUE_ATOM_H );
    material->AddElement( GetElement( E_O ), wi=GLUE_ATOM_O );
    AddMaterial( M_GLUE, material );

    material = new G4Material( AIREXULTEM, AIREXULTEM_D, AIREXULTEM_NC );
    material->AddElement( GetElement( E_C ), wi=AIREXULTEM_ATOM_C );
    material->AddElement( GetElement( E_H ), wi=AIREXULTEM_ATOM_H );
    material->AddElement( GetElement( E_O ), wi=AIREXULTEM_ATOM_O );
    material->AddElement( GetElement( E_N ), wi=AIREXULTEM_ATOM_N );
    AddMaterial( M_AIREXULTEM, material );

    material = new G4Material( CARBONFORM, CARBONFORM_D, CARBONFORM_NC );
    material->AddElement( GetElement( E_C ), wi=CARBONFORM_ATOM_C );
    material->AddElement( GetElement( E_H ), wi=CARBONFORM_ATOM_H );
    material->AddElement( GetElement( E_O ), wi=CARBONFORM_ATOM_O );
    AddMaterial( M_CARBONFORM, material );

    material = new G4Material( GATHERFORM, GATHERFORM_D, GATHERFORM_NC );
    material->AddElement( GetElement( E_C ), wi=GATHERFORM_ATOM_C );
    material->AddElement( GetElement( E_H ), wi=GATHERFORM_ATOM_H );
    AddMaterial( M_GATHERFORM, material );

    material = new G4Material( STYROFORM, STYROFORM_D, STYROFORM_NC );
    material->AddElement( GetElement( E_C ), wi=STYROFORM_ATOM_C );
    material->AddElement( GetElement( E_H ), wi=STYROFORM_ATOM_H );
    material->AddElement( GetElement( E_N ), wi=STYROFORM_ATOM_N );
    material->AddElement( GetElement( E_O ), wi=STYROFORM_ATOM_O );
    AddMaterial( M_STYROFORM, material );

    material = new G4Material( POLYETHYLENE, POLYETHYLENE_D, POLYETHYLENE_NC );
    material->AddElement( GetElement( E_C ), wi=POLYETHYLENE_ATOM_C );
    material->AddElement( GetElement( E_H ), wi=POLYETHYLENE_ATOM_H );
    AddMaterial( M_POLYETHYLENE, material );

    material = new G4Material( AGELM, AGELM_D, AGELM_NC );
    material->AddElement( GetElement( E_SI ), wi=AGELM_ATOM_SI );
    material->AddElement( GetElement( E_O  ), wi=AGELM_ATOM_O  );
    AddMaterial( M_AGEL, material );

    //G4cout << "Done add material" << G4endl;
}
