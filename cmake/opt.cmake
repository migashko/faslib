if ( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
  message(FATAL_ERROR "********* FATAL: Source and build directories cannot be the same. ********* Remove CMakeCache.txt from ${CMAKE_SOURCE_DIR}")
endif()

if (NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 11)
endif()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(CODE_COVERAGE "Build with code coverage" OFF)
option(BUILD_TESTING "Build with tests and samples" OFF)
option(WITH_SAMPLES "Build with samples" ON)
option(PARANOID_WARNING "Paranoid warning level" OFF)

if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type selected, default to Release")
  set(CMAKE_BUILD_TYPE "Release")
endif()

if ( CODE_COVERAGE )
  set(BUILD_TESTING ON)
  set(WITH_SAMPLES OFF)
  set(CMAKE_BUILD_TYPE "Debug")
  set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -Wpedantic -pedantic-errors -ftemplate-depth=1400 -ftemplate-backtrace-limit=0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG -march=native  ")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O2 -g -DNDEBUG -march=native ")
set(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")

if ( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STRICT_ANSI__ ${CLANG_LIBPP} ")   #-stdlib=libc++
endif()

set(UNIT_TEST_BIN_OUTPUT_DIR "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/tests")

MACRO(add_test_memcheck test)
  if ( NOT CODE_COVERAGE )
    add_test(
      NAME "${test}-memcheck"
      COMMAND valgrind --tool=memcheck --leak-check=full --error-exitcode=1 ${UNIT_TEST_BIN_OUTPUT_DIR}/${test} ${ARGN}
      WORKING_DIRECTORY ${UNIT_TEST_BIN_OUTPUT_DIR}
    )
  endif()
ENDMACRO(add_test_memcheck)

include(${CMAKE_CURRENT_LIST_DIR}/extended/extended.cmake)
