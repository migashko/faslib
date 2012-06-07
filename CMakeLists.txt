cmake_minimum_required(VERSION 2.6)

project(faslib)

if ( "${CMAKE_BUILD_TYPE}" STREQUAL ""  )
  set(CMAKE_BUILD_TYPE "Release")
endif ( "${CMAKE_BUILD_TYPE}" STREQUAL ""  )

if(UNIX)

  SET(CMAKE_CXX_FLAGS "-Wall -fno-rtti")
  SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG ")
  SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "-O2 -g -DNDEBUG")
  SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")

elseif(MSVC)
#/WX 
  SET(CMAKE_CXX_FLAGS "/W3 /wd4503 /EHsc /D_CRT_SECURE_NO_WARNINGS /D_SCL_SECURE_NO_WARNINGS")
  SET(CMAKE_CXX_FLAGS_RELEASE "/O2 /DNDEBUG")
  SET(CMAKE_CXX_FLAGS_DEBUG  "/Od /D_DEBUG")
  SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "/Yd /O2 /DNDEBUG")

else(UNIX)
  
endif(UNIX)


add_subdirectory(config)

#add_definitions(-DFASLIB_TYPE_LIST_CHECK)
#add_definitions(-DDISABLE_TYPE_LIST_SPEC)
#add_definitions(-DFAS_ALGORITHM_LAMBDA_CAST)
#add_definitions(-DFAS_ALGORITHM_SIMPLIFY)
add_definitions(-DFAS_DISABLE_WARNINGS)

if (FAS_USE_RT_LIB )
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


add_custom_target( examples make WORKING_DIRECTORY examples )
add_custom_target( tests make WORKING_DIRECTORY tests )
#add_subdirectory(tutorial)
#add_subdirectory(probe)

SET(CPACK_PACKAGE_VERSION "0.2.0")

install(DIRECTORY fas DESTINATION include
	PATTERN "*.cmake" EXCLUDE
	PATTERN "*~" EXCLUDE
	PATTERN ".*" EXCLUDE
	PATTERN "*.cmake" EXCLUDE
	PATTERN "Makefile" EXCLUDE
	PATTERN "CMakeFiles" EXCLUDE)

include(CPack)
