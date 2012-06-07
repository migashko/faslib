add_executable(test_xspan    test_xspan.cpp)
add_executable(test_nanotime test_nanotime.cpp)


if (HAVE_RT_LIB AND FAS_USE_RT_LIB)
  target_link_libraries(test_nanotime rt)
  target_link_libraries(test_xspan rt)
endif (HAVE_RT_LIB AND FAS_USE_RT_LIB)

add_test(xtime_xspan    test_xspan)
add_test(xtime_nanotime test_nanotime)
