add_executable(advice_select advice_select.cpp)
add_executable(find_advice find_advice.cpp)
add_executable(aspect_hierarchy aspect_hierarchy.cpp)
add_executable(aspect_class aspect_class.cpp)
add_executable(aspect_group aspect_group.cpp)

add_test(aop find_advice)
add_test(aop aspect_hierarchy)
add_test(aop aspect_class)
add_test(aop aspect_group)



