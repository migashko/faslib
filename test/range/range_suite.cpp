#include <iostream>
#include <fas/testing.hpp>
#include <fas/range.hpp>
#include <fas/static_check/static_check.hpp>
#include <string>
#include <vector>



UNIT(range_unit, "")
{
  using namespace ::fas::testing;
};


BEGIN_SUITE(range_suite, "")
  ADD_UNIT(range_unit)
END_SUITE(range_suite)
