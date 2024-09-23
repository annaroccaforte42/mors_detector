void compare(std::string simfilename, std::string expfilename)
{
  TFile * expfile = new TFile(expfilename.c_str());

  TH1F * hexp = (TH1F*) expfile->Get("h");
  hexp->GetXaxis()->Set(6000,-14.957,-14.957+0.064*50000);


  // hexp->GetXaxis()->Set(6000,13.24793,13.24793+0.0589757*50000+1.692328e-7*50000*50000);
  hexp->SetLineColor(kBlue);

  hexp->Rebin(2);
  hexp->SetStats(kFALSE);
  hexp->Draw("HIST");

  TFile * simfile = new TFile(simfilename.c_str());

  TH1F * hsim = (TH1F*) simfile->Get("h_lbc");

  // hsim->Scale(7e-9);
  hsim->Scale((4724147.0-0.03*4724147.0)/1e6);
  hsim->Rebin(2);
  hsim->SetLineColor(kBlack);
  hsim->Draw("HIST SAME");

  return ;
}
