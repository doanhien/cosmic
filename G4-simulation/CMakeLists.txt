#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
#project(BessMagnetRun)


#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=0")

project(BessMagnetRun)


#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#

#option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
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


#include_directories(${PROJECT_SOURCE_DIR}/include)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#find_package(ROOT REQUIRED COMPONENTS RIO Net)
find_package(ROOT QUIET)

#include(${ROOT_USE_FILE})

if(ROOT_FOUND)
add_definitions(-DG4ANALYSIS_USE_ROOT)
include(${Geant4_USE_FILE})
include_directories(${ROOT_INCLUDE_DIR} ${Geant4_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/include)
else()
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)
endif()


#include_directories(${PROJECT_SOURCE_DIR}/include 
#                    ${Geant4_INCLUDE_DIR}
#                    ${ROOT_INCLUDE_DIR})


#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(BessMagnetRun BessMagnetRun.cc ${sources} ${headers})

if(ROOT_FOUND)
target_link_libraries(BessMagnetRun ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})
else()
target_link_libraries(BessMagnetRun ${Geant4_LIBRARIES})
endif()

#target_link_libraries(BessMagnetRun ${Geant4_LIBRARIES})
#target_link_libraries(BessMagnetRun ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build ED. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#

set(BessMagnetRun_SCRIPTS
  init_vis.mac
  run.mac
  run.png
  vis.mac
  )

foreach(_script ${BessMagnetRun_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone
#
#add_custom_target(ED DEPENDS BessMagnetRun)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS BessMagnetRun DESTINATION bin)


