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


UNIT(iterator_range_unit, "")
{
  using namespace ::fas::testing;
  typedef std::vector<int> vint_type;

  vint_type vint;
  const vint_type& vintc = vint;
  for (int i=0; i < 5; ++i)
    vint.push_back(i);

  typedef fas::typerange<vint_type::iterator>::range vint_range;
  vint_range r1 = fas::range( vint.begin(), vint.end() );
  for (int i=0; i < 5; ++i, ++r1)
    t << equal<expect>( *r1, i ) << FAS_TESTING_FILE_LINE;

  typedef fas::typerange<vint_type::const_iterator>::range vint_crange;
  vint_crange cr1 = fas::range( vintc.begin(), vintc.end() );
  // error: assignment of read-only location ‘cr1.fas::random_access_range<T>::operator*
  // *cr1 = 33;
  for (int i=0; i < 5; ++i, ++cr1)
    t << equal<expect>( *cr1, i ) << FAS_TESTING_FILE_LINE;


  typedef fas::typerange<vint_type::reverse_iterator >::range vint_rrange;
  vint_rrange rr = fas::range( vint.rbegin(), vint.rend() );

  for (int i=0; i < 5; ++i, ++rr)
    t << equal<expect>( *rr, 5 - i -1 ) << FAS_TESTING_FILE_LINE
      << std::endl << (5 - i -1) << "!=" << *rr ;
  ;

  typedef std::back_insert_iterator<vint_type> vint_bii_type;
  typedef fas::typerange< vint_bii_type >::range rbi_type;
  rbi_type rbi = fas::range( vint_bii_type(vint) );
  *rbi = 5;
  t << equal<expect, size_t>( vint.size(), 6 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( vint[5], 5 ) << FAS_TESTING_FILE_LINE;

  // error: ‘orange’ in ‘struct fas::typerange<std::back_insert_iterator<std::vector<int> > >’ does not name a type
  //typedef fas::typerange< vint_bii_type >::orange rbio_type;



}


BEGIN_SUITE(iterator_range_suite, "")
  ADD_UNIT(iterator_range_unit)
END_SUITE(iterator_range_suite)
