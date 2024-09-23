#include "G4LBCRunAction.hh"
#include "Analysis.hh"
#include "G4Run.hh"

G4LBCRunAction::G4LBCRunAction() : G4UserRunAction()
{
  fAnalysisManager = G4AnalysisManager::Instance();

  fAnalysisManager->SetVerboseLevel(1);

  fAnalysisManager->CreateNtuple("lbc_tree","LBC Simulation");
  fAnalysisManager->CreateNtupleDColumn("edep");
  fAnalysisManager->FinishNtuple();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

G4LBCRunAction::~G4LBCRunAction()
{
  delete fAnalysisManager;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void G4LBCRunAction::BeginOfRunAction(const G4Run * run)
{
  fAnalysisManager->OpenFile();
  return ;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void G4LBCRunAction::EndOfRunAction(const G4Run * run)
{

  fAnalysisManager->Write();
  fAnalysisManager->CloseFile();
  return ;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
