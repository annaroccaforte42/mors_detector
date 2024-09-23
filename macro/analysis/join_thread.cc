Double_t apply_resolution(double energy)
{

  const double p0 = 3.73976e+00;
  const double p1 = 1.96246e-01;
  const double p2 = 2.08473e-02;
  const double p3 = -4.89837e-06;

  double fwhm = p0 + p1 * sqrt(energy) + p2 * energy + p3 * energy * energy;

  double sigma = fwhm/2.355;

  return gRandom->Gaus(energy,sigma);
}

void join(std::string pattern_name, int nthreads, std::string outputfile)
{

   std::vector<string> filenames;

   for (size_t i = 0; i < nthreads; i++)
   {
      filenames.push_back(pattern_name+"_t"+std::to_string(i)+".root");
   }


   const int nBins = 6000;
   TH1F* h_edep = new TH1F("h_lbc", "LBC Spectra", nBins, 0, 3000);

   for(auto name: filenames)
   {
      TFile * f = new TFile(name.c_str());
      TTreeReader datareader("lbc_tree", f);
      TTreeReaderValue<Double_t> data_energy(datareader,"edep");

      while( datareader.Next() )
      {
        h_edep->Fill( apply_resolution(*data_energy) );
      }

      f->Close();
      delete f;
   }

   TFile * outfile = new TFile(outputfile.c_str(),"RECREATE");
   h_edep->Write();
   outfile->Close();
   delete outfile;
   return ;
}
