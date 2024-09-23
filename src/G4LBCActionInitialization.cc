#include "G4LBCActionInitialization.hh"
#ifdef MRESPONSE
   #include "G4LBCPrimaryGeneratorActionMR.hh"
#else
   #include "G4LBCPrimaryGeneratorAction.hh"
#endif
#include "G4LBCRunAction.hh"
#include "G4LBCEventAction.hh"
#include "G4LBCStackingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4LBCActionInitialization::G4LBCActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4LBCActionInitialization::~G4LBCActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4LBCActionInitialization::BuildForMaster() const
{
  G4LBCRunAction * run = new G4LBCRunAction();
  SetUserAction(run);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4LBCActionInitialization::Build() const
{

#ifdef MRESPONSE
  G4LBCPrimaryGeneratorActionMR * gen   = new G4LBCPrimaryGeneratorActionMR();
#else
  G4LBCPrimaryGeneratorAction * gen   = new G4LBCPrimaryGeneratorAction();
#endif
     G4LBCEventAction            * event = new G4LBCEventAction();
     G4LBCStackingAction         * stack = new G4LBCStackingAction();

     G4LBCRunAction * run = new G4LBCRunAction();
     SetUserAction(run);

     SetUserAction(gen);
     SetUserAction(event);
     SetUserAction(stack);

     return ;
}
//
