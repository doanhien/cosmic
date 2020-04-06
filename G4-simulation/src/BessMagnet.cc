/* $Id: BessMagnet.cc,v 1.8 2008/03/11 11:01:24 kusumoto Exp $ */

//////////////////////////////////////////////////////////////////////////
//
// BessMagnet
//
//  BessMagnet calculates detailed magnetic field at any position
//  based on solenoidal field calculation with elliptic integrals
//
//  imported to C++ codes from TKBPOLAR which is 
//  modified by S.Matsuda
//  written by H.Fuke for BESS-Polar
//  based on the BESS magnet version written by H.Matsunaga
//
//////////////////////////////////////////////////////////////////////////

//#include "/data3/cmkuo/root/include/TMath.h"
#include "BessMagnet.h"

#include "globals.hh"

#include <iostream>
#include <cmath>

using namespace std;


G4double EllipticInt::FirstKind( G4double akp )
{
  // Translation of Algol procedures cel1(kc), cel2(kc,a,b) in
  //  R. BULIRSCH Numerical Calculation of Elliptic Integrals and
  //  Elliptic Functions,  Numer. Math. 7 (1965) 78-90
  // and of Algol procedure cel3(kc,m,p) in
  //  R. BULIRSCH Numerical Calculation of Elliptic Integrals and
  //  Elliptic Functions II.,  Numer. Math. 7 (1965) 353-354
  //
  // Calculates complete elliptic integral of the first kind
  // imported to C++ code from CERN MATHLIB C347

  if ( akp == 0 ) return 0;

  G4double ID  = 16;
  G4double Z1  = 1;
  G4double Z10 = 10;
  G4double HF  = Z1/2;
  //G4double CA  = TMath::Power( Z10, -ID/2 );
  G4double CA  = pow( Z10, -ID/2 );

  //G4double ykp = TMath::Abs( akp );
  G4double ykp = abs( akp );
  G4double xm  = 1;

  for ( ;; ) {
    G4double g = xm;
    xm += ykp;

    //if ( TMath::Abs( g-ykp ) <= CA*g ) break;
    if ( abs( g-ykp ) <= CA*g ) break;
    ykp = sqrt( g*ykp );
    xm *= HF;
  }

  return M_PI/xm;
}

G4double EllipticInt::SecondKind( G4double akp, G4double a, G4double b )
{
  // Translation of Algol procedures cel1(kc), cel2(kc,a,b) in
  //  R. BULIRSCH Numerical Calculation of Elliptic Integrals and
  //  Elliptic Functions,  Numer. Math. 7 (1965) 78-90
  // and of Algol procedure cel3(kc,m,p) in
  //  R. BULIRSCH Numerical Calculation of Elliptic Integrals and
  //  Elliptic Functions II.,  Numer. Math. 7 (1965) 353-354
  //
  // Calculates complete elliptic integral of the second kind
  // imported to C++ code from CERN MATHLIB C347

  if ( akp == 0 ) {
    if ( b == 0 ) return a;
    else          return 0;
  }

  G4double ID  = 16;
  G4double PIQ = M_PI_4;
  G4double Z10 = 10;
  //G4double CA  = TMath::Power( Z10, -ID/2 );
  G4double CA  = pow( Z10, -ID/2 );

  G4double aa = a;
  G4double bb = b;
  G4double xm = 1;
  G4double c  = aa;

  aa += bb;
  //G4double ykp = TMath::Abs( akp );
  G4double ykp = abs( akp );
  G4double xm0;

  for ( ;; ) {
    bb = 2*(c*ykp+bb);
    c = aa;
    xm0 = xm;
    xm += ykp;
    aa = bb/xm+aa;
    //if ( TMath::Abs( xm0-ykp ) <= CA*xm0 ) break;
    if ( abs( xm0-ykp ) <= CA*xm0 ) break;
    ykp = 2*sqrt( ykp*xm0 );
  }
  
  return PIQ*aa/xm;
}

