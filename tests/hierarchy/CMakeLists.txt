add_executable(test_hierarchy test_hierarchy.cpp)
target_link_libraries(test_hierarchy PRIVATE faslib)
wci_test(NAME hierarchy TARGET test_hierarchy)
