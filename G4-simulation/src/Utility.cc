#include "Utility.h"

#include "G4LogicalVolume.hh"
#include "G4Color.hh"
#include "G4VisAttributes.hh"

void Util::SetColor( G4LogicalVolume *log, G4int r, G4int g, G4int b, G4double alpha )
{
    if( !log ) return;
    if( r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255 ) return;
    if( alpha < 0 || alpha > 1 ) return;

    G4Color col( (G4double)r/255., (G4double)g/255., (G4double)b/255., alpha );
    G4VisAttributes *vis = const_cast<G4VisAttributes*>( log->GetVisAttributes() ); 
    if( !vis )
    {
        G4VisAttributes newvis;
        newvis.SetColor( col );
        log->SetVisAttributes( newvis );
    }
    else
        vis->SetColor( col );
}

void Util::SolidMode( G4LogicalVolume *log )
{
    if( !log ) return;

    G4VisAttributes *vis = const_cast<G4VisAttributes*>( log->GetVisAttributes() ); 
    if( !vis )
    {
        G4VisAttributes newvis;
        newvis.SetForceSolid( true );
        log->SetVisAttributes( newvis );
    }
    else vis->SetForceSolid( true );
}

void Util::WireMode( G4LogicalVolume *log )
{
    if( !log ) return;

    G4VisAttributes *vis = const_cast<G4VisAttributes*>( log->GetVisAttributes() ); 
    if( !vis )
    {
        G4VisAttributes newvis;
        newvis.SetForceWireframe( true );
        log->SetVisAttributes( newvis );
    }
    else vis->SetForceWireframe( true );
}

void Util::Invisible( G4LogicalVolume *log )
{
    if( !log ) return;

    G4VisAttributes *vis = const_cast<G4VisAttributes*>( log->GetVisAttributes() ); 
    if( !vis )
    {
        G4VisAttributes newvis;
        newvis.SetVisibility( false );
        log->SetVisAttributes( newvis );
    }
    else
        vis->SetVisibility( false );
}

void Util::Visible( G4LogicalVolume *log )
{
    if( !log ) return;

    G4VisAttributes *vis = const_cast<G4VisAttributes*>( log->GetVisAttributes() ); 
    if( !vis )
    {
        G4VisAttributes newvis;
        newvis.SetVisibility( true );
        log->SetVisAttributes( newvis );
    }
    else
        vis->SetVisibility( true );
}