G4double EllipticInt::ThirdKind( G4double akp, G4double ak2, G4double p )
{
  // Translation of Algol procedures cel1(kc), cel2(kc,a,b) in
  //  R. BULIRSCH Numerical Calculation of Elliptic Integrals and
  //  Elliptic Functions,  Numer. Math. 7 (1965) 78-90
  // and of Algol procedure cel3(kc,m,p) in
  //  R. BULIRSCH Numerical Calculation of Elliptic Integrals and
  //  Elliptic Functions II.,  Numer. Math. 7 (1965) 353-354
  //
  // Calculates complete elliptic integral of the third kind
  // imported to C++ code from CERN MATHLIB C347

  if ( akp*p == 0 ) return 0;

  G4double ID  = 16;
  G4double PIH = M_PI_2;
  G4double Z10 = 10;
  //G4double CA  = TMath::Power( Z10, -ID/2 );
  G4double CA  = pow( Z10, -ID/2 );

  //G4double ykp = TMath::Abs( akp );
  G4double ykp = abs( akp );
  G4double e   = ykp;
  G4double am0 = 1;
  G4double pp  = p;
  G4double c, d, f, g;

  if ( pp > 0 ) {
    c  = 1;
    pp = sqrt( pp );
    d  = 1/pp;
  }else {
    g  = 1-pp;
    f  = ykp*ykp-pp;
    pp = sqrt( f/g );
    d  = -ak2/(g*pp);
    c  = 0;
  }

  for ( ;; ) {
    f   = c;
    c  += d/pp;
    g   = e/pp;
    d   = 2*(f*g+d);
    pp += g;
    g   = am0;
    am0 = ykp+am0;
    //if ( TMath::Abs( g-ykp ) <= CA*g ) break;
    if ( abs( g-ykp ) <= CA*g ) break;

    ykp = 2*sqrt( e );
    e = ykp*am0;
  }

  return PIH*(c*am0+d)/(am0*(am0+pp));
}

G4double EllipticInt::K( G4double ak )
{
  // Based on
  //  W.J. Cody, Chebyshev approximations for the complete elliptic
  //  integral K, Math. Comp. l9 (1965) 105-112
  //
  // imported to C++ code from CERN MATHLIB C347

  G4double u = ak*ak;
  if ( u >= 1 ) return 0;
  
  G4double Z1 = 1;
  G4double HF = Z1/2;
  G4double C  = 1.3862943611198906E0;

  G4double dataA[8] = { 6.4998443329390180E-4, 6.6905509906897936E-3,
			1.3855601247156560E-2, 1.1208918554644092E-2,
			9.6587579861753113E-3, 1.4978988178704629E-2,
			3.0885573486752694E-2, 9.6573590797589018E-2 };
  G4double dataB[8] = { 1.5049181783601883E-4, 3.1831309927862886E-3,
			1.4105380776158048E-2, 2.7189861116788250E-2,
			3.7068398934155422E-2, 4.8818058565403952E-2,
			7.0312426464627361E-2, 1.2499999994117923E-1 };
  
  G4double y = 1-u;
  G4double pa = 0, pb = 0;

  for ( G4int i = 0; i <= 7; i++ ) {
    pa = pa*y+dataA[i];
    pb = pb*y+dataB[i];
  }

  return C+pa*y-log( y )*( HF+pb*y );
}

G4double EllipticInt::E( G4double ak )
{
  // Based on
  //  W.J. Cody, Chebyshev approximations for the complete elliptic
  //  integral E, Math. Comp. l9 (1965) 105-112
  //
  // imported to C++ code from CERN MATHLIB C347

  G4double u = ak*ak;
  if ( u >= 1 ) return 0;

  G4double dataP[8] = { 7.0980964089987229E-4, 7.3356164974290365E-3,
			1.5377102528552019E-2, 1.3034146073731432E-2,
			1.2510592410844644E-2, 2.1876220647186198E-2,
			5.6805657874695358E-2, 4.4314718112155806E-1 };
  G4double dataQ[8] = { 1.6427210797048025E-4, 3.4838679435896492E-3,
			1.5525129948040721E-2, 3.0302747728412848E-2,
			4.2382807456947900E-2, 5.8582839536559024E-2,
			9.3749920249680113E-2, 2.4999999993617622E-1 };
  
  G4double y = 1-u;
  G4double pa = 0, pb = 0;

  for ( G4int i = 0; i <= 7; i++ ) {
    pa = pa*y+dataP[i];
    pb = pb*y+dataQ[i];
  }

  return 1+(pa-log( y )*pb)*y;
}


