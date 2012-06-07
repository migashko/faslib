//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include "basic_suite.hpp"
#include <fas/testing.hpp>
#include <fas/range.hpp>
#include <fas/range/orange.hpp>

#include <fas/static_check/static_check.hpp>

#include <vector>
#include <set>
#include <list>
#include <iterator>
#include <sstream>
#include <iostream>


UNIT(range_vector_unit, "")
{
  using namespace ::fas::testing;
  
  std::vector<int> v;
  fas::typerange< std::vector<int>  >::orange ir = fas::orange( v );
  *ir++=1;
  *ir++=2;
  
  trivial_test( t, fas::range(v) );
  trivial_test(t, fas::range(v) );
  trivial_const_test( t, fas::range(v) );
  input_test(t, fas::range(v));
  output_test(t, fas::range(v));
  forward_test(t, fas::range(v));
  bidirectional_test(t, fas::range(v));
  random_access_test(t, fas::range(v));
  random_access_const_test(t, fas::range(v));
};

UNIT(range_set_unit, "")
{
  using namespace ::fas::testing;

  std::set<int> v;
  fas::typerange< std::set<int>  >::orange ir = fas::orange( v );
  *ir++=1;
  *ir++=2;
  trivial_const_test( t, fas::range(v) );
  input_test(t, fas::range(v));
  
  forward_test(t, fas::range(v));
  bidirectional_test(t, fas::range(v));
};

typedef int int_array[2];
typedef fas::typerange< int_array  >::orange range_type;

UNIT(range_array_unit, "")
{
  using namespace ::fas::testing;

  int_array v={3, 4};
  
  range_type ir = fas::orange( v );
  *ir++=1;
  *ir++=2;

  trivial_test( t, fas::range(v) );
  trivial_test(t, fas::range(v) );
  trivial_const_test( t, fas::range(v) );
  input_test(t, fas::range(v));
  output_test(t, fas::range(v));
  forward_test(t, fas::range(v));
  bidirectional_test(t, fas::range(v));
  random_access_test(t, fas::range(v));
  random_access_const_test(t, fas::range(v));

  std::stringstream ss;

  fas::typerange< std::stringstream >::orange isr = fas::orange(ss);
  *(isr++) = 'a';
  *(isr++) = 'b';

  
  fas::typerange< std::stringstream >::range osr = fas::range(ss);
  t << equal<expect, char>( 'a', *(osr++) ) << FAS_TESTING_FILE_LINE;
  t << equal<expect, char>( 'b', *(osr++) ) << FAS_TESTING_FILE_LINE;
};


BEGIN_SUITE(basic2_suite, "")
  ADD_UNIT(range_vector_unit)
  ADD_UNIT(range_set_unit)
  ADD_UNIT(range_array_unit)
END_SUITE(basic2_suite)
