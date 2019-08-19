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
#include <sstream>
#include <fstream>

UNIT(stream_range_unit, "")
{
  using namespace ::fas::testing;

  std::ofstream fo("stream_range.txt");
  fas::typerange< std::ofstream >::orange ro( fas::orange( fas::orange(fo) ) );
  *ro++ = '1';
  *ro++ = '2';
  *ro++ = '3';

  {
    std::ifstream fi("stream_range.txt");
    fas::typerange< std::ifstream >::range ri = fas::range( fi );
    char ch = ri ? *ri++ : '!' ;
    t << equal<expect, char>( ch, '!' ) << FAS_TESTING_FILE_LINE << std::endl << ch ;
  }

  fo.close();
  std::ifstream fi("stream_range.txt");
  fas::typerange< std::ifstream >::range ri = fas::range( fi );
  t << equal<expect, char>( *ri++, '1' ) << FAS_TESTING_FILE_LINE;
  t << equal<expect, char>( *ri++, '2' ) << FAS_TESTING_FILE_LINE;
  t << equal<expect, char>( *ri++, '3' ) << FAS_TESTING_FILE_LINE;
}


BEGIN_SUITE(stream_range_suite, "")
  ADD_UNIT(stream_range_unit)
END_SUITE(stream_range_suite)
