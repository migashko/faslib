add_executable(advice_select advice_select.cpp)
add_executable(find_advice find_advice.cpp)
add_executable(aspect_hierarchy aspect_hierarchy.cpp)
add_executable(aspect_class aspect_class.cpp)
add_executable(aspect_group aspect_group.cpp)
# add_executable(performance_compile1 performance_compile1.cpp)

add_test(advice_select      advice_select)
add_test(find_advice        find_advice)
add_test(aspect_hierarchy   aspect_hierarchy)
add_test(aspect_class       aspect_class)
add_test(aspect_group       aspect_group)



