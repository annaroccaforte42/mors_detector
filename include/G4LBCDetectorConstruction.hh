#ifndef G4LBC_DETECTOR_CONSTRUCTION_H
#define G4LBC_DETECTOR_CONSTRUCTION_H 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4LBCDetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    G4LBCDetectorConstruction();
    virtual ~G4LBCDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

};

#endif
