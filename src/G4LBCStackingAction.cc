#include "G4LBCStackingAction.hh"
#include "G4Track.hh"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/

G4LBCStackingAction::G4LBCStackingAction(){}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/

G4LBCStackingAction::~G4LBCStackingAction(){}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/

G4ClassificationOfNewTrack G4LBCStackingAction::ClassifyNewTrack(const G4Track* track)
{

   G4double time = track->GetGlobalTime()/CLHEP::second;
   if( time > 3600.0*24.0*365.0*50000.0 ){ return fKill; }

   return fUrgent;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~/
