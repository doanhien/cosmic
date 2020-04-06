#include "Fitter.h"

#include "TF1.h"
#include "TMath.h"

#include <iostream>

using namespace std;


Fitter::Fitter() 
{
}


Double_t Fitter::myFunc(Double_t *x, Double_t *par)
{

  Double_t xx = x[0];
  Double_t fx = -TMath::Sqrt(par[0] - (xx-par[1])*(xx-par[1]))+par[2];
  return fx;

}


void Fitter::fitCircular(TGraphErrors* gr)
{

  Double_t *x = new Double_t;
  Double_t *par = new Double_t;

  Double_t xx = x[0];
  Double_t fx = -TMath::Sqrt(par[0] - (xx-par[1])*(xx-par[1]))+par[2];

  //TF1 *f1 = new TF1("f1", fx, -80., -2., 3);
  //TF1 *f1 = new TF1("f1", myFunc, -80., -2., 3);
  TF1 *f1 = new TF1("f1", "-TMath::Sqrt([0] - (x-[1])*(x-[1]))+[2]", -80., -2., 3);
  f1->SetParameters(9E7, -1.E3, 1.E3);
  f1->SetParNames("radius", "x0", "y0");
  gr->Fit("f1", "M", "");

  std::cout << "chi2 = " << f1->GetChisquare() << std::endl;

}
