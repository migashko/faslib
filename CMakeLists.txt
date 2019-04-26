cmake_minimum_required(VERSION 2.8)

project(faslib CXX)

# Enable compile-time check type_list and generate human readable error (increases compile time)
if ( FASLIB_TYPE_LIST_CHECK )
  add_definitions(-DFASLIB_TYPE_LIST_CHECK)
endif()

# Experimental disable type_list specialization (increases compile time)
if ( DISABLE_TYPE_LIST_SPEC )
  add_definitions(-DDISABLE_TYPE_LIST_SPEC)
endif()

# Deprecated
if ( FAS_ALGORITHM_LAMBDA_CAST )
  add_definitions(-DFAS_ALGORITHM_LAMBDA_CAST)
endif()

# Enable simplify  expressions for algorithms (experimental)
if ( FAS_ALGORITHM_SIMPLIFY )
  add_definitions(-DFAS_ALGORITHM_SIMPLIFY)
endif()

# Disable warnings for non-optimal code
if ( NOT FAS_ENABLE_WARNINGS )
  add_definitions(-DFAS_DISABLE_WARNINGS)
endif()

add_subdirectory(config)
set(FAS_TESTING_CPP "${CMAKE_CURRENT_SOURCE_DIR}/fas/testing/testing.cpp")

if ( BUILD_TESTING)

  if ( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STRICT_ANSI__")
  endif()
  
  if (PARANOID_WARNING)
    if(UNIX)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -ftemplate-depth=1400 -Wcast-align -Winvalid-pch -pedantic-errors  -Wformat-nonliteral -Wchar-subscripts ")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcomment -Wconversion -Wformat-security -Wimport")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat-y2k")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wlong-long -Wmissing-braces -Wmissing-field-initializers")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmissing-format-attribute -Wmissing-noreturn -Wpacked -Wparentheses -Wpointer-arith")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wreturn-type -Wsequence-point -Wsign-compare -Wstack-protector -Wuninitialized")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch-enum -Wtrigraphs -Wunknown-pragmas")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfloat-equal  -Wformat -Wformat=2 -Winit-self  -Wmissing-declarations")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunreachable-code -Wunused -Wunused-function -Wunused-label -Wunused-parameter -Wunused-value")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused-variable  -Wvariadic-macros -Wvolatile-register-var  -Wwrite-strings")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wstrict-overflow=2 -Wswitch -Wswitch-default -Wundef -Werror")
      #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weffc++ -Wnon-virtual-dtor")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")
      if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        # -Wunsafe-loop-optimizations
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wlogical-op  -Wnoexcept -Wstrict-null-sentinel")
      endif()
    endif()
  endif ()
  enable_testing()
  include_directories(./)
  add_subdirectory(tests)
  add_subdirectory(examples)
  add_subdirectory(tutorial)
endif()

set(CPACK_PACKAGE_NAME "faslib")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "8")
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
  PATTERN "*~*" EXCLUDE
  PATTERN "*kdev*" EXCLUDE
  PATTERN ".git*" EXCLUDE
  PATTERN "README.md" EXCLUDE
  PATTERN "fasg++*" EXCLUDE
  PATTERN timeout EXCLUDE
)

include(CPack)
