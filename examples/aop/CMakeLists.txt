if (MSVC )
    add_compile_options(-wd4020 -wd4250)
endif()

add_executable(foo foo.cpp)
add_executable(oop_duck oop_duck.cpp)
add_executable(aop_duck aop_duck.cpp)
add_executable(aop_duck2 aop_duck2.cpp)
add_executable(aop_error aop_error.cpp)

update_ogenc(TARGETS oop_duck aop_duck WARNINGS -Wsuggest-override -Wnon-virtual-dtor OFF)
wci_utils(foo oop_duck aop_duck aop_duck2 aop_error)