//ClassImp( Solenoid )

Solenoid::Solenoid( G4double r, G4double l, G4double t, G4double c )
  : fRadius( r ), fZlength( l ), fTurn( t ), fCurrent( c )
{
}

Solenoid::Solenoid( void )
  : fRadius( 0 ), fZlength( 0 ), fTurn( 0 ), fCurrent( 0 )
{
}

Solenoid::~Solenoid()
{
}

G4int Solenoid::GetField( G4double r,   G4double z,
			  G4double &br, G4double &bz ) const
{
  br = bz = 0;
  if ( fRadius <= 0 ) return -1;

  G4double fctr = 4.0*fTurn*fCurrent*1.0E-4;

  G4double dr = fRadius-r;
  G4double sr = fRadius+r;
  G4double rr = dr/sr;
  G4double  p = rr*rr;

  for ( int i = 0; i < 2; i++ ) {
    G4double sgn  = ( i == 0 ) ? 1 : -1;
    G4double zz   = z+sgn*fZlength/2;
    G4double zrzr = zz*zz+sr*sr; 
    //G4double zr   = TMath::Sqrt( zrzr );
    G4double zr   = sqrt( zrzr );
    G4double akak = 4.*r*fRadius/zrzr; 
    //G4double ak   = TMath::Sqrt( akak ); 
    //G4double akp  = TMath::Sqrt( 1-akak );
    G4double ak   = sqrt( akak ); 
    G4double akp  = sqrt( 1-akak );
    
    G4double elik = EllipticInt::K( ak );
    G4double elie = EllipticInt::E( ak );
    G4double eli3 = EllipticInt::ThirdKind( akp, akak, p );
    
    if ( r > 0 ) {
      br += sgn*( elik*(2/akak-1)-elie*2/akak )/zr*fRadius*fctr;
      bz += sgn*( elik+rr*eli3 )*zz/zr*fctr/2;
    }else
      //bz += sgn*zz/TMath::Sqrt( fRadius*fRadius+zz*zz )*fctr*M_PI_2;
      bz += sgn*zz/sqrt( fRadius*fRadius+zz*zz )*fctr*M_PI_2;
  }

  //G4cout << "Magnetic field in Z direction: " << bz << "\t in rho: " << br << "\t in radius=" << fRadius << G4endl;

  return 0;
}


//ClassImp( BessMagnet )

BessMagnet *BessMagnet::fPtr = 0;

BessMagnet::BessMagnet( void )
{
  Initialize();

  fNtable = 0;
  fBr = fBz = 0;
  fZofs = 0;

  fBdrMode = kEnd;
  fPtr = this;
}

BessMagnet::~BessMagnet()
{
  delete [] fCoil;
  delete [] fBr;
  delete [] fBz;
}

void BessMagnet::Initialize( void )
{
  // electric current (A)
  // in case of 0.8T: 383A,  in case of 1.0T:  479A
  // actual operation in the 2004 flight (0.8T):  380.3A <- 383.0A?
  G4double curr = 383.0; //official
  //G4double curr = 380.3;
  //G4double curr = 5000.;
  
  G4double rm[2] = { 449.02, 450.83 }; // radius of the main coil (mm)
  G4double rc[2] = { 449.02, 450.98 }; // radius of the cor. coil (mm)
  G4double lm    = 500.85*2;           // length of the main coil (mm)
  G4double lcl   = 699.30-500.85;      // length of the cor. coil (mm)
  G4double lcr   = 699.83-500.85;      // length of the cor. coil (mm)
  G4double tm[2] = { 1113.0, 834.0 };  // #turns of the main coil
  G4double tc[2] = {  220.5, 220.5 };  // #turns of the cor. coil

  fNlayer = 2;
  fNcoil  = fNlayer*3;

  fCoil = new Solenoid[fNcoil];

  for ( G4int i = 0; i < fNlayer; i++ ) {
    // main coil
    fCoil[i*3].SetRadius ( rm[i] );
    fCoil[i*3].SetTurn   ( tm[i]/lm );
    fCoil[i*3].SetCurrent( curr );
    fCoil[i*3].SetZlength( lm );

    // left correction coil
    fCoil[i*3+1].SetRadius ( rc[i] );
    fCoil[i*3+1].SetTurn   ( tc[i]/lcl );
    fCoil[i*3+1].SetCurrent( curr );
    fCoil[i*3+1].SetZlength( lcl );

    // right correction coil
    fCoil[i*3+2].SetRadius ( rc[i] );
    fCoil[i*3+2].SetTurn   ( tc[i]/lcr );
    fCoil[i*3+2].SetCurrent( curr );
    fCoil[i*3+2].SetZlength( lcr );
  }

  // center position of correction coils
  fZl = -(lm+lcl)/2;
  fZr =  (lm+lcr)/2;
}

