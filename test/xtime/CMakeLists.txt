add_executable(xspan xspan.cpp)
add_executable(nanotime nanotime.cpp)


if (HAVE_RT_LIB AND FAS_USE_RT_LIB)
  target_link_libraries(nanotime rt)
  target_link_libraries(xspan rt)
endif (HAVE_RT_LIB AND FAS_USE_RT_LIB)

add_test(xtime_xspan    xspan)
add_test(xtime_nanotime nanotime)


