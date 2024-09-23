#ifndef G4LBC_RUN_ACTION_H
#define G4LBC_RUN_ACTION_H 1

#include "Analysis.hh"
#include "G4UserRunAction.hh"

class G4Run;


class G4LBCRunAction : public G4UserRunAction
{
  public:

    G4LBCRunAction();
    virtual ~G4LBCRunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

  private:

    G4AnalysisManager* fAnalysisManager;
};

#endif
