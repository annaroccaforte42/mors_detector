#ifndef G4LBC_PHYSICS_LIST
#define G4LBC_PHYSICS_LIST 1

#include "G4VModularPhysicsList.hh"

class G4LBCPhysicsList : public G4VModularPhysicsList
{
  public:

    G4LBCPhysicsList();
    virtual ~G4LBCPhysicsList();
    virtual void SetCuts();

};

#endif
