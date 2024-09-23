#include "G4LBCSensitiveDetector.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"

G4LBCSensitiveDetector::G4LBCSensitiveDetector()
: G4VSensitiveDetector("det"), fHitsCollection(nullptr){}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

G4LBCSensitiveDetector::G4LBCSensitiveDetector(const G4String& name, const G4String& HC_name)
: G4VSensitiveDetector(name), fHitsCollection(nullptr)
{
  collectionName.insert(HC_name);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

G4LBCSensitiveDetector::~G4LBCSensitiveDetector(){}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void G4LBCSensitiveDetector::Initialize(G4HCofThisEvent* hitCollectionOfEvent)
{
  // Create a Hit Collection
  fHitsCollection = new G4LBCHitsCollection(SensitiveDetectorName, collectionName[0]);

  auto HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);

  hitCollectionOfEvent->AddHitsCollection(HCID, fHitsCollection);

  return ;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

G4bool G4LBCSensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* history)
{

  // Create an hit object
  G4LBCHit * hit = new G4LBCHit();

  G4double edep = step->GetTotalEnergyDeposit()/CLHEP::keV;

  hit->SetEdep(edep);

  fHitsCollection->insert(hit);

  return true;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void G4LBCSensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{
  return ;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
