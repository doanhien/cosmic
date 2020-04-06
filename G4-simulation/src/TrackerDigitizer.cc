// $Id: Digitizer.cc 94 2010-01-26 13:18:30Z adotti $
/**
 * @file  Digitizer.cc
 * @brief Implements Digitizer class, i.e. the digitization process.
 *
 * @date 10 Dec 2009
 * @author adotti
 */

#include "TrackerDigitizer.hh"
#include "TrackerDigit.hh"
#include "MYTrackerHit.hh"

#include "NoiseGenerator.hh"
#include "MeV2ChargeConverter.hh"
//#include "CrosstalkGenerator.hh"

#include "G4DigiManager.hh"
#include "G4RunManager.hh"
#include "G4VPhysicalVolume.hh"

#include <assert.h>
#include <list>
#include <map>

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


TrackerDigitizer::TrackerDigitizer(G4String aName, G4String hitsCollName_) :
  G4VDigitizerModule(aName) ,
  //digiCollectionName("DigitCollection") ,
  digiCollectionName(aName) ,
  hitsCollName(hitsCollName_) ,

  //Digitization requires several components:
  //1- A pedestal level
  pedestal(5000.) ,

  //2- A noise generator: a simple gaussian noise
  //Noise standard deviation is 1000 e
  //To turn it off put a value <0
  noise( 1000. ) ,

  //3- MeV2Charge converter: converts energy deposits from MeV to Q
  //It needs a parameter: the MeV2Q conversion factor: 3.6 eV/e.
  convert( 1./(3.6*eV) ) ,
  charge(0.)

  /* consider later
  //4- Crosstalk Generator:
  //Crosstalk needs two parameters: number of strips in each module
  //and fraction of charge that leaks.
  //To turn off crosstalk put 0.0
  ////crosstalk( 0.05 , 48 ),
  */
  //UI cmds
  //messenger(this)
{
  collectionName.push_back( digiCollectionName );
  //ResetValues();
}


void TrackerDigitizer::Digitize()
{


  //G4RunManager* runManager = G4RunManager::GetRunManager();
  G4DigiManager* digMan = G4DigiManager::GetDMpointer();

  G4int HitCollID = digMan->GetHitsCollectionID( hitsCollName );//Number associated to hits collection names hitsCollName

  const MYTrackerHitsCollection* hitCollection = static_cast<const MYTrackerHitsCollection*>(digMan->GetHitsCollection(HitCollID));

  TrackerDigitCollection* digiCollection = 0;

  if ( hitCollection )
    {
      G4int hitCol_size = hitCollection->entries();

      digiCollection = new TrackerDigitCollection("TrackerDigitizer",digiCollectionName);

      std::vector<TrackerDigit*> digitsMap(hitCol_size);

      //define each digit
      for (G4int i=0 ; i<hitCol_size; i++ )
	{
          MYTrackerHit* aHit = (*hitCollection)[i];

	  G4int nModule = aHit->GetModule();
	  G4int nStrip = aHit->GetStrip();

	  TrackerDigit* newDigi = new TrackerDigit(nModule, nStrip);       //Create empty digits
	  digitsMap[i] = newDigi;

	  G4double edep = aHit->GetEdep();
	  G4double Charge = convert( edep/MeV );

	  digitsMap[i]->SetCharge(Charge);
	  digitsMap[i]->SetModuleNumber(nModule);
	  digitsMap[i]->SetStripNumber(nStrip);
	  digitsMap[i]->SetGlobalTime(aHit->GetGlobalTime());
	  //digitsMap[i]->SetGlobalTime(aHit->GetGlobalTime());

	  digiCollection->insert(newDigi); 

	  //G4cout << "TrackerDigitizer successfull" << G4endl;
	}

    }

  else  //something really bad happened!!!!
    {
      G4cout <<" TrackerDigitizer::Digitize: Could not found Hit collection with name:" << hitsCollName << G4endl;
    }

  StoreDigiCollection(digiCollection);

}


void TrackerDigitizer::MakeCrosstalk(std::vector< std::vector< TrackerDigit*> >& digitsMap )
{

  G4cout<<"TrackerDigitizer::MakeCrosstalk"<<G4endl;

}


void TrackerDigitizer::ResetValues(void)
{

  SetNoise(0.0);
  SetPedestal(0.0);
  SetCharge(0.0);
  //SetLocalTime(0.0);
  //SetGlobalTime(0.0);
  //SetDetectorName("");
}

