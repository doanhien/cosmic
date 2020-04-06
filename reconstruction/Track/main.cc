#include <iostream>
#include <string>

#include <TFile.h>
#include <TTree.h>
#include <TGraphErrors.h>
#include <TMath.h>
#include <TSystem.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TAxis.h>

#include "TrackerHitSimple.h"
#include "SectorSystemTracker.h"
#include "TrackerSectorConnector.h"
#include "SegmentBuilder.h"

#include "Crit2_RZRatio.h"
#include "Crit2_DeltaPhi.h"
#include "Crit2_DeltaRho.h"
#include "Crit2_DeltaY.h"

#include "Crit3_2DAngle.h"

#include "Crit4_DistOfCircleCenters.h"
#include "Crit4_2DAngleChange.h"


//#include "Fitter.h"
#include "RiemannFit.h"

using namespace std;

namespace {
  void PrintUsage() {
    cerr << " Usage: " << endl;
    cerr << " TrackFinding [-f inputfile]" << endl;
    cerr << endl;
  }
}


Double_t myFunc(Double_t *x, Double_t *par)
{

  Double_t xx = x[0];
  Double_t fx = -TMath::Sqrt(par[0]*par[0] - (xx-par[1])*(xx-par[1]))+par[2];
  return fx;

}



int main(int argc, char** argv)
{

  if (argc > 3) {
    PrintUsage();
    return 1;
  }

  string inputfile;

  if ( string(argv[1]) == "-f" ) inputfile = argv[2];
  else {
    PrintUsage();
    return 1;
  }

  gSystem->Load("libTree");

  TFile *file = new TFile(inputfile.c_str(), "read");
  TTree *intree = (TTree*) file->Get("ntuple");

  Int_t nHits_Layer1;
  vector<double> *Sensor_digi_layer1 = 0;
  vector<double> *Strip_digi_layer1 = 0;
  vector<double> *Edep_digi_layer1 = 0;
  vector<double> *Edep_layer1 = 0;

  Int_t nHits_Layer2;
  vector<double> *Sensor_digi_layer2 = 0;
  vector<double> *Strip_digi_layer2 = 0;
  vector<double> *Edep_digi_layer2 = 0;
  vector<double> *Edep_layer2 = 0;

  Int_t nHits_Layer3;
  vector<double> *Sensor_digi_layer3 = 0;
  vector<double> *Strip_digi_layer3 = 0;
  vector<double> *Edep_digi_layer3 = 0;
  vector<double> *Edep_layer3 = 0;

  Int_t nHits_Layer4;
  vector<double> *Sensor_digi_layer4 = 0;
  vector<double> *Strip_digi_layer4 = 0;
  vector<double> *Edep_digi_layer4 = 0;
  vector<double> *Edep_layer4 = 0;

  Int_t nHits_Layer5;
  vector<double> *Sensor_digi_layer5 = 0;
  vector<double> *Strip_digi_layer5 = 0;
  vector<double> *Edep_digi_layer5 = 0;
  vector<double> *Edep_layer5 = 0;

  Int_t EventID;


  intree->ResetBranchAddresses();
  intree->SetBranchAddress("nHits_Layer1",        &nHits_Layer1);
  intree->SetBranchAddress("Sensor_digi_layer1",  &Sensor_digi_layer1);
  intree->SetBranchAddress("Strip_digi_layer1",   &Strip_digi_layer1);
  intree->SetBranchAddress("Edep_digi_layer1",    &Edep_digi_layer1);
  intree->SetBranchAddress("Edep_layer1",         &Edep_layer1);

  intree->SetBranchAddress("nHits_Layer2",        &nHits_Layer2);
  intree->SetBranchAddress("Sensor_digi_layer2",  &Sensor_digi_layer2);
  intree->SetBranchAddress("Strip_digi_layer2",   &Strip_digi_layer2);
  intree->SetBranchAddress("Edep_digi_layer2",    &Edep_digi_layer2);
  intree->SetBranchAddress("Edep_layer2",         &Edep_layer2);

  intree->SetBranchAddress("nHits_Layer3",        &nHits_Layer3);
  intree->SetBranchAddress("Sensor_digi_layer3",  &Sensor_digi_layer3);
  intree->SetBranchAddress("Strip_digi_layer3",   &Strip_digi_layer3);
  intree->SetBranchAddress("Edep_digi_layer3",    &Edep_digi_layer3);
  intree->SetBranchAddress("Edep_layer3",         &Edep_layer3);

  intree->SetBranchAddress("nHits_Layer4",        &nHits_Layer4);
  intree->SetBranchAddress("Sensor_digi_layer4",  &Sensor_digi_layer4);
  intree->SetBranchAddress("Strip_digi_layer4",   &Strip_digi_layer4);
  intree->SetBranchAddress("Edep_digi_layer4",    &Edep_digi_layer4);
  intree->SetBranchAddress("Edep_layer4",         &Edep_layer4);

  intree->SetBranchAddress("nHits_Layer5",        &nHits_Layer5);
  intree->SetBranchAddress("Sensor_digi_layer5",  &Sensor_digi_layer5);
  intree->SetBranchAddress("Strip_digi_layer5",   &Strip_digi_layer5);
  intree->SetBranchAddress("Edep_digi_layer5",    &Edep_digi_layer5);
  intree->SetBranchAddress("Edep_layer5",         &Edep_layer5);

  intree->SetBranchAddress("EventID",             &EventID);

  //number of events
  Long64_t totEv = intree->GetEntriesFast();

  //for (Long64_t iev = 0; iev < totEv; iev++) {
  for (Long64_t iev = 24; iev < 25; iev++) {

    intree->GetEntry(iev);
    if(intree->GetEntry(iev)<=0) break;
    cout << "Processing Event: " << EventID << " th" << endl;

    //if (iev%20000 == 0) cout << "processing event: " << iev+1 << " th of " << totEv << " events" << endl;

    //-------------------------------------------//
    //for track finding
    //-------------------------------------------//

    //first declare class of sector system
    unsigned nLayers = 5;
    unsigned nModules = 20; //number of cell in z-axis
    unsigned nSensors = 332; //number of strip in x-axis, 332 - 1st layer

    //because nDivisions in X-axis are different for layers
    //we use different sector system
    SectorSystemTracker *SectorSystem_layer1 = new SectorSystemTracker(nLayers, nModules, nSensors);

    //nSensors = 421;
    SectorSystemTracker *SectorSystem_layer2 = new SectorSystemTracker(nLayers, nModules, nSensors);

    //nSensors = 447;
    SectorSystemTracker *SectorSystem_layer3 = new SectorSystemTracker(nLayers, nModules, nSensors);

    //nSensors = 421;
    SectorSystemTracker *SectorSystem_layer4 = new SectorSystemTracker(nLayers, nModules, nSensors);

    //nSensors = 332;
    SectorSystemTracker *SectorSystem_layer5 = new SectorSystemTracker(nLayers, nModules, nSensors);

    //std::cout << "done define SectorSystemTracker!" << std::endl;

    //get position and energy deposit
    //if many hits in same sensor and strip --> 1 hit with summed deposited energy
    //one layer: 20 sensor and >= 332 strip numbered from 0 to >=332
    //--> only check strip value

    std::map<int, std::vector<double>> map_strip_energy_layer1;
    std::map<int, std::vector<double>> map_strip_energy_layer2;
    std::map<int, std::vector<double>> map_strip_energy_layer3;
    std::map<int, std::vector<double>> map_strip_energy_layer4;
    std::map<int, std::vector<double>> map_strip_energy_layer5;

    std::map<int, std::vector<double>> map_sensor_energy_layer1;
    std::map<int, std::vector<double>> map_sensor_energy_layer2;
    std::map<int, std::vector<double>> map_sensor_energy_layer3;
    std::map<int, std::vector<double>> map_sensor_energy_layer4;
    std::map<int, std::vector<double>> map_sensor_energy_layer5;

    std::map<int, std::vector<int>> map_sensor_strip_layer1;
    std::map<int, std::vector<int>> map_sensor_strip_layer2;
    std::map<int, std::vector<int>> map_sensor_strip_layer3;
    std::map<int, std::vector<int>> map_sensor_strip_layer4;
    std::map<int, std::vector<int>> map_sensor_strip_layer5;

    for (int i = 0; i < nHits_Layer1; i++ ) {
      int strip = (*Strip_digi_layer1)[i];
      int sensor = (*Sensor_digi_layer1)[i];

      map_strip_energy_layer1[strip].push_back((*Edep_digi_layer1)[i]);
      map_sensor_energy_layer1[sensor].push_back((*Edep_digi_layer1)[i]);
      map_sensor_strip_layer1[strip].push_back(sensor);
    }

    for (int i = 0; i < nHits_Layer2; i++ ) {
      int strip = (*Strip_digi_layer2)[i];
      int sensor = (*Sensor_digi_layer2)[i];

      map_strip_energy_layer2[strip].push_back((*Edep_digi_layer2)[i]);
      map_sensor_energy_layer2[sensor].push_back((*Edep_digi_layer2)[i]);
      map_sensor_strip_layer2[strip].push_back(sensor);
    }

    for (int i = 0; i < nHits_Layer3; i++ ) {
      int strip = (*Strip_digi_layer3)[i];
      int sensor = (*Sensor_digi_layer3)[i];

      map_strip_energy_layer3[strip].push_back((*Edep_digi_layer3)[i]);
      map_sensor_energy_layer3[sensor].push_back((*Edep_digi_layer3)[i]);
      map_sensor_strip_layer3[strip].push_back(sensor);

    }

    for (int i = 0; i < nHits_Layer4; i++ ) {
      int strip = (*Strip_digi_layer4)[i];
      int sensor = (*Sensor_digi_layer4)[i];

      map_strip_energy_layer4[strip].push_back((*Edep_digi_layer4)[i]);
      map_sensor_energy_layer4[sensor].push_back((*Edep_digi_layer4)[i]);
      map_sensor_strip_layer4[strip].push_back(sensor);

    }

    for (int i = 0; i < nHits_Layer5; i++ ) {
      int strip = (*Strip_digi_layer5)[i];
      int sensor = (*Sensor_digi_layer5)[i];

      map_strip_energy_layer5[strip].push_back((*Edep_digi_layer5)[i]);
      map_sensor_energy_layer5[sensor].push_back((*Edep_digi_layer5)[i]);
      map_sensor_strip_layer5[strip].push_back(sensor);

    }


    //get all position of hits and put them into a vector
    // position in x,y,z are calculated as middle point of sensor and strip

    vector<double> Xpos_allLayer;
    vector<double> Ypos_allLayer;
    vector<double> Zpos_allLayer;
    vector<double> Edep_allLayer;

    Xpos_allLayer.clear();
    Ypos_allLayer.clear();
    Zpos_allLayer.clear();


    std::map< int , std::vector< double > >::iterator itStripEne;
    std::map< int , std::vector< double > >::iterator itSensorEne;
    std::map< int , std::vector< int > >::iterator itStripSensor;

    int nhits_layer1_ = 0;
    //first- layer1
    for (  itStripSensor = map_sensor_strip_layer1.begin(); itStripSensor!= map_sensor_strip_layer1.end(); itStripSensor++ ){

      int strip = itStripSensor->first;
      std::vector<int> sensor = itStripSensor->second;

      double zpos;
      if (sensor[0] <= 9) zpos = -35.*(19 - 2*sensor[0]);
      else zpos = 35.* (2*sensor[0] - 19);

      double xpos;
      if (strip <=165) xpos = 2.*strip - 331.;
      else xpos = 331. - 2.*strip;

      Xpos_allLayer.push_back(xpos);
      Ypos_allLayer.push_back(300.);
      Zpos_allLayer.push_back(zpos);

      nhits_layer1_++;

    }

    int nhits_layer2_ = 0;
    for (  itStripSensor = map_sensor_strip_layer2.begin(); itStripSensor!= map_sensor_strip_layer2.end(); itStripSensor++ ){

      int strip = itStripSensor->first;
      std::vector<int> sensor = itStripSensor->second;

      double zpos;
      if (sensor[0] <= 9) zpos = -35.*(19 - 2*sensor[0]);
      else zpos = 35.* (2*sensor[0] - 19);

      double xpos;
      if (strip <=210) xpos = 2.*strip - 420.;
      else xpos = 420. - 2.*strip;

      Xpos_allLayer.push_back(xpos);
      Ypos_allLayer.push_back(150.);
      Zpos_allLayer.push_back(zpos);

      nhits_layer2_++;
    }

    int nhits_layer3_ = 0;
    for (  itStripSensor = map_sensor_strip_layer3.begin(); itStripSensor!= map_sensor_strip_layer3.end(); itStripSensor++ ){

      int strip = itStripSensor->first;
      std::vector<int> sensor = itStripSensor->second;

      double zpos;
      if (sensor[0] <= 9) zpos = -35.*(19 - 2*sensor[0]);
      else zpos = 35.* (2*sensor[0] - 19);

      double xpos;
      if (strip <=223) xpos = 2.*strip - 446.;
      else xpos = 446. - 2.*strip;

      Xpos_allLayer.push_back(xpos);
      Ypos_allLayer.push_back(0.);
      Zpos_allLayer.push_back(zpos);

      nhits_layer3_++;

    }


    int nhits_layer4_ = 0;
    for (  itStripSensor = map_sensor_strip_layer4.begin(); itStripSensor!= map_sensor_strip_layer4.end(); itStripSensor++ ){

      int strip = itStripSensor->first;
      std::vector<int> sensor = itStripSensor->second;

      double zpos;
      if (sensor[0] <= 9) zpos = -35.*(19 - 2*sensor[0]);
      else zpos = 35.* (2*sensor[0] - 19);

      double xpos;
      if (strip <=210) xpos = 2.*strip - 420.;
      else xpos = 420. - 2.*strip;   

      Xpos_allLayer.push_back(xpos);
      Ypos_allLayer.push_back(-150.);
      Zpos_allLayer.push_back(zpos);

      nhits_layer4_++;

    }

    int nhits_layer5_ = 0;
    for (  itStripSensor = map_sensor_strip_layer5.begin(); itStripSensor!= map_sensor_strip_layer5.end(); itStripSensor++ ){

      int strip = itStripSensor->first;
      std::vector<int> sensor = itStripSensor->second;

      double zpos;
      if (sensor[0] <= 9) zpos = -35.*(19 - 2*sensor[0]);
      else zpos = 35.* (2*sensor[0] - 19);

      double xpos;
      if (strip <=165) xpos = 2.*strip - 331.;
      else xpos = 331. - 2.*strip;

      Xpos_allLayer.push_back(xpos);
      Ypos_allLayer.push_back(-300.);
      Zpos_allLayer.push_back(zpos);

      nhits_layer5_++;

    }


    //get energy deposit in strip
    //layer1 of tracker
    for ( itStripEne = map_strip_energy_layer1.begin(); itStripEne!=map_strip_energy_layer1.end(); itStripEne++ ){

      int strip = itStripEne->first;
      std::vector <double> energy = itStripEne->second;

      double TotEn = 0.;

      for ( int ie = 0; ie < energy.size(); ie++) {
        TotEn += energy[ie];
      }

      Edep_allLayer.push_back(TotEn);
    }

    //layer2 of tracker
    for ( itStripEne = map_strip_energy_layer2.begin(); itStripEne!=map_strip_energy_layer2.end(); itStripEne++ ){

      int strip = itStripEne->first;
      std::vector <double> energy = itStripEne->second;

      double TotEn = 0.;

      for ( int ie = 0; ie < energy.size(); ie++) {
        TotEn += energy[ie];
      }

      Edep_allLayer.push_back(TotEn);
    }


    //layer3 of tracker
    for ( itStripEne = map_strip_energy_layer3.begin(); itStripEne!=map_strip_energy_layer3.end(); itStripEne++ ){

      int strip = itStripEne->first;
      std::vector <double> energy = itStripEne->second;

      double TotEn = 0.;

      for ( int ie = 0; ie < energy.size(); ie++) {
        TotEn += energy[ie];
      }

      Edep_allLayer.push_back(TotEn);
    }

    //layer4 of tracker
    for ( itStripEne = map_strip_energy_layer4.begin(); itStripEne!=map_strip_energy_layer4.end(); itStripEne++ ){

      int strip = itStripEne->first;
      std::vector <double> energy = itStripEne->second;

      double TotEn = 0.;

      for ( int ie = 0; ie < energy.size(); ie++) {
        TotEn += energy[ie];
      }

      Edep_allLayer.push_back(TotEn);
    }


    //layer5 of tracker
    for ( itStripEne = map_strip_energy_layer5.begin(); itStripEne!=map_strip_energy_layer5.end(); itStripEne++ ){

      int strip = itStripEne->first;
      std::vector <double> energy = itStripEne->second;

      double TotEn = 0.;

      for ( int ie = 0; ie < energy.size(); ie++) {
        TotEn += energy[ie];
      }

      Edep_allLayer.push_back(TotEn);
    }

    //for (int i = 0; i < Zpos_allLayer.size(); i++) {
    //cout << "\n z position: " << Zpos_allLayer[i] << endl;
    //}

    vector<int> vLayer;
    vLayer.clear();
    vLayer.push_back(nhits_layer1_);
    vLayer.push_back(nhits_layer2_);
    vLayer.push_back(nhits_layer3_);
    vLayer.push_back(nhits_layer4_);
    vLayer.push_back(nhits_layer5_);


    //std::cout << "starting get mapping sector and hit!" << std::endl;

    std::map<int, std::vector<IHit*>> map_sector_Hit;

    /************* loop on each layer ******************/
    /************* to get sector and hit simple ********/
    /***************************************************/

    //declare track hit simples - which constain position x,y,z, layer, module, sensor and sector system
    std::vector<TrackerHitSimple*> vector_TrackerHit;
    vector<int> vsector;

    int nHits_Layers_ = 0;

    for (int i = 0; i < vLayer.size(); i++) {

      //std::cout << "Layer number " << i+1 << std::endl;

      vector_TrackerHit.clear();
      vsector.clear();

      for (int j = 0; j < vLayer[i]; j++) {

	double x = Xpos_allLayer[nHits_Layers_ + j];
	double y = Ypos_allLayer[nHits_Layers_ + j];
	double z = Zpos_allLayer[nHits_Layers_ + j];    

	//cout << "z position: " << z << " of layer: " << (nHits_Layers_ + j) << endl;
	cout << "x position: " << x << " of layer: " << (nHits_Layers_ + j) << endl;
	//cout << "y position: " << y << " of layer: " << (nHits_Layers_ + j) << endl;

	unsigned layer = (unsigned) i;

	//get module and sensor from sector system
	SectorSystemTracker *SectorSystem ;
	if (i == 0) SectorSystem = SectorSystem_layer1;
	else if ( i == 1) SectorSystem = SectorSystem_layer2;
	else if ( i == 2) SectorSystem = SectorSystem_layer3;
	else if ( i == 3) SectorSystem = SectorSystem_layer4;
	else if ( i == 4) SectorSystem = SectorSystem_layer5;

	unsigned module = SectorSystem->getModule(z);
	unsigned sensor = SectorSystem->getSensor(layer, x);
	
	TrackerHitSimple* TrackerHitSimple_ = new TrackerHitSimple(x, y, z, layer, module, sensor, SectorSystem);
	//vector_TrackerHit.push_back(TrackerHitSimple);

	//std::cout << "get sector from layer, module and sensor" << std::endl;
	
	int sector = SectorSystem->getSector(layer, module, sensor);
	//vsector.push_back(sector);

	map_sector_Hit[sector].push_back(TrackerHitSimple_);

      }

      nHits_Layers_ += vLayer[i];

    }


    /*************************************/
    /********* building segment **********/
    /*************************************/

    SegmentBuilder* SegmentBuilder_ = new SegmentBuilder(map_sector_Hit);

    TrackerSectorConnector* TrackerSectorConnector_layer1 = new TrackerSectorConnector(SectorSystem_layer1, 1, 5, 1);
    TrackerSectorConnector* TrackerSectorConnector_layer2 = new TrackerSectorConnector(SectorSystem_layer2, 1, 5, 2);
    TrackerSectorConnector* TrackerSectorConnector_layer3 = new TrackerSectorConnector(SectorSystem_layer3, 1, 5, 3);
    TrackerSectorConnector* TrackerSectorConnector_layer4 = new TrackerSectorConnector(SectorSystem_layer4, 1, 5, 4);
    TrackerSectorConnector* TrackerSectorConnector_layer5 = new TrackerSectorConnector(SectorSystem_layer5, 1, 5, 5);

    SegmentBuilder_->addSectorConnector(TrackerSectorConnector_layer1);
    SegmentBuilder_->addSectorConnector(TrackerSectorConnector_layer2);
    SegmentBuilder_->addSectorConnector(TrackerSectorConnector_layer3);
    SegmentBuilder_->addSectorConnector(TrackerSectorConnector_layer4);
    SegmentBuilder_->addSectorConnector(TrackerSectorConnector_layer5);

    float ratio_min = 0.01;
    float ratio_max = 0.3;
    Crit2_RZRatio* rzRation_crit2 = new Crit2_RZRatio(ratio_min, ratio_max);

    float deltaRhoMin = 10.;
    float deltaRhoMax = 200.;
    Crit2_DeltaRho* deltaRho = new Crit2_DeltaRho(deltaRhoMin, deltaRhoMax);

    float dy_min = 149., dy_max = 151.;
    Crit2_DeltaY* deltaY = new Crit2_DeltaY(dy_min, dy_max);

    float phi_min = -90., phi_max = 90.;

    Crit2_DeltaPhi* deltaphi = new Crit2_DeltaPhi(phi_min, phi_max);
    //std::cout << "add criteria for segment builder" << std::endl;
    SegmentBuilder_->addCriterion(deltaY);
    SegmentBuilder_->addCriterion(deltaRho);
    //SegmentBuilder_->addCriterion(deltaphi);
    //SegmentBuilder_->addCriterion(rzRation_crit2);


    //declare automaton
    // std::cout << "***********performing get1SegAutomaton() from SegmentBuilder_ ********" << std::endl;
    Automaton automaton_ = SegmentBuilder_->get1SegAutomaton();

    //std::cout << "\n -------- segment of automaton: " << (automaton_.getSegments()).size() << std::endl;
    //std::cout << "add criteria for automaton" << std::endl;
    //this is done before doAutomaton() and cleanBadStates()

    automaton_.addCriterion(deltaRho);
    //automaton_.addCriterion(rzRation_crit2);
    

    std::cout << "\n ------doAutomaton------" << std::endl;
    //perform automaton, then lengthen the segments
    //clean segments that are not connected each other
    automaton_.doAutomaton();

    float angleMin = 0., angleMax = 20.;
    Crit3_2DAngle* deltaAngle = new Crit3_2DAngle(angleMin, angleMax);

    automaton_.addCriterion(deltaAngle);

    //float distMinR = 0., distMaxR = 15.;
    float distMinR = 0., distMaxR = 2000.;
    Crit4_DistOfCircleCenters* distCircleCenter = new Crit4_DistOfCircleCenters(distMinR, distMaxR);

    automaton_.addCriterion(distCircleCenter);

    float angle_3hit_min = 0., angle_3hit_max = 20.;
    Crit4_2DAngleChange* deltaAngle_3hit = new Crit4_2DAngleChange(angle_3hit_min, angle_3hit_max);

    automaton_.addCriterion(deltaAngle_3hit);

    std::cout << "\n ------lengthenSegments from 1hits --> 2hits------\n" << std::endl;
    automaton_.lengthenSegments();

    //automaton_.addCriterion(deltaAngle);
    std::cout << "\n \n------lengthenSegments from 2hits --> 3hits------\n" << std::endl;
    automaton_.lengthenSegments();

    //std::cout << ">>>>>>>------------ get track-----------" << std::endl;
    std::vector < std::vector< IHit* > > IHit_check = automaton_.getTracks(3);

    std::cout << "\n \n------lengthenSegments from 3hits --> 4hits------\n" << std::endl;
    automaton_.lengthenSegments();

    //std::cout << ">>>>>>>------------ get track-----------" << std::endl;
    automaton_.getTracks(4);
    std::cout << ">>>>number of hit with 4 layer: " << (automaton_.getTracks(4)).size() << std::endl;
    std::vector < std::vector< IHit* > > Track4 = automaton_.getTracks(4);

    //std::cout << "------cleanBadStates------" << std::endl;
    //automaton_.cleanBadStates();

    //automaton_.doAutomaton();
    std::cout << "\n \n------lengthenSegments from 4hits --> 5hits------\n" << std::endl;
    //automaton_.addCriterion(distCircleCenter);
    automaton_.lengthenSegments();


    std::vector < std::vector< IHit* > > Track5 = automaton_.getTracks(5);
    //std::cout << "number of hit: " << finalTrack.size() << std::endl;
    std::vector < std::vector< IHit* > > finalTrack = Track5;

    if (Track4.size() > 0 && Track5.size() == 0)  finalTrack = Track4;

    for (int i = 0; i< finalTrack.size(); i++) {

      std::vector< IHit* > finalhit = finalTrack[i];

      float *x = new float;
      float *y = new float;
      float *z = new float;
      float *errx = new float;
      float *erry = new float;
      float *errz = new float;

      int k = 0;
      /*
      std::vector< IHit* >::iterator ihit;
      for (ihit = finalhit.begin(); ihit != finalhit.end() - 1; ihit++) {
	//if ( k>=3) continue;
	IHit* trackerhit = *ihit;
	//std::cout << "position of ihit: " << x << "\t" << y << " \t" << z << std::endl;
	if (abs(trackerhit->getX()) > abs(*ihit+1)
	x[k] = trackerhit->getX();
	y[k] = trackerhit->getY();
	z[k] = trackerhit->getZ();
	errx[k] = 1.;
	erry[k] = 0.15;
	k++;
      }
      */

      std::cout << "no. of hits: " << finalhit.size() << std::endl;
      for (int ihit = finalhit.size()-1; ihit >=0; ihit--) {
	/*
	if (ihit > 0 ) {
	  if (abs(finalhit[ihit]->getX()) > abs(finalhit[ihit-1]->getX()) ) continue;
	}
	else if (ihit == 0) {
	  if (abs(finalhit[ihit]->getX()) < abs(finalhit[ihit+1]->getX()) ) continue;
	}
	*/
	//std::cout << "x pos: " << finalhit[ihit]->getX() << "\t " << ihit << std::endl;

	x[k] = finalhit[ihit]->getX();
        y[k] = finalhit[ihit]->getY();
        z[k] = finalhit[ihit]->getZ();
        errx[k] = 1.;
        erry[k] = 0.15;
	errz[k] = 35.;
        k++;

      }


      //Riemann fit
      RiemannFit *Fitter = new RiemannFit();
      for (int ihit = 0; ihit < k; ihit++) {
	Fitter->AddHit(x[ihit], y[ihit], z[ihit], errx[ihit]*errx[ihit], erry[ihit]*erry[ihit], 0.);
      }

      Fitter->FitCircle();
      vector<double> param = Fitter->GetCircleParameters();
      //x0 = param[0], y[0] = param[1], radius = param[2]

      //cout << "----radius of circle: " << param[2] << "-----" << endl;

      float xfit[10], yfit[10];

      for (int i = 0; i < 10; i++) {
	xfit[i] = x[k-1] - i*(x[k-1] - x[0])/9;
	yfit[i] = param[1] - sqrt( pow(param[2],2) - pow(param[0]-xfit[i],2) );

	//cout << "xfit: " << xfit[i] << "\t yfit: " << yfit[i] << "\t radius: " << param[2] << endl;
      }
      TGraphErrors *grfit = new TGraphErrors(10, xfit, yfit, errx, erry);
      //grfit->Print();



      gStyle->SetOptFit(1111);
      gStyle->SetOptTitle(0);
      gStyle->SetStatY(0.9);
      gStyle->SetStatX(0.7);
      gStyle->SetStatW(0.25);
      gStyle->SetStatH(0.18);
      gStyle->SetStatFontSize(0.04); 
      gStyle->SetStatFont(62); 

      if ( k < 3 ) continue; //only fitting and get track parameter with >= 3 hits
      TGraphErrors *gr = new TGraphErrors(k, x, y, errx, erry);

      //TF1 *f1 = new TF1("f1", myFunc, -80., 0., 3);
      TF1 *f1 = new TF1("f1", myFunc, x[k-1]-1., x[0]+1., 3);
      //f1->SetParameters(5.E3, -5.E3, 5.E2); //1GeV
      //f1->SetParameters(3.E3, -3.E3, 1.E2);  //800 MeV
      //f1->SetParameters(1.E3, -1.E3, 1.E1);  //500 MeV
      //f1->SetParameters(790., -860., 500.);  //200 MeV
      f1->SetParameters(param[2], param[0], param[1]);
      f1->SetParNames("radius", "x0", "y0");

      TF1 *f2 =  new TF1("f2", myFunc, x[k-1]-1., x[0]+1., 3);
      f2->SetParameters(param[2], param[0], param[1]);
      TCanvas *c = new TCanvas("c", "c", 650, 650);
      c->cd();
      c->SetLeftMargin(1.8);
      gr->Print();
      gr->SetMarkerStyle(20);
      gr->SetMarkerSize(2);
      gr->GetYaxis()->SetTitle("Y-Position [mm]");
      gr->GetYaxis()->SetTitleOffset(1.2);
      gr->GetXaxis()->SetTitle("X-Position [mm]");
      gr->Fit("f1", "R", "");
      gr->Draw("AP");
      f2->SetLineColor(kOrange-1);
      f2->Draw("same");
      //grfit->SetLineColor(kOrange-1);
      //grfit->SetLineWidth(2);
      //grfit->Draw("LC");
      //gr->Draw("P");

      c->SaveAs("fitting.png");


      //calculate phi angle and py
      //extrapolate x-position at the edge of bess magnet
      //with y = 448.1 mm
      //x0 = param[0], y[0] = param[1], radius = param[2]
      cout << "\n ";

      float x_edge = param[0] + sqrt( pow(param[2],2) - pow ( 448.1 - param[1],2));
      float ydir_x_edge = (x_edge - param[0]) / sqrt( pow(param[2],2) - pow(param[0]-x_edge,2) );

      float phi = atan2(ydir_x_edge, x_edge);
      cout << "phi angle: " << phi << endl;
      float pt = 0.3*0.8*param[2]/1000; //[GeV/c]
      float py = cos(phi) * pt;

      TGraphErrors *gryz = new TGraphErrors(k, z, y, errz, erry);
      TF1 *fline = new TF1("fline", "pol1", z[k-1]-20, z[0]+20);
      fline->SetParameters(1000., 500.);
      //gryz->Fit("pol1", "", "", z[k-1]-20, z[0]+20);
      gryz->Fit(fline);

      Double_t* param_line = fline->GetParameters();

      float pz = py/param_line[1];
      cout << "\n pt: " << pt << "\t pz: " << pz << endl;

      TCanvas *c1 = new TCanvas("c1", "c1", 650, 650);
      c1->cd();
      gryz->Draw("AP");

      c1->SaveAs("LineFitting.png");

      std::cout << "\n " << std::endl;

    }

    std::cout << "done event " << iev << " th \n \n " << std::endl;


    


      /***********************************/
      /**** get map of sector and hit ****/
      /***********************************/
    //the code below is replace by command: map_sector_Hit[sector].push_back(TrackerHitSimple);
    /*
      if (vsector.size() > 0) {

	vector<int> vindex;
	std::vector<TrackerHitSimple*> vTrackerHit;

	vTrackerHit.clear();

	for (int i = 0; i < vsector.size(); i++) {

	  if (vindex.size() > 0) {

	    for (int ii = 0; ii < vindex.size(); ii++) {
	      if (i == vindex[ii]) continue;

	    }
	  }

	  vindex.clear();

	  vTrackerHit.push_back(vector_TrackerHit[i]);

	//loop to check if one sector has several hits
	for (int j = i+1; j < vsector.size(); j++) {
	  if (vsector[j] == vsector[i]) vTrackerHit.push_back(vector_TrackerHit[j]);
	  vindex.push_back(j);
	}

	map_sector_Hit.insert(std::map<int, std::vector<IHits*>>::value_type(vsector[i], vTrackerHit));

	} //done loop on vsector

      } //close if loop (vsector>0)

    } //done loop on vLayer
    */




  }




}
