#include "MeV2ChargeConverter.hh"

MeV2ChargeConverter::MeV2ChargeConverter(const G4double& value) : MeV2Q(value)
{
}

G4double MeV2ChargeConverter::operator()( G4double input ) const
{
  /* Very simple!
   * You can complicate it as much as you want =)
   */
  return input*MeV2Q;
}
