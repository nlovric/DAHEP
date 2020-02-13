// Include classes
#include <Analyzer.h>

// Declaring default constructor
Analyzer::Analyzer()
{
}

// Destructor declaration
Analyzer::~Analyzer()
{
}

// Function for the ChiSquareFit
void Analyzer::ChiSquareFit()
{
  c = new TCanvas("c","c",1200,800);
  c->Divide(2);
  gStyle->SetOptFit(); //kako bi se u statističkoj kutiji vidjeli podaci o parametrima fittinga, u ovom slučaju svih jer nismo zadali drugačije

  c->cd(1);

  double F[5]  = {1,2,3,4,5};
  double a[5]  = {9.8,21.2,34.5,39.9,48.5};
  double sigma_F[5] = {0.,0.,0.,0.,0.};
  double sigma_a[5] = {1.0,1.9,3.1,3.9,5.1};

  gr = new TGraphErrors(5,F,a,sigma_F,sigma_a);

  gr->SetTitle("Mass of the ball measurement;F [N];a [m/s^{2}]");
  gr->SetMarkerColor(kBlack);
  gr->SetMarkerStyle(21);
  gr->Draw("AP");

  fit_function = new TF1("fit_function","x/[0]",0,50.); //x je ovdje F, a y je akceleracija, dakle a=F/m je funkcija na koju radimo fit
  fit_function->SetParName(0,"mass");
  fit_function->SetParameter(0,0.1);

  gr->Fit(fit_function);

  c->cd(2);

  ChiSquare_function = new TF1("Chi-Square Function",
  "TMath::Power(([0]-[1]*x)/([2]),2)+TMath::Power(([3]-[4]*x)/([5]),2)+TMath::Power(([6]-[7]*x)/([8]),2)+TMath::Power(([9]-[10]*x)/([11]),2)+TMath::Power(([12]-[13]*x)/([14]),2)",9.4,11.0);

  ChiSquare_function->SetParameter(0,a[0]);
  ChiSquare_function->SetParameter(1,F[0]);
  ChiSquare_function->SetParameter(2,sigma_a[0]);
  ChiSquare_function->SetParameter(3,a[1]);
  ChiSquare_function->SetParameter(4,F[1]);
  ChiSquare_function->SetParameter(5,sigma_a[1]);
  ChiSquare_function->SetParameter(6,a[2]);
  ChiSquare_function->SetParameter(7,F[2]);
  ChiSquare_function->SetParameter(8,sigma_a[2]);
  ChiSquare_function->SetParameter(9,a[3]);
  ChiSquare_function->SetParameter(10,F[3]);
  ChiSquare_function->SetParameter(11,sigma_a[3]);
  ChiSquare_function->SetParameter(12,a[4]);
  ChiSquare_function->SetParameter(13,F[4]);
  ChiSquare_function->SetParameter(14,sigma_a[4]);

  ChiSquare_function->SetTitle("Chi-Square function;mass^{-1} [kg^{-1}];#chi^{2}");

  ChiSquare_function->Draw();

  float n1 = 2*a[0]*F[0]*TMath::Power(sigma_a[1],2)*TMath::Power(sigma_a[2],2)*TMath::Power(sigma_a[3],2)*TMath::Power(sigma_a[4],2);
  float n2 = 2*a[1]*F[1]*TMath::Power(sigma_a[0],2)*TMath::Power(sigma_a[2],2)*TMath::Power(sigma_a[3],2)*TMath::Power(sigma_a[4],2);
  float n3 = 2*a[2]*F[2]*TMath::Power(sigma_a[1],2)*TMath::Power(sigma_a[0],2)*TMath::Power(sigma_a[3],2)*TMath::Power(sigma_a[4],2);
  float n4 = 2*a[3]*F[3]*TMath::Power(sigma_a[1],2)*TMath::Power(sigma_a[2],2)*TMath::Power(sigma_a[0],2)*TMath::Power(sigma_a[4],2);
  float n5 = 2*a[4]*F[4]*TMath::Power(sigma_a[1],2)*TMath::Power(sigma_a[2],2)*TMath::Power(sigma_a[3],2)*TMath::Power(sigma_a[0],2);

  float d1 = 2*F[0]*F[0]*TMath::Power(sigma_a[1],2)*TMath::Power(sigma_a[2],2)*TMath::Power(sigma_a[3],2)*TMath::Power(sigma_a[4],2);
  float d2 = 2*F[1]*F[1]*TMath::Power(sigma_a[0],2)*TMath::Power(sigma_a[2],2)*TMath::Power(sigma_a[3],2)*TMath::Power(sigma_a[4],2);
  float d3 = 2*F[2]*F[2]*TMath::Power(sigma_a[1],2)*TMath::Power(sigma_a[0],2)*TMath::Power(sigma_a[3],2)*TMath::Power(sigma_a[4],2);
  float d4 = 2*F[3]*F[3]*TMath::Power(sigma_a[1],2)*TMath::Power(sigma_a[2],2)*TMath::Power(sigma_a[0],2)*TMath::Power(sigma_a[4],2);
  float d5 = 2*F[4]*F[4]*TMath::Power(sigma_a[1],2)*TMath::Power(sigma_a[2],2)*TMath::Power(sigma_a[3],2)*TMath::Power(sigma_a[0],2);

  float oneOverMass_hat = (n1+n2+n3+n4+n5)/(d1+d2+d3+d4+d5);

  float sigma_oneOverMass = (sigma_a[0]*sigma_a[1]*sigma_a[2]*sigma_a[3]*sigma_a[4])/(TMath::Sqrt((d1/2)+(d2/2)+(d3/2)+(d4/2)+(d5/2)));

  cout << endl;
  cout << "===================================================================================================" << endl;
  cout << "Analiticaly calculated parameter from the Chi-Square method: mass = " << 1/oneOverMass_hat << endl;
  cout << "Analiticaly calculated standard deviation from the Chi-Square method: sigma = " << sigma_oneOverMass/TMath::Power(oneOverMass_hat,2) << endl;
  cout << "===================================================================================================" << endl;
  cout << endl;

  float mass_hat;
  float sigma_m, sigma_p;

  mass_hat = ChiSquare_function->GetMinimumX();
  sigma_m = mass_hat - ChiSquare_function->GetX(ChiSquare_function->GetMinimum() + 1.0,mass_hat - 5., mass_hat-0.01);
  sigma_p = ChiSquare_function->GetX(ChiSquare_function->GetMinimum() + 1.0,mass_hat+0.01, mass_hat + 5.) - mass_hat;

  cout << endl;
  cout << "===================================================================================================" << endl;
  cout << "Parameter from the maximum of the Chi-Square function: mass = " << 1/mass_hat << endl;
  cout << "Uncertainty from the Chi-Square_max - 0.5: sigma_+ = " << sigma_p/TMath::Power(mass_hat,2) << " sigma_- = " << sigma_m/TMath::Power(mass_hat,2) << endl;
  cout << "===================================================================================================" << endl;
  cout << endl;

  ChiSquare_function->SetMinimum(1.0);

  line_h = new TLine(mass_hat-sigma_m,ChiSquare_function->GetMinimum() + 1.0,mass_hat+sigma_p,ChiSquare_function->GetMinimum() + 1.0);
  line_h->SetLineColor(kBlack);
  line_h->SetLineStyle(kDashed);
  line_h->Draw();

  line_v1 = new TLine(mass_hat-sigma_m,1.0,mass_hat-sigma_m,ChiSquare_function->GetMinimum() + 1.0);
  line_v1->SetLineColor(kBlack);
  line_v1->SetLineStyle(kDashed);
  line_v1->Draw();

  line_v2 = new TLine(mass_hat,1.0,mass_hat,ChiSquare_function->GetMinimum());
  line_v2->SetLineColor(kBlack);
  line_v2->SetLineStyle(kDashed);
  line_v2->Draw();

  line_v3 = new TLine(mass_hat+sigma_p,1.0,mass_hat+sigma_p,ChiSquare_function->GetMinimum() + 1.0);
  line_v3->SetLineColor(kBlack);
  line_v3->SetLineStyle(kDashed);
  line_v3->Draw();

  c->SaveAs("ChiSquareFit.pdf");

  delete c,gr;
}