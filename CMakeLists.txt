
#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(G4LBC)

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build B1. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.

set(
  G4LBC
  # Geometry - LBC
  geometry/front_cap.stl
  geometry/guide.stl
  geometry/plastic_guide.stl
  geometry/source_holder_plastic_guide.stl
  geometry/source_plastic_guide.stl
  geometry/source_enclosure_plastic_guide.stl
  geometry/plastic_source.stl
  geometry/pmt_holder.stl
  geometry/rear_cap.stl
  geometry/source_holder.stl
  geometry/source.stl
  geometry/pmt.stl
  geometry/pmt_window.stl
  geometry/bosh.stl
  geometry/aluminum_guide.stl
  geometry/source_holder_plastic.stl
  geometry/source_holder_aluminum_guide.stl
  macro/vis/initialize_visualization.mac
  macro/examples/na22.mac
  macro/examples/cs137.mac
  macro/examples/ba133.mac
  macro/examples/am241.mac
  macro/examples/eu152.mac
  macro/examples/co60.mac
  macro/examples/geantino.mac
  macro/analysis/efficiency.cc
  macro/analysis/spectra.cc
  macro/analysis/join_thread.cc
)

foreach(_script ${G4LBC})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(G4LBC G4LBC.cc ${sources} ${headers})
target_link_libraries(G4LBC ${Geant4_LIBRARIES})


#----------------------------------------------------------------------------
# Build options
#

# Calibration Source ISO/12/C34343
option(SOURCE_ISO "Calibration source" OFF)
if(SOURCE_ISO)
   message("-- Building G4LBC using Calibration Source")
   add_definitions(-DSOURCE_ISO)
endif()

option(PLASTIC_GUIDE "Plastic Guide" OFF)
if(PLASTIC_GUIDE)
   message("-- Building G4LBC using plastic guide")
   add_definitions(-DPLASTIC_GUIDE)
endif()

option(BOSH_PROFILE "Bosh Profile" OFF)
if(BOSH_PROFILE)
   message("-- Building G4LBC using bosh profile")
   add_definitions(-DBOSH_PROFILE)
endif()

option(LEAD_SHIELDING "Lead Shielding" OFF)
if(LEAD_SHIELDING)
   message("-- Building G4LBC using lead shielding")
   add_definitions(-DLEAD_SHIELDING)
endif()

option(ALUMINUM_GUIDE "Aluminum Guide" OFF)
if(ALUMINUM_GUIDE)
   message("-- Building G4LBC using aluminum guide")
   add_definitions(-DALUMINUM_GUIDE)
endif()

option(CLOUD "Cloud version" OFF)
if(CLOUD)
   message("-- Building G4LBC with CLOUD Support")
   add_definitions(-DCLOUD)
endif()

option(MRESPONSE "Matrix Response" OFF)
if(MRESPONSE)
   message("-- Building G4LBC for Matrix Response calculation")
   add_definitions(-DMRESPONSE)
endif()

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS G4LBC DESTINATION bin)
