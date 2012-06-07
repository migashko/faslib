add_executable(test_static_check test_static_check.cpp)
add_executable(test_static_error test_static_error.cpp)

add_test(static_check test_static_check)
add_test(static_error test_static_error)


