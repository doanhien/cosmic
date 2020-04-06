/**
 * @file   NoiseGenerator.hh
 *
 * @date   10 Dec 2009
 * @author adotti, modified by Pico and D. Flechas (March 2015)
 *
 * @brief  Brief simulates electronic noise.
 */

#ifndef NoiseGenerator_h
#define NoiseGenerator_h

#include "G4Types.hh"
#include "Randomize.hh"


/*! \brief simulates electronic noise
 * This class simulates gaussian noise around 0
 */
class NoiseGenerator
{
public:

  NoiseGenerator(const G4double& value);

  virtual ~NoiseGenerator() {};

  virtual G4double operator() ();

  inline NoiseGenerator& operator= (const NoiseGenerator& rhs)
  {
    sigma = rhs.sigma;
    return *this;
  }

  //! \brief copy constructor
  NoiseGenerator(const NoiseGenerator& rhs);

private:
  //! Noise standard deviation
  G4double sigma;
  //! Gaussian Random number
  G4RandGauss randomGauss;
};

#endif /* NOISEGENERATOR_HH_ */
