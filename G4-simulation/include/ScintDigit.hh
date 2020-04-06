// $Id: Digi.hh 44 2010-01-18 13:01:57Z adotti $
/**
 * @file   Digi.hh
 *
 * @date   10 Dec 2009
 * @author adotti
 *
 * @brief Defines a digit in the silicon telescope.
 */
#ifndef ScintDigit_HH_
#define ScintDigit_HH_


#include "G4VDigi.hh"
#include "G4TDigiCollection.hh"
#include "G4Allocator.hh"

/*! \brief Definition of a digit
 *
 * This class defines the structure of a digit.
 * A digit is the output of the detector as recorded by the R/O
 * A digit is defined by an identifier: the coutple
 * (module number , strip number) and the measurement,
 * in this case the collected charge.
 * Hits are collected in a collection of hits: \sa DigiCollection
 */
class ScintDigit : public G4VDigi
{
 public:
  //! constructor
  ScintDigit(const int& moduleNum , const int& stripNum);
  //! Empty destructor
  virtual ~ScintDigit() {};
  /*!
   * \brief Add to the digit
   * Add a charge to the digit
   */
  inline void Add( const G4double& aValue ) { charge+= aValue; }
  /*!
   * \brief Print a digit
   *
   * Inherited method. Print some information on the
   * digit
   */
  void Print();
  /*!
   * \brief Draw a digit
   *
   * Inherited method, empty: do not draw digits
   */
  void Draw() {}
  //! \name some simple set & get functions

  inline void     SetLayerNumber( const G4int& aLayer ) { layerNumber = aLayer; }
  inline G4int    GetLayerNumber( ) const { return layerNumber; }
  inline void     SetModuleNumber( const G4int& aModule) { moduleNumber = aModule; }
  inline G4int    GetModuleNumber( ) const { return moduleNumber; }
  inline void     SetStripNumber( const G4int& aStrip) { stripNumber = aStrip; }
  inline G4int    GetStripNumber( ) const { return stripNumber; }
  inline void     SetCharge( const G4double& aCharge ) { charge = aCharge; }
  inline G4double GetCharge( ) const { return charge; }

  //! Equality operator
  /*! 
   * Two digits are the same if they belong to the same detector
   * i.e. layer and Strip number
   * note that no check is done on the charge, since the logic is that
   * each strip can make a single measurement (the hit).
   */
  inline G4int operator==(const ScintDigit& aDigi) const
  { return ( ( moduleNumber == aDigi.GetModuleNumber() ) && ( stripNumber == aDigi.GetStripNumber() ) && layerNumber == aDigi.GetLayerNumber()); }



  //! The new operator
  /*! 
   * This operator creates efficiently a new hit.
   * Overwriting the default new operators allows for the use
   * of the G4Allocator functionalities.
   *
   * See 3.2.4 "General management classes" paragraph in Application Developer G4 manual
   *
   * \note The use of allocators is not mandatory but recommended (to improve performances).
   * You can safely skip this part.
   */
  inline void* operator new(size_t);
  //! Delete operator
  /*! \sa operator new() */
  inline void  operator delete(void* aDigi);

 private:
  //! Collected charge
  G4double charge;
  //! Module number
  G4int moduleNumber;
  //! Strip number
  G4int stripNumber;
  //! Layer Number
  G4int layerNumber;
  //! flag if hit is from primary
  G4bool isPrimary;
};


typedef G4TDigiCollection<ScintDigit> ScintDigitCollection;


/*!
 * \brief Allocator
 *
 * Creating this objects allows for an efficient use of memory.
 * Operators new and delete for the Digi objects have to be
 * defined
 */
extern G4Allocator<ScintDigit> ScintDigitAllocator;

void* ScintDigit::operator new(size_t)
{
  return static_cast<void*>( ScintDigitAllocator.MallocSingle() );
}

void ScintDigit::operator delete(void* aDigi)
{
  ScintDigitAllocator.FreeSingle( static_cast<ScintDigit*>(aDigi) );
}

#endif 
