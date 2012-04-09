add_executable(strlen strlen.cpp)
add_executable(strcpy strcpy.cpp)
add_executable(range_sort sort.cpp)

#if(DEFINED HAVE_RT_LIB AND DEFINED FAS_USE_RT_LIB)
#target_link_libraries(strlen rt)
#target_link_libraries(strcpy rt)
#endif(DEFINED HAVE_RT_LIB AND DEFINED FAS_USE_RT_LIB)

if (HAVE_RT_LIB AND FAS_USE_RT_LIB)
  target_link_libraries(strlen rt)
  target_link_libraries(strcpy rt)
  target_link_libraries(range_sort rt)
endif (HAVE_RT_LIB AND FAS_USE_RT_LIB)
