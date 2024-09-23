#ifndef G4LBC_PRIMARY_GENERATOR_MR_H
#define G4LBC_PRIMARY_GENERATOR_MR_H

#include "G4VUserPrimaryGeneratorAction.hh"

class G4Event;
class G4ParticleGun;

class G4LBCPrimaryGeneratorActionMR : public G4VUserPrimaryGeneratorAction
{
   public:

      G4LBCPrimaryGeneratorActionMR();
      virtual ~G4LBCPrimaryGeneratorActionMR();

      void GeneratePrimaries(G4Event *);
      G4ParticleGun* GetGeneralGun() { return fParticleGun; }

   private:

      G4ParticleGun* fParticleGun;

};


#endif