void BessMagnet::MakeTable( G4int nr, G4int nz, G4double dr, G4double dz )
{
  cout << "Creating real B field table ... ";
  cout.flush();

  fNr = nr;
  fNz = nz;
  fDr = dr;
  fDz = dz;

  fBr = new G4double[fNr*fNz];
  fBz = new G4double[fNr*fNz];

  for ( G4int i = 0; i < fNr; i++ )
    for ( G4int j = 0; j < fNz; j++ )
      GetField( fDr*i, fDz*j, fBr[i*fNz+j], fBz[i*fNz+j] );

  fNtable = fNr*fNz;

  cout << fNtable << " data." << endl;
}

G4int BessMagnet::GetField( G4double r,   G4double z,
			    G4double &br, G4double &bz, G4int mode ) const
{

  //cout << "Getting field value" << endl;
  br = bz = 0;

  z -= fZofs;

  if ( fNtable > 0 && fDr > 0 && fDz > 0 && mode == 0 ) {
    //G4int i = (G4int)TMath::Floor( TMath::Abs( r )/fDr );
    //G4int j = (G4int)TMath::Floor( TMath::Abs( z )/fDz );
    G4int i = (G4int)floor( abs( r )/fDr );
    G4int j = (G4int)floor( abs( z )/fDz );
    if ( i+1 >= fNr || j+1 >= fNz ) {
      if ( fBdrMode == kCut ) return 2;
      if ( i+1 >= fNr ) i = fNr-1;
      if ( j+1 >= fNz ) j = fNz-1;
    }

    // 2-dimensional interpolation
    //G4double er   = TMath::Abs( r )-i*fDr;
    //G4double ez   = TMath::Abs( z )-j*fDz;
    G4double er   = abs( r )-i*fDr;
    G4double ez   = abs( z )-j*fDz;
    G4double br00 = fBr[ i   *fNz+j  ], bz00 = fBz[ i   *fNz+j  ];
    G4double br01 = fBr[(i+1)*fNz+j  ], bz01 = fBz[(i+1)*fNz+j  ];
    G4double br10 = fBr[ i   *fNz+j+1], bz10 = fBz[ i   *fNz+j+1];
    G4double br11 = fBr[(i+1)*fNz+j+1], bz11 = fBz[(i+1)*fNz+j+1];
    G4double br0  = br00+(br01-br00)/fDr*er;
    G4double bz0  = bz00+(bz01-bz00)/fDr*er;
    G4double br1  = br10+(br11-br10)/fDr*er;
    G4double bz1  = bz10+(bz11-bz10)/fDr*er;
    br = br0+(br1-br0)/fDz*ez;
    bz = bz0+(bz1-bz0)/fDz*ez;

    return 1;
  }

  G4double bbr, bbz;

  for ( G4int i = 0; i < fNlayer; i++ ) {
    // main coil
    fCoil[i*3].GetField( r, z, bbr, bbz );
    br += bbr; bz += bbz;

    // left correction coil
    fCoil[i*3+1].GetField( r, z-fZl, bbr, bbz );
    br += bbr; bz += bbz;

    // right correction coil
    fCoil[i*3+2].GetField( r, z-fZr, bbr, bbz );
    br += bbr; bz += bbz;
  }

  //G4cout << "correction magnetic field in bz: " << bz << G4endl;

  return 0;
}
