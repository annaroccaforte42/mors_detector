#ifndef G4LBC_EVENT_ACTION_H
#define G4LBC_EVENT_ACTION_H 1

#include "G4UserEventAction.hh"
#include "globals.hh"

#include "G4LBCHit.hh"

class G4LBCEventAction : public G4UserEventAction
{
  public:

    G4LBCEventAction();
    virtual ~G4LBCEventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

  private:

    G4LBCHitsCollection* GetHitsCollection(G4int hcID, const G4Event* event) const;
    G4int fHCID;

};

#endif
