#ifndef G4LBC_SENSITIVE_DETECTOR_H
#define G4LBC_SENSITIVE_DETECTOR_H 1

#include "G4Step.hh"
#include "G4LBCHit.hh"
#include "G4HCofThisEvent.hh"
#include "G4VSensitiveDetector.hh"

class G4LBCSensitiveDetector : public G4VSensitiveDetector
{
  public:

    G4LBCSensitiveDetector();
    G4LBCSensitiveDetector(const G4String& name, const G4String& HC_name);

    virtual ~G4LBCSensitiveDetector();

    virtual void   Initialize(G4HCofThisEvent* hitsCollection);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    virtual void   EndOfEvent(G4HCofThisEvent* hitsCollection);

  private:

    G4LBCHitsCollection* fHitsCollection;
};


#endif
