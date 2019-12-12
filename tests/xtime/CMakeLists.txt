add_executable(test_xspan    test_xspan.cpp)
add_executable(test_nanotime test_nanotime.cpp)

if (HAVE_RT_LIB)
  target_link_libraries(test_nanotime PRIVATE rt)
  target_link_libraries(test_xspan PRIVATE rt)
endif ()

wci_test(NAME test_xspan    TARGET test_xspan)
wci_test(NAME test_nanotime TARGET test_nanotime)

#add_test(NAME test_xspan-leak TARGET valgrind --leak-check=full --error-exitcode=1 ./test_xspan)
#add_test(NAME test_test_nanotime TARGET valgrind --leak-check=full --error-exitcode=1 ./test_nanotime)
