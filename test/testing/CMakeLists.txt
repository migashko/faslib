add_executable(unit unit.cpp)
add_executable(statements statements.cpp)
add_executable(suite suite.cpp)
add_executable(suite_run suite_run.cpp)
add_executable(suite_map suite_map.cpp)

add_test(testing unit)
add_test(testing statements)
add_test(testing suite)
add_test(testing suite_run)
#add_test(testing suite_map)

SUBDIRS(final)
