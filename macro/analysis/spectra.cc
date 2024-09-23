/*
  Macro : Reading LBC G4APP output file
  -------------------------------------
*/

Double_t apply_resolution(double energy)
{
  const double p0 = 6.74969e-01;
  const double p1 = 7.01927e-01;
  const double p2 = 1.41488e-04;

  double fwhm = p0+p1*sqrt(energy + p2 * energy * energy);

  double sigma = fwhm/2.355;

  return gRandom->Gaus(energy,sigma);
}

void spectra(std::string filename, std::string outfilename="test.root")
{

  TFile * infile = new TFile(filename.c_str());

  TTreeReader datareader("lbc_tree", infile);
  TTreeReaderValue<Double_t> data_energy(datareader,"edep");

  const int nBins = 6000;

  TH1F* h_edep = new TH1F("h_lbc", "LBC Spectra", nBins, 0, 3000);

  int counts    = 0;
  int counts_pp = 0;

  while( datareader.Next() )
  {
    h_edep->Fill( apply_resolution(*data_energy) );
    if(*data_energy>511*0.9999 and *data_energy < 1.0001*511) counts_pp++;
    counts++;
  }

  std::cout << "Total Number of Events : " << counts << std::endl;
  std::cout << "Total Numer of PhotoElectric Events : " << counts_pp << std::endl;
  std::cout << "PhotoPeak to Total Ratio : " << (counts_pp*1.0)/counts << std::endl;

  TCanvas * c = new TCanvas("c","LBC Canvas");

  h_edep->Draw("HIST");
  h_edep->GetXaxis()->SetTitle("Energy [keV]");
  h_edep->GetYaxis()->SetTitle("Counts [renormalized]");

  TFile * outfile = new TFile(outfilename.c_str(),"RECREATE");
  h_edep->Write();
  outfile->Close();
  return ;
}
