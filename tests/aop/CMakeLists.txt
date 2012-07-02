add_executable(test_advice_select    test_advice_select.cpp)
add_executable(test_find_advice      test_find_advice.cpp)
add_executable(test_aspect_hierarchy test_aspect_hierarchy.cpp)
add_executable(test_aspect_class     test_aspect_class.cpp)
add_executable(test_aspect_group     test_aspect_group.cpp)
add_executable(test_remove_advice    test_remove_advice.cpp)

add_test(aop_advice_select      test_advice_select)
add_test(aop_find_advice        test_find_advice)
add_test(aop_aspect_hierarchy   test_aspect_hierarchy)
add_test(aop_aspect_class       test_aspect_class)
add_test(aop_aspect_group       test_aspect_group)
add_test(aop_remove_advice      test_remove_advice)



