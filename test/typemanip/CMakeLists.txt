add_executable(typemanip typemanip.cpp)
add_executable(conversion conversion.cpp)
add_executable(switch_case switch_case.cpp)
add_executable(tstring tstring.cpp)

add_test(typemanip              typemanip)
add_test(typemanip_conversion   conversion)
add_test(typemanip_switch_case  switch_case)
add_test(typemanip_tstring      tstring)
