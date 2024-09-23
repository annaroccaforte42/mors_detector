// User Defined Classes
#include "G4LBCDetectorConstruction.hh"
#include "G4LBCSensitiveDetector.hh"

// Geometry Related Libraries
#include "G4SDManager.hh"
#include "G4NistManager.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"

// CGS Geometry Classes
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"

// Visualization Libraries
#include "G4Colour.hh"
#include "G4VisAttributes.hh"


// CADMesh Library
// Reference : https://github.com/christopherpoole/CADMesh
#include "CADMesh.hh"


G4LBCDetectorConstruction::G4LBCDetectorConstruction()
: G4VUserDetectorConstruction(){}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

G4LBCDetectorConstruction::~G4LBCDetectorConstruction(){}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

G4VPhysicalVolume* G4LBCDetectorConstruction::Construct()
{

  /////////////////////////////////////////////////////////////////////////////
  // Materials Definition
  /////////////////////////////////////////////////////////////////////////////
  G4NistManager * nist = G4NistManager::Instance();

  G4Material * materialAir           = nist->FindOrBuildMaterial("G4_AIR");
  G4Material * materialAluminum      = nist->FindOrBuildMaterial("G4_Al");
  G4Material * materialQuartz        = nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
  G4Material * materialCopper        = nist->FindOrBuildMaterial("G4_Cu");
  G4Material * materialLead          = nist->FindOrBuildMaterial("G4_Pb");
  G4Material * materialPlexyGlass    = nist->FindOrBuildMaterial("G4_PLEXIGLASS");
  G4Material * materialPolyPropilene = nist->FindOrBuildMaterial("G4_POLYPROPYLENE");
  G4Material * materialSoftTissue    = nist->FindOrBuildMaterial("G4_TISSUE_SOFT_ICRP");

  G4Element * elLa = new G4Element("Lanthanum", "La", 57, 138.905*g/mole);
  G4Element * elBr = new G4Element("Bromine", "Br", 35, 79.904*g/mole);
  G4Element * elCl = new G4Element("Chlorine", "Cl", 17, 35.453*g/mole);

  G4double density     = 4.90 * g / cm3;
  G4int    nComponents = 3;

  G4Material * materialLBC = new G4Material("LBC", density, nComponents);
  materialLBC->AddElement(elLa, 37.3451*perCent);
  materialLBC->AddElement(elBr, 61.22*perCent);
  materialLBC->AddElement(elCl, 1.4296*perCent);

  G4Element * elC  = new G4Element("Carbon", "C", 6, 12.011*g/mole);
  G4Element * elH  = new G4Element("Hydrogen", "H", 1, 1.008*g/mole);
  G4Element * elO  = new G4Element("Oxygen", "O", 8, 15.999*g/mole);
  G4Element * elMn = new G4Element("Manganese", "Mn", 25, 54.938 *g/mole);
  G4Element * elNi = new G4Element("Nickel", "Ni", 28, 58.693 *g/mole);
  G4Element * elFe = new G4Element("Iron", "Fe", 26, 55.845 *g/mole);
  G4Element * elMo = new G4Element("Molybdenum","Mo",42,95.95*g/mole);
  G4Element * elSi = new G4Element("Silicon", "Si", 14, 28.085*g/mole);
  G4Element * elCe = new G4Element("Cerium", "Ce", 58, 140.12*g/mole);
  G4Element * elAl = new G4Element("Aluminum", "Al", 13, 24.982*g/mole);
  G4Element * elMg = new G4Element("Magnesium", "Mg", 12, 24.982*g/mole);
  G4Element * elLi = new G4Element("Lithium", "Li", 3, 6.94*g/mole);

  density = 0.4021 * g / cm3;
  nComponents = 3;
  G4Material * materialPLA = new G4Material("PLA", density, nComponents);
  materialPLA->AddElement(elC, 3);
  materialPLA->AddElement(elH, 4);
  materialPLA->AddElement(elO, 2);

  G4Element * elF = new G4Element("Florine", "F", 9, 18.998* g/mole);

  density = 1.2*g/cm3;
  nComponents = 2;
  G4Material* materialTeflon = new G4Material("materialTeflon", density, nComponents);
  materialTeflon->AddElement(elC,2);
  materialTeflon->AddElement(elF,4);

  density = 8.74 * g/cm3;
  nComponents = 6;
  G4Material * materialMuMetal = new G4Material("MuMetal", density, nComponents);
  materialMuMetal->AddElement(elC, 0.0002);
  materialMuMetal->AddElement(elMn, 0.005);
  materialMuMetal->AddElement(elSi, 0.0035);
  materialMuMetal->AddElement(elNi, 0.8000);
  materialMuMetal->AddElement(elFe, 0.1493);
  materialMuMetal->AddElement(elMo, 0.0420);


  //////////////////////////////////////////////////////////////////////////////
  // Glass Definition
  //////////////////////////////////////////////////////////////////////////////

   // SiO2
   density = 2.65* g/cm3;
   nComponents = 2;
   G4int nAtoms;
   G4Material * sio2 = new G4Material("SiO2", density, nComponents);
   sio2->AddElement(elSi,nAtoms=1);
   sio2->AddElement(elO, nAtoms=2);

   // MgO
   density = 3.58 * g/cm3;
   nComponents = 2;
   G4Material * mgo = new G4Material("MgO", density, nComponents);
   mgo->AddElement(elMg, nAtoms=1);
   mgo->AddElement(elO, nAtoms=1);

   // Ce2O3
   density = 6.2* g/cm3;
   nComponents = 2;
   G4Material * ce2o3 = new G4Material("Ce2O3", density, nComponents);
   ce2o3->AddElement(elCe,nAtoms=2);
   ce2o3->AddElement(elO, nAtoms=3);

   // Al2O3
   density = 3.95* g/cm3;
   nComponents = 2;
   G4Material * al2o3 = new G4Material("Al2O3", density, nComponents);
   al2o3->AddElement(elAl,nAtoms=2);
   al2o3->AddElement(elO, nAtoms=3);

   // Li2O
   density = 2.013* g/cm3;
   nComponents = 2;
   G4Material * li2o = new G4Material("Li2O", density, nComponents);
   li2o->AddElement(elLi,nAtoms=2);
   li2o->AddElement(elO, nAtoms=1);

   // glassMaterial
   density = 2.69 * g/cm3;
   nComponents = 5;
   G4Material * materialGlass = new G4Material("Glass", density, nComponents);
   materialGlass->AddMaterial(sio2,0.56);
   materialGlass->AddMaterial(mgo,0.04);
   materialGlass->AddMaterial(ce2o3,0.04);
   materialGlass->AddMaterial(al2o3,0.18);
   materialGlass->AddMaterial(li2o,0.18);

   G4Material * materialAm = nist->FindOrBuildMaterial("G4_Am");


  /////////////////////////////////////////////////////////////////////////////
  // World Volume
  /////////////////////////////////////////////////////////////////////////////

  G4double world_half_Z  = 100*cm;
  G4double world_half_XY = 100*cm;

  G4Box * solidWorld = new G4Box("solidWorld", world_half_XY, world_half_XY, world_half_Z);
  G4LogicalVolume* logicalWorld = new G4LogicalVolume(solidWorld, materialAir, "logicalWorld", 0, 0, 0, true);

  G4VPhysicalVolume * physicalWorld = new G4PVPlacement(0,
                                                        G4ThreeVector(),
                                                        logicalWorld,
                                                        "physicalWorld",
                                                        0,
                                                        false,
                                                        0,
                                                        true);

  G4double spanning_angle = 360*deg;

  /////////////////////////////////////////////////////////////////////////////
  // LBC Detector
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // 1. Hermetic Sealing
  /////////////////////////////////////////////////////////////////////////////

  G4double pRmin = 0    * mm;
  G4double pRmax = 16.5 * mm;
  G4double halfZ = 15.0 * mm;

  G4Tubs * solid_HermeticSeal_side = new G4Tubs("solid_HermeticSeal_side",
                                                pRmin,
                                                pRmax,
                                                halfZ,
                                                0*deg,
                                                spanning_angle);

  pRmin = 0     * mm;
  pRmax = 15.25 * mm;
  halfZ = 3.2    * mm;

  G4Tubs * solid_HermeticSeal_window = new G4Tubs("solid_HermeticSeal_window",
                                                  pRmin,
                                                  pRmax,
                                                  halfZ,
                                                  0*deg,
                                                  spanning_angle);

  G4SubtractionSolid * solid_HermeticSeal =
    new G4SubtractionSolid("solid_HermeticSeal", solid_HermeticSeal_side, solid_HermeticSeal_window, 0, G4ThreeVector(0,0,-15*mm));

  G4LogicalVolume * logical_HermeticSeal =
    new G4LogicalVolume(solid_HermeticSeal, materialAluminum, "logicalHermeticSeal", 0, 0, 0, true);

  G4RotationMatrix* m90rotX = new G4RotationMatrix();
  m90rotX->rotateX(-90*deg);

  new G4PVPlacement(m90rotX,
                    G4ThreeVector(0,-15.765*cm,0),
                    logical_HermeticSeal,
                    "physicalHermeticSeal",
                    logicalWorld,
                    false,
                    0,
                    true);

  /////////////////////////////////////////////////////////////////////////////
  // 2. Reflector
  /////////////////////////////////////////////////////////////////////////////
  pRmin = 0     * mm;
  pRmax = 15.25 * mm;
  halfZ = 12.8  * mm;

  G4Tubs * solid_Reflector = new G4Tubs("solid_Reflector",
                                        pRmin,
                                        pRmax,
                                        halfZ,
                                        0*deg,
                                        spanning_angle);

  G4LogicalVolume * logical_Reflector =
    new G4LogicalVolume(solid_Reflector, materialTeflon, "logicalReflector", 0, 0, 0, true);

  new G4PVPlacement(0,
                    G4ThreeVector(0,0,1.4*mm),
                    logical_Reflector,
                    "physicalReflector",
                    logical_HermeticSeal,
                    false,
                    0,
                    true);

  /////////////////////////////////////////////////////////////////////////////
  // 3. LBC Crystal
  /////////////////////////////////////////////////////////////////////////////
  pRmin = 0     * mm;
  pRmax = 12.5  * mm;
  halfZ = 12.5  * mm;

  G4Tubs * solid_LBC = new G4Tubs("solid_LBC",
                                        pRmin,
                                        pRmax,
                                        halfZ,
                                        0*deg,
                                        spanning_angle);

  G4LogicalVolume * logical_LBC =
     new G4LogicalVolume(solid_LBC, materialLBC, "logicalLBC", 0, 0, 0, true);

  new G4PVPlacement(0,
                    G4ThreeVector(0,0,0.3-0.6*mm),
                    logical_LBC,
                    "physicalLBC",
                    logical_Reflector,
                    false,
                    0,
                    true);

  /////////////////////////////////////////////////////////////////////////////
  // 4. Optical Window
  /////////////////////////////////////////////////////////////////////////////
  pRmin = 0     * mm;
  pRmax = 15.25 * mm;
  halfZ = 0.2   * mm;

  G4Tubs * solid_OpticalWindow = new G4Tubs("solid_OpticalWindow",
                                        pRmin,
                                        pRmax,
                                        halfZ,
                                        0*deg,
                                        spanning_angle);

  G4LogicalVolume * logical_OpticalWindow =
    new G4LogicalVolume(solid_OpticalWindow, materialGlass, "logicalOpticalWindow", 0, 0, 0, true);

  new G4PVPlacement(0,
                    G4ThreeVector(0,0,-15+3.4*mm),
                    logical_OpticalWindow,
                    "physicalOpticalWindow",
                    logical_HermeticSeal,
                    false,
                    0,
                    true);


  /////////////////////////////////////////////////////////////////////////////
  // Detector Shell
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // 1. PMT Holder
  /////////////////////////////////////////////////////////////////////////////

#ifdef CLOUD
  auto mesh_pmt_holder = CADMesh::TessellatedMesh::FromSTL("/storage/lbcapp/geometry/pmt_holder.stl");
#else
   auto mesh_pmt_holder = CADMesh::TessellatedMesh::FromSTL("geometry/pmt_holder.stl");
#endif

  G4VSolid* solid_pmt_holder = mesh_pmt_holder->GetSolid();

  G4LogicalVolume* logical_pmt_holder =
    new G4LogicalVolume(solid_pmt_holder, materialPLA,"logical_pmt_holder", 0, 0, 0, true);

  new G4PVPlacement(0,
                    G4ThreeVector(0,0,0),
                    logical_pmt_holder,
                    "physical_pmt_holder",
                    logicalWorld,
                    false,
                    0,
                    true);

   /////////////////////////////////////////////////////////////////////////////
   // 2. Front CAP
   /////////////////////////////////////////////////////////////////////////////

#ifdef CLOUD
   auto mesh_front_cap = CADMesh::TessellatedMesh::FromSTL("/storage/lbcapp/geometry/front_cap.stl");
#else
   auto mesh_front_cap = CADMesh::TessellatedMesh::FromSTL("geometry/front_cap.stl");
#endif

   G4VSolid* solid_front_cap = mesh_front_cap->GetSolid();

   G4LogicalVolume* logical_front_cap =
      new G4LogicalVolume(solid_front_cap, materialPLA,"logical_front_cap", 0, 0, 0, true);

   new G4PVPlacement(0,
                     G4ThreeVector(0,0,0),
                     logical_front_cap,
                     "physical_front_cap",
                     logicalWorld,
                     false,
                     0,
                     true);

   /////////////////////////////////////////////////////////////////////////////
   // 3. Rear CAP
   /////////////////////////////////////////////////////////////////////////////

#ifdef CLOUD
   auto mesh_rear_cap = CADMesh::TessellatedMesh::FromSTL("/storage/lbcapp/geometry/rear_cap.stl");
#else
   auto mesh_rear_cap = CADMesh::TessellatedMesh::FromSTL("geometry/rear_cap.stl");
#endif

   G4VSolid* solid_rear_cap = mesh_rear_cap->GetSolid();

   G4LogicalVolume* logical_rear_cap =
      new G4LogicalVolume(solid_rear_cap, materialPLA,"logical_rear_cap", 0, 0, 0, true);

   new G4PVPlacement(0,
                     G4ThreeVector(0,1.5*mm,0),
                     logical_rear_cap,
                     "physical_rear_cap",
                     logicalWorld,
                     false,
                     0,
                     true);

   /////////////////////////////////////////////////////////////////////////////
   // 4. PMT - Core
   /////////////////////////////////////////////////////////////////////////////

#ifdef CLOUD
   auto mesh_pmt = CADMesh::TessellatedMesh::FromSTL("/storage/lbcapp/geometry/pmt.stl");
#else
   auto mesh_pmt = CADMesh::TessellatedMesh::FromSTL("geometry/pmt.stl");
#endif

   G4VSolid* solid_pmt = mesh_pmt->GetSolid();

   G4LogicalVolume* logical_pmt =
      new G4LogicalVolume(solid_pmt, materialMuMetal,"logical_pmt", 0, 0, 0, true);

   new G4PVPlacement(0,
                     G4ThreeVector(0,0.15*mm,0),
                     logical_pmt,
                     "physical_pmt",
                     logicalWorld,
                     false,
                     0,
                     true);

   /////////////////////////////////////////////////////////////////////////////
   // 5. PMT - Window
   /////////////////////////////////////////////////////////////////////////////

#ifdef CLOUD
   auto mesh_pmt_window = CADMesh::TessellatedMesh::FromSTL("/storage/lbcapp/geometry/pmt_window.stl");
#else
   auto mesh_pmt_window = CADMesh::TessellatedMesh::FromSTL("geometry/pmt_window.stl");
#endif

   G4VSolid* solid_pmt_window = mesh_pmt_window->GetSolid();

   G4LogicalVolume* logical_pmt_window =
      new G4LogicalVolume(solid_pmt_window, materialGlass,"logical_pmt_window", 0, 0, 0, true);

   new G4PVPlacement(0,
                     G4ThreeVector(0,0.13*mm,0),
                     logical_pmt_window,
                     "physical_pmt_window",
                     logicalWorld,
                     false,
                     0,
                     true);

  /////////////////////////////////////////////////////////////////////////////
  // Sample Guide
  /////////////////////////////////////////////////////////////////////////////

#ifdef PLASTIC_GUIDE

#ifdef CLOUD
  auto mesh_plastic_guide = CADMesh::TessellatedMesh::FromSTL("/storage/lbcapp/geometry/plastic_guide.stl");
#else
   auto mesh_plastic_guide = CADMesh::TessellatedMesh::FromSTL("geometry/plastic_guide.stl");
#endif

  G4VSolid* solid_plastic_guide = mesh_plastic_guide->GetSolid();

  G4LogicalVolume * logical_plastic_guide =
     new G4LogicalVolume(solid_plastic_guide, materialPLA, "logical_plastic_guide",0 ,0, 0, true);

  new G4PVPlacement(0,
                    G4ThreeVector(0,0,0.15*cm),
                    logical_plastic_guide,
                    "physical_plastic_guide",
                    logicalWorld,
                    false,
                    0,
                    true);
#endif

#ifdef ALUMINUM_GUIDE

#ifdef CLOUD
   auto mesh_aluminum_guide = CADMesh::TessellatedMesh::FromSTL("/storage/lbcapp/geometry/aluminum_guide.stl");
#else
   auto mesh_aluminum_guide = CADMesh::TessellatedMesh::FromSTL("geometry/aluminum_guide.stl");
#endif

   G4VSolid* solid_aluminum_guide = mesh_aluminum_guide->GetSolid();

   G4LogicalVolume * logical_aluminum_guide =
      new G4LogicalVolume(solid_aluminum_guide, materialAluminum, "logical_aluminum_guide",0 ,0, 0, true);

   new G4PVPlacement(0,
                     G4ThreeVector(0,0,0.15*cm),
                     logical_aluminum_guide,
                     "physical_plastic_guide",
                     logicalWorld,
                     false,
                     0,
                     true);

#endif

   /////////////////////////////////////////////////////////////////////////////
   // Bosh profile
   /////////////////////////////////////////////////////////////////////////////

#ifdef BOSH_PROFILE

#ifdef CLOUD
   auto mesh_bosh = CADMesh::TessellatedMesh::FromSTL("/storage/lbcapp/geometry/bosh.stl");
#else
   auto mesh_bosh = CADMesh::TessellatedMesh::FromSTL("geometry/bosh.stl");
#endif

   G4VSolid* solid_bosh = mesh_bosh->GetSolid();

   G4LogicalVolume * logical_bosh  =
      new G4LogicalVolume(solid_bosh, materialAluminum, "logical_bosh",0 ,0, 0, true);

    new G4PVPlacement(0,
                      G4ThreeVector(0,0,0.15*cm),
                      logical_bosh,
                      "physical_bosh",
                      logicalWorld,
                      false,
                      0,
                      true);

#endif

  /////////////////////////////////////////////////////////////////////////////
  // Sample / Source
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Source Holder:
  /////////////////////////////////////////////////////////////////////////////

#ifdef PLASTIC_GUIDE

#ifdef CLOUD
   auto mesh_source_holder = CADMesh::TessellatedMesh::FromSTL("/storage/lbcapp/geometry/source_holder_plastic_guide.stl");
#else
   auto mesh_source_holder = CADMesh::TessellatedMesh::FromSTL("geometry/source_holder_plastic_guide.stl");
#endif

#endif

#ifdef ALUMINUM_GUIDE

#ifdef CLOUD
   auto mesh_source_holder = CADMesh::TessellatedMesh::FromSTL("/storage/lbcapp/geometry/source_holder_aluminum_guide.stl");
#else
   auto mesh_source_holder = CADMesh::TessellatedMesh::FromSTL("geometry/source_holder_aluminum_guide.stl");
#endif

#endif

G4double fDistance = 5*cm;

#if defined(PLASTIC_GUIDE) || defined(ALUMINUM_GUIDE)

  G4VSolid* solid_source_holder = mesh_source_holder->GetSolid();

  G4LogicalVolume * logical_source_holder =
     new G4LogicalVolume(solid_source_holder, materialPLA, "logical_source_holder",0 ,0, 0, true);

   new G4PVPlacement(0,
                     G4ThreeVector(0,0*cm-fDistance,0.15*cm),
                     logical_source_holder,
                     "physical_source_holder",
                     logicalWorld,
                     false,
                     0,
                     true);

#endif


#ifdef SOURCE_ISO

  /////////////////////////////////////////////////////////////////////////////
  // 2. Plastic Source
  /////////////////////////////////////////////////////////////////////////////

#ifdef CLOUD
  auto mesh_plastic_source = CADMesh::TessellatedMesh::FromSTL("/storage/lbcapp/geometry/source_enclosure_plastic_guide.stl");
#else
  auto mesh_plastic_source = CADMesh::TessellatedMesh::FromSTL("geometry/source_enclosure_plastic_guide.stl");
#endif

  G4VSolid* solid_plastic_source = mesh_plastic_source->GetSolid();

  G4LogicalVolume * logical_plastic_source =
     new G4LogicalVolume(solid_plastic_source, materialPlexyGlass, "logical_plastic_source",0 ,0, 0, true);

   new G4PVPlacement(0,
                     G4ThreeVector(0,0.15*cm-fDistance,0.15*cm),
                     logical_plastic_source,
                     "physical_plastic_source",
                     logicalWorld,
                     false,
                     0,
                     true);

  /////////////////////////////////////////////////////////////////////////////
  // 2. Point Source  - ISO/12/C34343
  /////////////////////////////////////////////////////////////////////////////

#ifdef CLOUD
  auto mesh_source = CADMesh::TessellatedMesh::FromSTL("/storage/lbcapp/geometry/source_plastic_guide.stl");
#else
  auto mesh_source = CADMesh::TessellatedMesh::FromSTL("geometry/source_plastic_guide.stl");
#endif

  G4VSolid* solid_source = mesh_source->GetSolid();

  G4LogicalVolume * logical_source =
     new G4LogicalVolume(solid_source, materialPlexyGlass, "logical_source",0 ,0, 0, true);

   new G4PVPlacement(0,
                     G4ThreeVector(0,0.15*cm-fDistance,0.15*cm),
                     logical_source,
                     "physical_source",
                     logicalWorld,
                     false,
                     0,
                     true);

#endif

#ifdef LEAD_SHIELDING

  /////////////////////////////////////////////////////////////////////////////
  // Lead Shielding
  /////////////////////////////////////////////////////////////////////////////

  G4Box * solid_lead_brick = new G4Box("solid_lead_brick", 10*cm, 5*cm, 2.5*cm);
  G4LogicalVolume * logical_lead_brick = new G4LogicalVolume(solid_lead_brick, materialLead, "logical_lead_brick", 0, 0, 0, true);

  G4double yspacer = -3*cm;

  // Base Bricks
  new G4PVPlacement(0,
                    G4ThreeVector(0,yspacer,-7.85*cm),
                    logical_lead_brick,
                    "physical_source",
                    logicalWorld,
                    false,
                    0,
                    true);

  new G4PVPlacement(0,
                    G4ThreeVector(0,-10*cm+yspacer,-7.85*cm),
                    logical_lead_brick,
                    "physical_source",
                    logicalWorld,
                    false,
                    1,
                    true);

  new G4PVPlacement(0,
                    G4ThreeVector(0,-20*cm+yspacer,-7.85*cm),
                    logical_lead_brick,
                    "physical_source",
                    logicalWorld,
                    false,
                    2,
                    true);

  // Front Brick

  new G4PVPlacement(m90rotX,
                    G4ThreeVector(0,-22.5*cm+yspacer,-7.85*cm+2.5*cm+5*cm),
                    logical_lead_brick,
                    "physical_source",
                    logicalWorld,
                    false,
                    3,
                    true);

  // Side Bricks

  G4RotationMatrix* m90rotXZ = new G4RotationMatrix();
  m90rotXZ->rotateZ(-90*deg);
  m90rotXZ->rotateX(-90*deg);

  new G4PVPlacement(m90rotXZ,
                    G4ThreeVector(+7.5*cm-5*mm,yspacer-10*cm,-7.85*cm+7.5*cm),
                    logical_lead_brick,
                    "physical_source",
                    logicalWorld,
                    false,
                    4,
                    true);

  new G4PVPlacement(m90rotXZ,
                    G4ThreeVector(+7.5*cm-5*mm,yspacer-15*cm,-7.85*cm+7.5*cm+10*cm),
                    logical_lead_brick,
                    "physical_source",
                    logicalWorld,
                    false,
                    5,
                    true);

#endif

  /////////////////////////////////////////////////////////////////////////////
  // Visualization Attributes
  /////////////////////////////////////////////////////////////////////////////

  logicalWorld->SetVisAttributes(G4VisAttributes::Invisible);

  // LBC Assembly
  logical_HermeticSeal->SetVisAttributes(new G4VisAttributes(G4Colour(102.0/255, 103.0/255, 105.0/255, 1)));
  logical_Reflector->SetVisAttributes(new G4VisAttributes(G4Colour(194.0/255, 194.0/255, 194.0/255, 0.4)));
  logical_LBC->SetVisAttributes(new G4VisAttributes(G4Colour(50.0/255, 103.0/255, 105.0/255, 0.4)));
  logical_OpticalWindow->SetVisAttributes(new G4VisAttributes(G4Colour(145.0/255, 135.0/255, 106.0/255, 0.4)));
  logical_pmt_holder->SetVisAttributes(new G4VisAttributes(G4Colour(15.0/255, 15.0/255, 15.0/255, 0.4)));
  logical_front_cap->SetVisAttributes(new G4VisAttributes(G4Colour(15.0/255, 15.0/255, 15.0/255, 0.4)));
  logical_rear_cap->SetVisAttributes(new G4VisAttributes(G4Colour(15.0/255, 15.0/255, 15.0/255, 0.4)));
  logical_pmt->SetVisAttributes(new G4VisAttributes(G4Colour(214.0/255, 214.0/255, 214.0/255, 1)));
  logical_pmt_window->SetVisAttributes(new G4VisAttributes(G4Colour(247.0/255, 238.0/255, 136.0/255, 1)));

  // Plastic Guide source holder
#ifdef SOURCE_ISO
  logical_plastic_source->SetVisAttributes(new G4VisAttributes(G4Colour(235.0/255, 235.0/255, 235.0/255, 0.75)));
  logical_source->SetVisAttributes(new G4VisAttributes(G4Colour(191.0/255, 151.0/255, 17.0/255, 0.75)));
#endif

#ifdef PLASTIC_GUIDE
   logical_plastic_guide->SetVisAttributes(new G4VisAttributes(G4Colour(0.0/255, 0.0/255, 0.0/255, 1)));
#endif

#if defined(PLASTIC_GUIDE) || defined(ALUMINUM_GUIDE)
   logical_source_holder->SetVisAttributes(new G4VisAttributes(G4Colour(0.0/255, 0.0/255, 0.0/255, 1)));
#endif

#ifdef LEAD_SHIELDING
  logical_lead_brick->SetVisAttributes(new G4VisAttributes(G4Colour(110.0/255, 110.0/255, 110.0/255, 1)));
#endif

  // logical_CopperShielding->SetVisAttributes(new G4VisAttributes(G4Colour(189.0/255, 124.0/255, 51./255, 0.1)));
  // logical_LeadBrick->SetVisAttributes(new G4VisAttributes(G4Colour(0.5, 0.5, 0.5, 0.1)));
  // logical_detector_source_holder->SetVisAttributes(new G4VisAttributes(G4Colour(0, 0, 0, 0.4)));

#ifdef BOSH_PROFILE
  logical_bosh->SetVisAttributes(new G4VisAttributes(G4Colour(110.0/255, 110.0/255, 110.0/255, 1)));
#endif

  return physicalWorld;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void G4LBCDetectorConstruction::ConstructSDandField()
{
  G4LBCSensitiveDetector * sd = new G4LBCSensitiveDetector("LBC SD","LBCHitsCollection");

  G4SDManager::GetSDMpointer()->AddNewDetector(sd);
  SetSensitiveDetector("logicalLBC", sd);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
