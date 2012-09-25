cmake_minimum_required(VERSION 2.6)

project(faslib CXX)

SET(CPACK_PACKAGE_NAME "faslib")
SET(CPACK_PACKAGE_VERSION "0.2.0")

if (NOT DEFINED CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif (NOT DEFINED CMAKE_BUILD_TYPE)

if ( "${CMAKE_BUILD_TYPE}" STREQUAL ""  )
  set(CMAKE_BUILD_TYPE "Release")
endif ( "${CMAKE_BUILD_TYPE}" STREQUAL ""  )


if(UNIX)

  SET(CMAKE_CXX_FLAGS "-W -Wall -Werror -pedantic -fno-rtti")
  SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG ")
  SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "-O2 -g -DNDEBUG")
  SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")

elseif(MSVC)

  SET(CMAKE_CXX_FLAGS "/W3 /wd4503 /wd4307 /EHsc /D_CRT_SECURE_NO_WARNINGS /D_SCL_SECURE_NO_WARNINGS")
  SET(CMAKE_CXX_FLAGS_RELEASE "/O2 /DNDEBUG")
  SET(CMAKE_CXX_FLAGS_DEBUG  "/Od /D_DEBUG")
  SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "/Yd /O2 /DNDEBUG")

else(UNIX)

endif(UNIX)


add_subdirectory(config)

# Enable compile-time check type_list and generate human readable error (increases compile time)
#add_definitions(-DFASLIB_TYPE_LIST_CHECK)

# Experimental disable type_list specialization (increases compile time)
#add_definitions(-DDISABLE_TYPE_LIST_SPEC)

# Deprecated
#add_definitions(-DFAS_ALGORITHM_LAMBDA_CAST)

# Enable simplify  expressions for algorithms (experimental)
#add_definitions(-DFAS_ALGORITHM_SIMPLIFY)

# Disable warnings for non-optimal code
add_definitions(-DFAS_DISABLE_WARNINGS)

if (FAS_USE_RT_LIB)
  message(STATUS "ADD_DEFINITIONS(-DFAS_USE_RT_LIB)")
  add_definitions(-DFAS_USE_RT_LIB)
else(FAS_USE_RT_LIB)
  message(STATUS "NOT ADD_DEFINITIONS(-DFAS_USE_RT_LIB)")
endif(FAS_USE_RT_LIB)

message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

ENABLE_TESTING()

include_directories(./)

add_subdirectory(tests)
add_subdirectory(examples)
add_subdirectory(tutorial)

add_custom_target( tests make WORKING_DIRECTORY tests )
add_custom_target( examples make WORKING_DIRECTORY examples )
add_custom_target( tutorial make WORKING_DIRECTORY tutorial )

set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "2")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
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
  PATTERN "*~" EXCLUDE
  PATTERN "*kdev*" EXCLUDE
  PATTERN ".git*" EXCLUDE
  PATTERN "README.md" EXCLUDE
  PATTERN timeout EXCLUDE
)

include(CPack)
