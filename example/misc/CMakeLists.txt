add_executable(colorized colorized.cpp)
add_executable(xtime xtime.cpp)

#ADD_DEFINITIONS(xtime -DFAS_USE_RT_LIB)
#target_link_libraries(xtime rt)
if (HAVE_RT_LIB AND FAS_USE_RT_LIB)
  target_link_libraries(xtime rt)
endif (HAVE_RT_LIB AND FAS_USE_RT_LIB)

