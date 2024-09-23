/*
  ISOLPHARM Gamma-Counter based on a LBC scintillator
  ----------------------------------------------------

*/

// Geant4 core libs
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "Randomize.hh"

// User defined classes
#include "G4LBCDetectorConstruction.hh"
#include "G4LBCPhysicsList.hh"
#ifdef MRESPONSE
   #include "G4LBCPrimaryGeneratorActionMR.hh"
#else
   #include "G4LBCPrimaryGeneratorAction.hh"
#endif
#include "G4LBCRunAction.hh"
#include "G4LBCEventAction.hh"
#include "G4LBCStackingAction.hh"
#include "G4LBCActionInitialization.hh"

// Prepackaged PL
#include "G4PhysListFactory.hh"

// STL libs
#include <random>
#include <ctime>
#include <chrono>

int main(int argc, char** argv)
{

  G4UIExecutive * ui = 0;
  if(argc == 1)
  {
    ui = new G4UIExecutive(argc, argv);
  }

  // Choose the random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  // Initialize SEED using current time since epoch
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  // Set HepRandom with time dependent seed --> Needed for Cloud Parallelization
  CLHEP::HepRandom::setTheSeed(seed);
  G4Random::setTheSeed(seed);

  // Construct the run manager
#ifdef G4MULTITHREADED
 G4MTRunManager* runManager = new G4MTRunManager;
 runManager->SetNumberOfThreads(0.5*(G4Threading::G4GetNumberOfCores()));
#else
 G4RunManager* runManager = new G4RunManager;
#endif

  // Set Mandatory initialization classes
  // ---------------------------------------------------------------------------
  G4LBCDetectorConstruction * det  = new G4LBCDetectorConstruction();
  G4LBCPhysicsList          * phys = new G4LBCPhysicsList();

  // G4int verbose = 1;
  // G4PhysListFactory factory;
  // G4VModularPhysicsList* phys = factory.GetReferencePhysList("QGSP_BERT_HP");
  phys->SetVerboseLevel(2);

  runManager->SetUserInitialization(det);
  runManager->SetUserInitialization(phys);
  runManager->SetUserInitialization(new G4LBCActionInitialization);

  // Set Mandatory action classes
  // ---------------------------------------------------------------------------
// #ifdef MRESPONSE
//   G4LBCPrimaryGeneratorActionMR * gen   = new G4LBCPrimaryGeneratorActionMR();
// #else
//   G4LBCPrimaryGeneratorAction * gen   = new G4LBCPrimaryGeneratorAction();
// #endif
//   G4LBCRunAction              * run   = new G4LBCRunAction();
//   G4LBCEventAction            * event = new G4LBCEventAction();
//   G4LBCStackingAction         * stack = new G4LBCStackingAction();
//
//   runManager->SetUserAction(gen);
//   runManager->SetUserAction(run);
//   runManager->SetUserAction(event);
//   runManager->SetUserAction(stack);

  // Initialize visualization
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  // get the pointer to the User Interface Manager
  G4UImanager * uiManager = G4UImanager::GetUIpointer();

  if(!ui)
  {
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    uiManager->ApplyCommand(command+fileName);
  }
  else
  {
    uiManager->ApplyCommand("/control/execute macro/vis/initialize_visualization.mac");
    ui->SessionStart();
    delete ui;
  }

  // Terminate application
  // All user action and initialization classes are freed by the runManager
  // so they should not be deleted in the main() program
  delete visManager;
  delete runManager;

  return 0;
}
