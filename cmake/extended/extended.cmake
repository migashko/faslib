include(${CMAKE_CURRENT_LIST_DIR}/extended-option.cmake)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
  include(${CMAKE_CURRENT_LIST_DIR}/gen/optimize.cmake)
endif()

if ( PARANOID_WARNING )
  include(${CMAKE_CURRENT_LIST_DIR}/gen/warnings.cmake)
endif()
