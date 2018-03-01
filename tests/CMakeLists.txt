cmake_minimum_required(VERSION 3.5)

project(faslib-tests)

if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type selected, default to Release")
  set(CMAKE_BUILD_TYPE "Release")
endif()

if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Werror -pedantic -fno-rtti ")
  message(STATUS "CMAKE_CXX_COMPILER_VERSION = ${CMAKE_CXX_COMPILER_VERSION}")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG ")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "-O2 -g -DNDEBUG")
  set(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")
elseif(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GR- /W3 /wd4503 /wd4307 /EHsc /D_CRT_SECURE_NO_WARNINGS /D_SCL_SECURE_NO_WARNINGS")
  set(CMAKE_CXX_FLAGS_RELEASE "/O2 /DNDEBUG")
  set(CMAKE_CXX_FLAGS_DEBUG  "/Od /D_DEBUG")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "/Yd /O2 /DNDEBUG")
else(UNIX)

endif(UNIX)

include_directories(..)

set(FAS_TESTING_CPP "${CMAKE_CURRENT_SOURCE_DIR}/../fas/testing/testing.cpp")

add_subdirectory(static_check)
add_subdirectory(integral)
add_subdirectory(typemanip)
add_subdirectory(type_list)
add_subdirectory(mp)
add_subdirectory(algorithm)
add_subdirectory(hierarchy)
add_subdirectory(aop)
add_subdirectory(xtime)
add_subdirectory(testing)
add_subdirectory(range)
