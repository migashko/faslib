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

namespace {

const int BUFF_SIZE = 10;
typedef char buffer_type[BUFF_SIZE];
buffer_type buffer;

UNIT(pointer_range_unit, "")
{
  using namespace ::fas::testing;
  char* pbeg = buffer;
  char* pend = buffer + BUFF_SIZE;
  const char* pcbeg = pbeg;
  const char* pcend = pend;

  typedef fas::typerange<char*>::range ptr_range_type;
  ptr_range_type pr1 = fas::range(pbeg, pend);

  for (int i =0 ; i < BUFF_SIZE; ++i)
    *(pr1++) = char(i);

  t << equal<expect, size_t>( fas::distance(pr1), 0 ) << FAS_TESTING_FILE_LINE;
  pr1 -= BUFF_SIZE;
  t << equal<expect, size_t>( fas::distance(pr1), BUFF_SIZE ) << FAS_TESTING_FILE_LINE
    << std::endl << fas::distance(pr1);

  for (int i =0 ; i < BUFF_SIZE; ++i)
    t << equal<expect>( i, pr1[i] ) << FAS_TESTING_FILE_LINE << " pr1[" << i << "]=" << int( pr1[i] );

  typedef fas::typerange<const char*>::range ptr_crange_type;
  ptr_crange_type::reverse_range pcrr = fas::range(pcbeg, pcend).reverse();

  for (int i =0 ; i < BUFF_SIZE; ++i)
    t << equal<expect>( BUFF_SIZE-i-1, pcrr[i] ) << FAS_TESTING_FILE_LINE << " pcrr1[" << BUFF_SIZE-i-1 << "]=" << int( pcrr[i] );

}

}

BEGIN_SUITE(pointer_range_suite, "")
  ADD_UNIT(pointer_range_unit)
END_SUITE(pointer_range_suite)
