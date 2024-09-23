#include "G4LBCEventAction.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "Analysis.hh"

G4LBCEventAction::G4LBCEventAction() : G4UserEventAction(), fHCID(-1){}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

G4LBCEventAction::~G4LBCEventAction(){}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

G4LBCHitsCollection * G4LBCEventAction::GetHitsCollection(G4int hcID, const G4Event* event) const
{
  auto hitsCollection = static_cast<G4LBCHitsCollection*>(event->GetHCofThisEvent()->GetHC(hcID));

  return hitsCollection;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/


void G4LBCEventAction::BeginOfEventAction(const G4Event* event)
{
  return ;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/

void G4LBCEventAction::EndOfEventAction(const G4Event* event)
{
  // Check for Hit Collection ID
  if(fHCID == -1)
  {
    fHCID = G4SDManager::GetSDMpointer()->GetCollectionID("LBCHitsCollection");
  }

  // Retrieve Hit Collection of this Event
  auto hit_collection_of_this_event = GetHitsCollection(fHCID, event);

  const long hit_collection_size = (long) hit_collection_of_this_event->GetSize();

  if(hit_collection_size == 0) return ;

  double edep = 0.0;

  for (long i = 0; i < hit_collection_size; i++)
  {
    edep += (*hit_collection_of_this_event)[i]->GetEdep();
  }

  if(edep == 0) return ;

  auto fAnalysisManager = G4AnalysisManager::Instance();
  fAnalysisManager->FillNtupleDColumn(0,0,edep);
  fAnalysisManager->AddNtupleRow(0);
  return ;
}
