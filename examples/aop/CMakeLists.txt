add_executable(foo foo.cpp)
add_executable(oop_duck oop_duck.cpp)
add_executable(aop_duck aop_duck.cpp)
add_executable(aop_duck2 aop_duck2.cpp)
add_executable(aop_error aop_error.cpp)

wci_remove_options(-Wsuggest-override -Wsuggest-override -Wnon-virtual-dtor)
wci_targets(foo oop_duck aop_duck aop_duck2 aop_error)


