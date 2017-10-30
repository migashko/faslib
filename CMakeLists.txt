cmake_minimum_required(VERSION 2.6)

project(faslib CXX)

add_subdirectory(config)

if ( BUILD_TESTING)
  if (PARANOID_WARNING)
    if(UNIX)
      # -Weffc++ -Wunsafe-loop-optimizations
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall  -pedantic -Wcast-align -Winvalid-pch\
                         -pedantic-errors -Wextra -Wformat-nonliteral\
                         -Wchar-subscripts  -Wcomment -Wconversion -Wformat-security -Wimport \
                         -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat-y2k\
                         -Wlong-long -Wmissing-braces -Wmissing-field-initializers\
                         -Wmissing-format-attribute -Wmissing-noreturn -Wpacked -Wparentheses -Wpointer-arith\
                         -Wreturn-type -Wsequence-point -Wsign-compare -Wstack-protector -Wuninitialized\
                         -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch-enum -Wtrigraphs -Wunknown-pragmas\
                         -Wfloat-equal  -Wformat -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations \
                         -Wunreachable-code -Wunused -Wunused-function -Wunused-label -Wunused-parameter -Wunused-value \
                         -Wunused-variable  -Wvariadic-macros -Wvolatile-register-var  -Wwrite-strings \
                         -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual \
                         -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel \
                         -Wstrict-overflow=5 -Wswitch -Wswitch-default -Wundef -Werror")
    endif()
  endif ()
  enable_testing()
  add_subdirectory(tests)
  add_subdirectory(examples)
  add_subdirectory(tutorial)
endif()

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

include_directories(./)

set(CPACK_PACKAGE_NAME "faslib")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "1")
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
