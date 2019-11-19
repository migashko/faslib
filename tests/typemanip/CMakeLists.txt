add_executable(test_typemanip test_typemanip.cpp)
add_executable(test_conversion test_conversion.cpp)
add_executable(test_switch test_switch.cpp)
add_executable(test_tstring test_tstring.cpp)
add_executable(test_access ${FAS_TESTING_CPP} test_access.cpp)

wci_remove_options(-Wno-virtual-inheritance)
wci_test(NAME typemanip              COMMAND test_typemanip)
wci_test(NAME typemanip_conversion   COMMAND test_conversion)
wci_test(NAME typemanip_switch       COMMAND test_switch)
wci_test(NAME typemanip_tstring      COMMAND test_tstring)
wci_test(NAME test_access            COMMAND test_access)


