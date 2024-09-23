#include "G4LBCPhysicsList.hh"
#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics_option2.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4HadronElasticPhysics.hh"

G4LBCPhysicsList::G4LBCPhysicsList() : G4VModularPhysicsList()
{
  // Decay Physics
  RegisterPhysics(new G4DecayPhysics());
  RegisterPhysics(new G4RadioactiveDecayPhysics());
  // EM 3
  // RegisterPhysics(new G4EmStandardPhysics_option3());
  // EM 4
  RegisterPhysics(new G4EmStandardPhysics_option4());
  // Hadron Elastic
  // RegisterPhysics(new G4HadronElasticPhysics());

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

G4LBCPhysicsList::~G4LBCPhysicsList(){}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void G4LBCPhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCuts();

  return ;
}
