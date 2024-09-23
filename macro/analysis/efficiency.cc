/*
  Macro : Efficiency LBC G4APP output file
  -------------------------------------
*/

void eff(std::string filename, double energy_th)
{

  TFile * infile = new TFile(filename.c_str());

  TTreeReader datareader("lbc_tree", infile);
  TTreeReaderValue<Double_t> data_energy(datareader,"edep");

  int counts    = 0;
  int counts_pp = 0;

  while( datareader.Next() )
  {
    if(*data_energy>energy_th*0.999 and *data_energy < 1.001*energy_th) counts_pp++;
    counts++;
  }

  std::cout << "Total Number of Events : " << counts << std::endl;
  std::cout << "Total Numer of PhotoElectric Events : " << counts_pp << std::endl;
  std::cout << "PhotoPeak to Total Ratio : " << (counts_pp*1.0)/counts << std::endl;

  return ;
}
