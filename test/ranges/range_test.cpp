#include "basic_test.hpp"
#include <fas/testing.hpp>
#include <fas/range.hpp>

#include <fas/static_check/static_check.hpp>

#include <vector>
#include <set>
#include <list>
#include <iterator>
#include <sstream>
#include <iostream>


UNIT(range_vector_test, "test range( vector<int> )")
{
  using namespace ::fas::testing;
  
  std::vector<int> v;
  fas::range_traits< std::vector<int>  >::init_range ir = fas::init_range( v );
  *ir++=1;
  *ir++=2;
  // v.push_back(1); v.push_back(2);
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

UNIT(range_set_test, "test range( set<int> )")
{
  using namespace ::fas::testing;

  std::set<int> v;
  fas::range_traits< std::set<int>  >::init_range ir = fas::init_range( v );
  *ir++=1;
  *ir++=2;
  trivial_const_test( t, fas::range(v) );
  input_test(t, fas::range(v));
  // output_test(t, fas::range(v));
  forward_test(t, fas::range(v));
  bidirectional_test(t, fas::range(v));
  // random_access_const_test(t, fas::range(v));
};

typedef int int_array[2];
typedef fas::range_traits< int_array  >::init_range range_type;

UNIT(range_array_test, "test range( int[2] )")
{
  using namespace ::fas::testing;

  int_array v={3, 4};
  
  range_type ir = fas::init_range( v );
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


BEGIN_SUITE(range_suite, "make range suite")
  ADD_UNIT(range_vector_test)
  ADD_UNIT(range_set_test)
  ADD_UNIT(range_array_test)
END_SUITE(range_suite)
