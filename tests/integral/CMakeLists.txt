add_executable(test_integral test_integral.cpp)
add_executable(test_comparisons test_comparisons.cpp)
add_executable(test_arithmetic test_arithmetic.cpp)
add_executable(test_logical_op test_logical_op.cpp)

wci_test(NAME integral             COMMAND test_integral)
wci_test(NAME integral_comparisons COMMAND test_comparisons)
wci_test(NAME integral_arithmetic  COMMAND test_arithmetic)
wci_test(NAME integral_logical_op  COMMAND test_logical_op)


