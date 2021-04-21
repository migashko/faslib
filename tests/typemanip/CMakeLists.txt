add_executable(test_typemanip test_typemanip.cpp)
add_executable(test_conversion test_conversion.cpp)
add_executable(test_switch test_switch.cpp)
add_executable(test_tstring test_tstring.cpp)
add_executable(test_access test_access.cpp)
target_link_libraries(test_access PRIVATE fas::testing)

update_ogenc(TARGETS test_conversion WARNINGS -Wvirtual-inheritance OFF)
#target_ogenc_warning(test_conversion -Wvirtual-inheritance OFF)
wci_test(NAME typemanip              TARGET test_typemanip)
wci_test(NAME typemanip_conversion   TARGET test_conversion)
wci_test(NAME typemanip_switch       TARGET test_switch)
wci_test(NAME typemanip_tstring      TARGET test_tstring)
wci_test(NAME test_access            TARGET test_access)


