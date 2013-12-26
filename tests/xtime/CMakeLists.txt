add_executable(test_xspan    test_xspan.cpp)
add_executable(test_nanotime test_nanotime.cpp)

if (UNIX AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.8" AND HAVE_CLOCK_GETTIME_FUNC)
  target_link_libraries(test_nanotime rt)
  target_link_libraries(test_xspan rt)
endif ()

add_test(xtime_xspan    test_xspan)
add_test(xtime_nanotime test_nanotime)
