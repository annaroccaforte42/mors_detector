#include "G4LBCPrimaryGeneratorActionMR.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh"
#include "Randomize.hh"
#include "G4ThreeVector.hh"
#include "G4RandomDirection.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"

#include <random>
#include <ctime>
#include <chrono>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

G4LBCPrimaryGeneratorActionMR::G4LBCPrimaryGeneratorActionMR() :
G4VUserPrimaryGeneratorAction(), fParticleGun(nullptr)
{
   // Creating G4ParticleGun
   G4int numberOfParticlePerEvent = 1;
   fParticleGun = new G4ParticleGun(numberOfParticlePerEvent);

   G4ParticleDefinition * particle = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
   fParticleGun->SetParticleDefinition(particle);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

G4LBCPrimaryGeneratorActionMR::~G4LBCPrimaryGeneratorActionMR()
{
   delete fParticleGun;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void G4LBCPrimaryGeneratorActionMR::GeneratePrimaries(G4Event* anEvent)
{
   // Generate a random point inside a sphere of 1 mm of diameter
   unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
   std::mt19937 generator (seed);

   std::uniform_real_distribution<double> phi(0.0, 2*M_PI);
   std::uniform_real_distribution<double> cos_theta(-1,1);
   std::uniform_real_distribution<double> u(0.0, 1);

   double theta = std::acos(cos_theta(generator));
   G4double R = 0.5*CLHEP::mm;
   G4double r = R * std::cbrt(u(generator));
   G4double mphi = phi(generator);

   G4double x = r * std::sin( theta ) * cos( mphi );
   G4double y = r * std::sin( theta ) * sin( mphi );
   G4double z = r * std::cos( theta );

   //G4double fDistance = 20*CLHEP::cm;
   G4double fDistance = 0*CLHEP::cm;
   // Translate to predefined source-to-detector distance
   fParticleGun->SetParticlePosition(G4ThreeVector(x,y,z)+G4ThreeVector(0,-184.5*CLHEP::mm-fDistance,-1*CLHEP::mm));

   // Sample a point on unitary sphere surface
   fParticleGun->SetParticleMomentumDirection(G4RandomDirection());

   // Generate event
   fParticleGun->GeneratePrimaryVertex(anEvent);

   return ;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
