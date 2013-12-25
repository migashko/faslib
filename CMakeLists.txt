cmake_minimum_required(VERSION 2.6)

project(faslib CXX)

if(UNIX)
  SET(CMAKE_CXX_FLAGS "-W -Wall -Werror -pedantic -fno-rtti -Wno-long-long")
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
  add_definitions(-DFAS_USE_RT_LIB)
endif(FAS_USE_RT_LIB)

ENABLE_TESTING()

include_directories(./)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/tests)
add_custom_target( tests 
  #COMMAND cd tests
  COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Release --build ${CMAKE_BINARY_DIR}/tests --target all ${CMAKE_SOURCE_DIR}/tests
  #COMMAND cd ..
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)
#add_subdirectory(tests)
#add_subdirectory(examples)
#add_subdirectory(tutorial)



#CMAKE_INCLUDE_PATH
#add_custom_target(all true WORKING_DIRECTORY .)
#add_custom_target( all make WORKING_DIRECTORY true )
#add_custom_target( tests {CMAKE_COMMAND} WORKING_DIRECTORY tests )
#add_custom_target( examples make WORKING_DIRECTORY examples )
#add_custom_target( tutorial make WORKING_DIRECTORY tutorial )

set(CPACK_PACKAGE_NAME "faslib")
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
  PATTERN "*~*" EXCLUDE
  PATTERN "*kdev*" EXCLUDE
  PATTERN ".git*" EXCLUDE
  PATTERN "README.md" EXCLUDE
  PATTERN "fasg++*" EXCLUDE
  PATTERN timeout EXCLUDE
)

include(CPack)
