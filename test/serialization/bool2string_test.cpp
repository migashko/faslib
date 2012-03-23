#include <fas/testing.hpp>

#include <fas/serialization/bool2string.hpp>
//#include <fas/range/.hpp>
#include <limits>

UNIT(bool2string_test, "test bool2string ")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  
  bool2string<> bool2str;
  t << equal_str<expect>( "false", bool2str.c_str() ) << "false!=" << bool2str.c_str();
  bool2str = false;
  t << equal_str<expect>( "false", bool2str.c_str() ) << "false!=" << bool2str.c_str();
  bool2str = true;
  t << equal_str<expect>( "true", bool2str.c_str() ) << "true!=" << bool2str.c_str();
}

BEGIN_SUITE(bool2string_suite, "bool2string_int suite")
  ADD_UNIT(bool2string_test)
END_SUITE(bool2string_suite)
