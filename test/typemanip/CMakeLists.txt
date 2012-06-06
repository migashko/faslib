add_executable(test_typemanip test_typemanip.cpp)
add_executable(test_conversion test_conversion.cpp)
add_executable(test_switch test_switch.cpp)
add_executable(test_tstring test_tstring.cpp)

add_test(typemanip    test_typemanip)
add_test(conversion   test_conversion)
add_test(switch       test_switch)
add_test(tstring      test_tstring)
