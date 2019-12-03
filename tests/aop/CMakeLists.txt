add_executable(test_aop1 test_aop1.cpp)
add_executable(test_aop2 test_aop2.cpp)
add_executable(test_aop3 test_aop3.cpp)
add_executable(test_aop4 test_aop4.cpp)
add_executable(test_aop5 test_aop5.cpp)
add_executable(test_aop6 test_aop6.cpp)
add_executable(test_aop7 test_aop7.cpp)
add_executable(test_aop8 test_aop8.cpp)
add_executable(test_aop9 test_aop9.cpp)
add_executable(test_aop10 test_aop10.cpp)

wci_test(NAME aop1  COMMAND test_aop1)
wci_test(NAME aop2  COMMAND test_aop2)
wci_test(NAME aop3  COMMAND test_aop3)
wci_test(NAME aop4  COMMAND test_aop4)
wci_test(NAME aop5  COMMAND test_aop5)
wci_test(NAME aop6  COMMAND test_aop6)
wci_test(NAME aop7  COMMAND test_aop7)
wci_test(NAME aop8  COMMAND test_aop8)
wci_test(NAME aop9  COMMAND test_aop9)
wci_test(NAME aop10 COMMAND test_aop10)



