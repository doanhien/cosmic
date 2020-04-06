// $Id: Digi.cc 94 2010-01-26 13:18:30Z adotti $
/**
 * @file Digi.cc
 * @brief implements Digi detector output class
 *
 * @date 10 Dec 2009
 * @author adotti
 */

#include "TrackerDigit.hh"

// -- one more nasty trick for new and delete operator overloading:
G4Allocator<TrackerDigit> TrackerDigitAllocator;

TrackerDigit::TrackerDigit(const int& pn,const int& sn) :
  charge(0) ,
  moduleNumber(pn) ,
  stripNumber(sn) ,
  isPrimary(false),
  localTime(0.),
  globalTime(0.)
{

}

/*
G4int operator==(const TrackerDigit& aDigi) const 
{

  moduleNumber = aDigi.moduleNumber;
  stripNumber  = aDigi.stripNumber;
  //planeNumber = aDigi.planeNumber;

}
*/

void TrackerDigit::Print()
{
  G4cout<<"TrackerDigit: Module= "<<moduleNumber<<" Strip= "<<stripNumber<<" with Charge= "<<charge<<G4endl;
}
