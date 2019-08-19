//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <iostream>

#include <fas/testing.hpp>
#include <fas/range.hpp>
#include <fas/static_check/static_check.hpp>
#include <fas/utility/useless_cast.hpp>
#include <string>
#include <vector>

UNIT(range_unit, "")
{
  using namespace ::fas::testing;
  int arr[]={1,2,3,4,5,6,7,8,9,10};

  fas::typerange<int*>::range r  = fas::range(arr);
  for (size_t i =0; i < sizeof(arr)/sizeof(int); ++i, ++r)
  {
    for (size_t j =0; j < sizeof(arr)/sizeof(int) - i; ++j)
    {
      t << equal<assert>( *r, arr[i] ) << FAS_TESTING_FILE_LINE;
      t << equal<assert, char>( r[j], arr[i+j] ) << FAS_TESTING_FILE_LINE;
    }
  }
}

UNIT(range2_unit, "")
{
  using namespace ::fas::testing;

  std::stringstream ss;
  for (size_t i =0; i < 10; ++i)
    ss << i ;

  fas::typerange<std::stringstream>::range r  = fas::range(ss);
  size_t i=0;
  for (; r; ++i, ++r)
    t << equal<assert, char>( *r, '0' + i ) << FAS_TESTING_FILE_LINE << std::endl << static_cast<int>(*r);
  t << equal<assert, size_t>( i, 10 ) << FAS_TESTING_FILE_LINE;
}

UNIT(irange_unit2, "")
{
  using namespace ::fas::testing;

  int arr[]={0,1,2,3,4,5,6,7,8,9};
  std::stringstream ss;
  for (size_t i =0; i < 10; ++i)
    ss << i ;

  std::vector<int> vect;
  vect.reserve(10);
  typedef fas::input_range_adapter< fas::typerange<std::stringstream>::range, std::vector<int> >  input_adapter;
  input_adapter r  = fas::irange(ss, vect);
  size_t i=0;
  for (; r; ++i, ++r)
  {
    input_adapter rr = r;
    for (size_t j =0; j < 10 - i; ++j, ++rr)
      t << equal<assert, int>( *rr, '0' + arr[i+j] ) << FAS_FL;
  }
  t << equal<assert, size_t>( i, 10 ) << FAS_FL;

}

UNIT(crange_unit, "")
{
  using namespace ::fas::testing;

  int arr[]={0,1,2,3,4,5,6,7,8,9};
  std::stringstream ss;
  for (size_t i =0; i < 10; ++i)
    ss << i ;

  std::vector<int> vect;
  vect.reserve(10);

  typedef fas::copy_range_adapter<
    fas::typerange<std::stringstream>::range,
    fas::typerange< std::vector<int> >::orange
  >  copy_adapter;

  copy_adapter r  = copy_adapter( fas::range(ss), fas::orange(vect) );
  size_t i=0;
  for (; r; ++i, ++r)
  {
    for (size_t j =0; j < vect.size(); ++j)
    {
      t << equal<assert>( vect[j], '0' +  arr[j] ) << FAS_TESTING_FILE_LINE << std::endl << "i==" << i << " j==" << j << ", "<< vect[j] << "!=" << '0' + arr[j];
      t << stop;
    }
  }
  t << equal<assert, size_t>( i, 10 ) << FAS_TESTING_FILE_LINE << std::endl << "i==" << i ;
}


BEGIN_SUITE(range_suite, "")
  ADD_UNIT(range_unit)
  ADD_UNIT(range2_unit)
  ADD_UNIT(irange_unit2)
  ADD_UNIT(crange_unit)
END_SUITE(range_suite)
