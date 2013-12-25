cmake_minimum_required(VERSION 2.6)

project(tutorial)
include_directories(..)

if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type selected, default to Release")
  set(CMAKE_BUILD_TYPE "Release")
endif()

if(UNIX)
  SET(CMAKE_CXX_FLAGS "-W -Wall -Werror -pedantic -fno-rtti -Wno-unused-local-typedefs")
  SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG ")
  SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "-O2 -g -DNDEBUG")
  SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")
elseif(MSVC)
  SET(CMAKE_CXX_FLAGS "/GR- /W3 /wd4503 /wd4307 /EHsc /D_CRT_SECURE_NO_WARNINGS /D_SCL_SECURE_NO_WARNINGS")
  SET(CMAKE_CXX_FLAGS_RELEASE "/O2 /DNDEBUG")
  SET(CMAKE_CXX_FLAGS_DEBUG  "/Od /D_DEBUG")
  SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "/Yd /O2 /DNDEBUG")
else(UNIX)

endif(UNIX)


include_directories(..)


add_subdirectory(type_list)
add_subdirectory(algorithm)
add_subdirectory(aop)

