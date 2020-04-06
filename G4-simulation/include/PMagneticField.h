#ifndef __P_MAGNET_FIELD_H__
#define __P_MAGNET_FIELD_H__

#include "G4MagneticField.hh"
#include "globals.hh"

class BessMagnet;

class PMagneticField : public G4MagneticField {
private:
    BessMagnet *bMagnet;

public:
    PMagneticField( void );
    ~PMagneticField();

    void GetFieldValue( const G4double point[4], G4double *bField ) const;
};

#endif
