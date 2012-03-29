add_executable(unit unit.cpp)
add_executable(statements statements.cpp)
add_executable(suite suite.cpp)
add_executable(suite_run suite_run.cpp)
add_executable(suite_map suite_map.cpp)

add_test(testing_unit       unit)
add_test(testing_statements statements)
add_test(testing_suite      suite)
add_test(testing_suite_run  suite_run)
add_test(testing_suite_map  suite_map)

SUBDIRS(final)
