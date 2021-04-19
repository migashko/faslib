cmake_minimum_required(VERSION 3.1)

project(faslib CXX)

include(cmake/ci.cmake)

option(FASLIB_TYPE_LIST_CHECK "Enable compile-time check type_list and generate human readable error (increases compile time)" OFF)
option(DISABLE_TYPE_LIST_SPEC "Experimental disable type_list specialization (increases compile time)" OFF)
option(FAS_ALGORITHM_SIMPLIFY "Enable simplify  expressions for algorithms (experimental)" OFF)

# Enable compile-time check type_list and generate human readable error (increases compile time)
if ( FASLIB_TYPE_LIST_CHECK )
  add_definitions(-DFASLIB_TYPE_LIST_CHECK)
endif()

# Experimental disable type_list specialization (increases compile time)
if ( DISABLE_TYPE_LIST_SPEC )
  add_definitions(-DDISABLE_TYPE_LIST_SPEC)
endif()

# Enable simplify  expressions for algorithms (experimental)
if ( FAS_ALGORITHM_SIMPLIFY )
  add_definitions(-DFAS_ALGORITHM_SIMPLIFY)
endif()

add_subdirectory(config)

set(ENV{FAS_TESTING_CPP} "${CMAKE_CURRENT_SOURCE_DIR}/fas/testing/testing.cpp")
add_library(faslib INTERFACE)
add_library(fas_testing STATIC $ENV{FAS_TESTING_CPP})
add_library(fas::testing ALIAS fas_testing)
target_include_directories(faslib INTERFACE ${faslib_SOURCE_DIR})
target_include_directories(fas_testing PUBLIC ${faslib_SOURCE_DIR})

if ( BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
  if ( WITH_SAMPLES )
    add_subdirectory(examples)
    add_subdirectory(tutorial)
  endif()
endif()

set(CPACK_PACKAGE_NAME "faslib")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "9")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/Readme.md")
set(CPACK_PACKAGE_CONTACT "migashko@gmail.com")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

install(DIRECTORY fas DESTINATION include
  PATTERN "*.cmake" EXCLUDE
  PATTERN "*~" EXCLUDE
  PATTERN ".*" EXCLUDE
  PATTERN "Makefile" EXCLUDE
  PATTERN "CMakeFiles" EXCLUDE
)

install(DIRECTORY . DESTINATION share/faslib
  PATTERN "fas" EXCLUDE
  PATTERN "*.cmake" EXCLUDE
  PATTERN "*~*" EXCLUDE
  PATTERN "*kdev*" EXCLUDE
  PATTERN ".git*" EXCLUDE
  PATTERN "Readme.md" EXCLUDE
  PATTERN "fasg++*" EXCLUDE
  PATTERN timeout EXCLUDE
)

include(CPack)
