/* $Id: BessMagnet.h,v 1.8 2008/03/11 11:01:24 kusumoto Exp $ */
#ifndef _BESS_MAGNET_H
#define _BESS_MAGNET_H

#include "globals.hh"
//#include "TObject.h"
//#include "/data3/cmkuo/root/include/TObject.h"

class EllipticInt {

public:
  // Translation of Algol procedures cel1(kc), cel2(kc,a,b) in
  //  R. BULIRSCH Numerical Calculation of Elliptic Integrals and
  //  Elliptic Functions,  Numer. Math. 7 (1965) 78-90
  // and of Algol procedure cel3(kc,m,p) in
  //  R. BULIRSCH Numerical Calculation of Elliptic Integrals and
  //  Elliptic Functions II.,  Numer. Math. 7 (1965) 353-354
  //
  // Complete elliptic integrals of first, second, and third kind
  // imported to C++ code from CERN MATHLIB C347

  //static Double_t FirstKind ( Double_t akp );
  //static Double_t SecondKind( Double_t akp, Double_t a,   Double_t b );
  //static Double_t ThirdKind ( Double_t akp, Double_t ak2, Double_t p );

  static G4double FirstKind ( G4double akp );
  static G4double SecondKind( G4double akp, G4double a,   G4double b );
  static G4double ThirdKind ( G4double akp, G4double ak2, G4double p );


  // Based on
  //  W.J. Cody, Chebyshev approximations for the complete elliptic
  //  integrals K and E, Math. Comp. l9 (1965) 105-112
  //
  // imported to C++ code from CERN MATHLIB C347

  //static Double_t K( Double_t ak );
  //static Double_t E( Double_t ak );

  static G4double K( G4double ak );
  static G4double E( G4double ak );
};


// Solenoid class

class Solenoid { //: public TObject {

protected:
  //Double_t fRadius;      // radius (mm)
  //Double_t fZlength;     // length (mm)
  //Double_t fTurn;        // number of turns/mm
  //Double_t fCurrent;     // electric current (A)

  G4double fRadius;      // radius (mm)
  G4double fZlength;     // length (mm)
  G4double fTurn;        // number of turns/mm
  G4double fCurrent;     // electric current (A)

public:
  //Solenoid( Double_t r, Double_t l, Double_t t, Double_t c );
  Solenoid( G4double r, G4double l, G4double t, G4double c );
  Solenoid( void );
  ~Solenoid();

  // access functions
  G4double GetRadius ( void ) const { return fRadius;  }
  G4double GetZlength( void ) const { return fZlength; }
  G4double GetTurn   ( void ) const { return fTurn;    }
  G4double GetCurrent( void ) const { return fCurrent; }

  void SetRadius ( G4double r ) { fRadius  = r; }
  void SetZlength( G4double l ) { fZlength = l; }
  void SetTurn   ( G4double t ) { fTurn    = t; }
  void SetCurrent( G4double c ) { fCurrent = c; }
  
  // method
  G4int GetField( G4double r,   G4double z,
		  G4double &br, G4double &bz ) const;

//  ClassDef( Solenoid, 1 )      // solenoid object
};


// BESS-Polar magnet class

class BessMagnet { //: public TObject {

public:
  enum EBdrModes{ kCut, kEnd };

protected:
  G4int     fNlayer;    // number of solenoid layers
  G4int     fNcoil;     // number of solenoids
  Solenoid *fCoil;      // [fNcoil] solenoid array

  G4double  fZl;        // correction magnet position (Left)
  G4double  fZr;        // correction magnet position (Right)

  // magnetic field table
  G4int     fNr;        // number of r-grids
  G4int     fNz;        // number of z-grids
  G4int     fNtable;    // field table size (=fNr*fNz)
  G4double  fDr;        // r-grid size
  G4double  fDz;        // z-grid size
  G4double *fBr;        // [fNtable] Br field table
  G4double *fBz;        // [fNtable] Bz field table

  G4double  fZofs;      // z offset

  G4int     fBdrMode;   // border mode kCut or kEnd

  static BessMagnet *fPtr;

public:
  BessMagnet( void );
  ~BessMagnet();

  static BessMagnet *GetPtr( void ) { return fPtr; }

  Solenoid *GetSolenoid( G4int i ) const;

  G4int GetBdrMode( void ) const { return fBdrMode; }
  void  SetBdrMode( G4int md ) { fBdrMode = md; }

  void  Initialize( void );
  void  MakeTable ( G4int    nr = 100, G4int    nz = 100,
		    G4double dr = 10,  G4double dz = 5 );
  
  G4int GetField( G4double r,   G4double z,
		  G4double &br, G4double &bz, G4int mode = 0 ) const;

  //ClassDef( BessMagnet, 1 )    // BESS-Polar magnet class
};

inline Solenoid *BessMagnet::GetSolenoid( G4int i ) const
{ 
  return ( 0 <= i && i < fNcoil ) ? fCoil+i : 0;
}


#endif

// Local Variables:
// mode:C++
// End:
