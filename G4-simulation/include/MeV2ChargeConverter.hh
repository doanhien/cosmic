/**
 * @file    MeV2ChargeConverter.hh
 *
 * @date   July 01 2010, 06 march 2015
 * @author adotti, modified by Pico and D. Flechas
 *
 * @brief Converts energy deposit (hits) to charge (digits).
 */


#ifndef MeV2ChargeConverter_h
#define MeV2ChargeConverter_h

#include "G4Types.hh"

/*! \brief MeV to Q converter
 *
 * This class is used to convert the true energy deposits (in MeV), usually from hits
 * to a different units (i.e. charge) this is done to simulate a very simple ADC.
 * You can inherit from this class to implement your own more realistic
 * ADC. This class does not deal with electronic noise.
 * \sa SiDigitizer
 */
class MeV2ChargeConverter
{
public:

  MeV2ChargeConverter(const G4double& value);
  virtual ~MeV2ChargeConverter() {}

  virtual G4double operator()( G4double input_in_MeV ) const;

private:
  G4double MeV2Q;

};

#endif
