#ifndef Fitter_h
#define Fitter_h


#include "TGraph.h"
#include "TGraphErrors.h"
//#include "TCanvas.h"
//#include "TStyle.h"
#include "TF1.h"

class Fitter {

 public:

  Fitter();
  virtual ~Fitter() {};

  Double_t myFunc(Double_t* x, Double_t* par);
  void fitCircular(TGraphErrors* gr);

  //private:


};

#endif
