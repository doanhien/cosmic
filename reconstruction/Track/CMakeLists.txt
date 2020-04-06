cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=0")

#export CFLAGS=-D_GLIBCXX_USE_CXX11_ABI=0
#export CXXFLAGS=-D_GLIBCXX_USE_CXX11_ABI=0


# set the project name
project(TrackFinding)

# You need to tell CMake where to find the ROOT installation.
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS RIO Net)

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})


include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#add_library(tracklib STATIC ${PROJECT_SOURCE_DIR}/src/*.cc ${PROJECT_SOURCE_DIR}/include/*.hh)
#add_library(tracklib STATIC sources headers)
#target_include_directories(tracklib PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(TrackFinding main.cc ${sources} ${headers})

target_link_libraries(TrackFinding ${ROOT_LIBRARIES})

install(TARGETS TrackFinding DESTINATION bin)

