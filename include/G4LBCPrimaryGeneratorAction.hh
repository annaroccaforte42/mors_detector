#ifndef G4LBC_PRIMARY_GENERATOR_ACTION_H
#define G4LBC_PRIMARY_GENERATOR_ACTION_H 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"

class G4LBCPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:

    G4LBCPrimaryGeneratorAction();
    ~G4LBCPrimaryGeneratorAction();
    void GeneratePrimaries(G4Event* anEvent);

private:
    G4GeneralParticleSource* fParticleGPS;
};

#endif
