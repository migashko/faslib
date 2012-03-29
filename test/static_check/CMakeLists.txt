add_executable(static_check static_check.cpp)
add_executable(verifying verifying.cpp)

add_test(static_check static_check)
add_test(static_check_verifying verifying)


