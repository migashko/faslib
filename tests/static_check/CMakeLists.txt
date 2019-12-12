add_executable(test_static_check test_static_check.cpp)
add_executable(test_static_error test_static_error.cpp)

wci_test(NAME static_check TARGET test_static_check)
wci_test(NAME static_error TARGET test_static_error)


