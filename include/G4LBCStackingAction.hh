#ifndef G4LBC_STACKING_ACTION_H
#define G4LBC_STACKING_ACTION_H

#include "G4UserStackingAction.hh"
#include "globals.hh"

class G4LBCStackingAction : public G4UserStackingAction
{
   public:

      G4LBCStackingAction();
      virtual ~G4LBCStackingAction();

      virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track*);

};

#endif
