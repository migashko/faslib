add_executable(test_xspan    test_xspan.cpp)
add_executable(test_nanotime test_nanotime.cpp)

if (HAVE_RT_LIB)
  target_link_libraries(test_nanotime rt)
  target_link_libraries(test_xspan rt)
endif ()

add_test(test_xspan    test_xspan)
add_test(test_nanotime test_nanotime)

add_test(NAME test_xspan-leak COMMAND valgrind --leak-check=full --error-exitcode=1 ./test_xspan)
add_test(NAME test_test_nanotime COMMAND valgrind --leak-check=full --error-exitcode=1 ./test_nanotime)
