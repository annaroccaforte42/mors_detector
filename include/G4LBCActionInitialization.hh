#ifndef G4LBC_ACTION_INITIALIZATION_H
#define G4LBC_ACTION_INITIALIZATION_H

#include "G4VUserActionInitialization.hh"

class G4LBCActionInitialization : public G4VUserActionInitialization
{
  public:
    G4LBCActionInitialization();
    virtual ~G4LBCActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif
