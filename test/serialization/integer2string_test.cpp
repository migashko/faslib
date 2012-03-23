#include <fas/testing.hpp>

#include <fas/serialization/integer2string.hpp>
//#include <fas/range/range.hpp>
#include <limits>

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

UNIT(integer2string_int, "test integer2string for int")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  
  integer2string<int> int2str;
  int2str = 0;
  t << equal_str<expect>( "0", int2str.c_str() ) << "0!=" << int2str.c_str();
  int2str = 1;
  t << equal_str<expect>( "1", int2str.c_str() ) << "1!=" << int2str.c_str();
  int2str = -1;
  t << equal_str<expect>( "-1", int2str.c_str() ) << "-1!=" << int2str.c_str();
  int2str = /*2147483647*/std::numeric_limits<int>::max();
  t << equal_str<expect>( "2147483647", int2str.c_str() ) << "2147483647!=" << int2str.c_str();
  int2str = /*-2147483648 + 1*/std::numeric_limits<int>::min();
  t << equal_str<expect>( "-2147483648", int2str.c_str() ) << "-2147483648!=" << int2str.c_str();
  
  /*
  using namespace ::fas::json;
  using namespace ::fas::json::serializer;
  */

  /*
  ad_number_integer number_serializer;
  number<long> ni;
  long value = -123445334534L;
  std::string str;

  number_serializer( t, ni, value, (std::back_inserter(str) ) );
  
  t << message(str);
  */
}

BEGIN_SUITE(integer2string_suite, "integer2string suite")
  ADD_UNIT(integer2string_int)
END_SUITE(integer2string_suite)
