add_executable(integral integral.cpp)
add_executable(comparisons comparisons.cpp)
add_executable(arithmetic arithmetic.cpp)
add_executable(logical_op logical_op.cpp)

add_test(integral integral)
add_test(integral_comparisons comparisons)
add_test(integral_arithmetic  arithmetic)
add_test(integral_logical_op  logical_op)


