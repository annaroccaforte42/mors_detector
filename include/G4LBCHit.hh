#ifndef G4LBC_HIT_H
#define G4LBC_HIT_H 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"

class G4LBCHit : public G4VHit
{
  public:

    // Constructors
    G4LBCHit();
    G4LBCHit(const G4LBCHit&);
    // Destructor
    ~G4LBCHit();

    // Operators
    const G4LBCHit& operator=(const G4LBCHit&);
    G4int operator==(const G4LBCHit&) const;

    inline void * operator new(size_t);
    inline void   operator delete(void*);

    // User Defined Hit Interface

    void SetEdep(G4double edep){ fEdep = edep; };
    G4double GetEdep(){ return fEdep; };

  private:

    G4double fEdep;
};

using G4LBCHitsCollection = G4THitsCollection<G4LBCHit>;
extern G4ThreadLocal G4Allocator<G4LBCHit>* G4LBCHitAllocator;

inline void* G4LBCHit::operator new(size_t)
{
  if(!G4LBCHitAllocator) G4LBCHitAllocator = new G4Allocator<G4LBCHit>;

  void * hit;
  hit = (void*) G4LBCHitAllocator->MallocSingle();

  return hit;
}

inline void G4LBCHit::operator delete(void *hit)
{
  if(!G4LBCHitAllocator) G4LBCHitAllocator = new G4Allocator<G4LBCHit>;

  G4LBCHitAllocator->FreeSingle((G4LBCHit*)hit);

  return ;
}

#endif
