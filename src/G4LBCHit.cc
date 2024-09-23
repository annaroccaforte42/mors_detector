#include "G4LBCHit.hh"

G4ThreadLocal G4Allocator<G4LBCHit>* G4LBCHitAllocator = 0;

G4LBCHit::G4LBCHit() : G4VHit()
{
  fEdep = 0.0;
}

G4LBCHit::~G4LBCHit(){}

G4LBCHit::G4LBCHit(const G4LBCHit& right) : G4VHit()
{
	fEdep = right.fEdep;
}

const G4LBCHit& G4LBCHit::operator=(const G4LBCHit& right)
{
	fEdep = right.fEdep;
	return *this;
}

G4int G4LBCHit::operator==(const G4LBCHit& right) const
{
	return (this == &right ) ? 1 : 0;
}
