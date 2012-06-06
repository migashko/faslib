add_executable(
  adv_test
  ${CMAKE_SOURCE_DIR}/fas/testing/testing.cpp
  adv_test.cpp
  test_managers.cpp
)
add_test(adv adv_test)


