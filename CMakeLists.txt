cmake_minimum_required(VERSION 3.10)

project(faslib LANGUAGES CXX
               VERSION "0.9.8"
               HOMEPAGE_URL https://faslib.com/)

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
target_sources(faslib INTERFACE $<BUILD_INTERFACE:${faslib_SOURCE_DIR}>
                                $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_include_directories(faslib SYSTEM INTERFACE $<BUILD_INTERFACE:${faslib_SOURCE_DIR}>
                                                   $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_include_directories(fas_testing SYSTEM PUBLIC $<BUILD_INTERFACE:${faslib_SOURCE_DIR}>
                                                     $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)


if ( BUILD_TESTING)
  enable_testing()
  add_subdirectory(tests)
  if ( WITH_SAMPLES )
    add_subdirectory(examples)
    add_subdirectory(tutorial)
  endif()
endif()

include(cmake/install.cmake)

install(
  DIRECTORY fas/
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/fas"
)

install(
  TARGETS fas_testing
  EXPORT ${PROJECT_NAME}Targets
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

