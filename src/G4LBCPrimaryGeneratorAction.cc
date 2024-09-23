#include "G4LBCPrimaryGeneratorAction.hh"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

G4LBCPrimaryGeneratorAction::G4LBCPrimaryGeneratorAction()
{
    fParticleGPS = new G4GeneralParticleSource();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

G4LBCPrimaryGeneratorAction::~G4LBCPrimaryGeneratorAction()
{
    delete fParticleGPS;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void G4LBCPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    fParticleGPS->GeneratePrimaryVertex(anEvent);
}
