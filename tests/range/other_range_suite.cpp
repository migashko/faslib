//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <iostream>
#include <fas/testing.hpp>
#include <fas/range.hpp>
#include <fas/static_check/static_check.hpp>
#include <string>
#include <vector>


UNIT(other_range_unit, "")
{
  using namespace ::fas::testing;

  typedef fas::typerange<int>::range int_range;
  typedef fas::typerange<int>::orange int_orange;
  int value = 10;
  int_range r = fas::range(value);
  t << equal<expect>(*r, 10) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(value, 10) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( fas::begin(r), &value) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( fas::end(r), &value + 1) << FAS_TESTING_FILE_LINE;
  ++(*r);
  t << equal<expect>(*r, 11) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(value, 11) << FAS_TESTING_FILE_LINE;
  *r = 22;
  t << equal<expect>(*r, 22) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(value, 22) << FAS_TESTING_FILE_LINE;
  ++r;
  t << is_false<expect>( r ) << FAS_TESTING_FILE_LINE;
  --r;
  t << is_true<expect>( r ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(*r, 22) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(value, 22) << FAS_TESTING_FILE_LINE;

  int_orange ro = fas::orange(value);
  t << equal<expect>(*ro, 22) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(value, 22) << FAS_TESTING_FILE_LINE;
  *ro = 23;
  t << equal<expect>(*ro, 23) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(value, 23) << FAS_TESTING_FILE_LINE;

  ro = fas::orange(value, true);
  t << equal<expect>(*ro, 0) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(value, 0) << FAS_TESTING_FILE_LINE;
}


BEGIN_SUITE(other_range_suite, "")
  ADD_UNIT(other_range_unit)
END_SUITE(other_range_suite)
