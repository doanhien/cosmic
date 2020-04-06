// $Id: Digi.cc 94 2010-01-26 13:18:30Z adotti $
/**
 * @file Digi.cc
 * @brief implements Digi detector output class
 *
 * @date 10 Dec 2009
 * @author adotti
 */

#include "ScintDigit.hh"

// -- one more nasty trick for new and delete operator overloading:
G4Allocator<ScintDigit> ScintDigitAllocator;

ScintDigit::ScintDigit(const int& pn,const int& sn) :
  charge(0) ,
  moduleNumber(pn) ,
  stripNumber(sn) ,
  isPrimary(false)
{

}


/*
G4int operator==(const ScintDigit& aDigi) const
{

  moduleNumber = aDigi.moduleNumber;
  stripNumber  = aDigi.stripNumber;
  //planeNumber = aDigi.planeNumber;
}
*/


void ScintDigit::Print()
{
  G4cout<<"ScintDigit: Module= "<<moduleNumber<<" Strip= "<<stripNumber<<" with Charge= "<<charge<<G4endl;
}
