#include <fas/testing.hpp>
#include <fas/serialization/json/ser/ad_integer.hpp>
#include <fas/serialization/json/ser/ad_boolean.hpp>
#include <fas/serialization/json/ser/ad_real.hpp>
#include <fas/serialization/json/meta/integer.hpp>
#include <fas/serialization/json/meta/boolean.hpp>
#include <fas/serialization/json/meta/real.hpp>

#include <fas/serialization/json/except/ad_except.hpp>

#include <fas/range/range.hpp>
#include <sstream>

#include <limits>

UNIT(ad_boolean_test, "test fas::serialization::json::ser::ad_boolean advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;


  bool value = false;
  std::string result;
  ad_boolean adb;

  t << is_true<expect>( adb.check(t, ::fas::json::boolean(), value) ) << FAS_TESTING_FILE_LINE;

  adb(t, ::fas::json::boolean(), value, init_range(result) );
  t << equal<expect>(result, "false" ) << FAS_TESTING_FILE_LINE;

  value = true;
  result.clear();
  adb(t, ::fas::json::boolean(), value, init_range(result) );
  t << is_true<expect>( adb.check(t, ::fas::json::boolean(), value) ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result, "true" ) << FAS_TESTING_FILE_LINE;

  int int_value = 0;
  result.clear();
  adb(t, ::fas::json::boolean(), int_value, init_range(result) );
  t << equal<expect>(result, "false" ) << FAS_TESTING_FILE_LINE;

  int_value = 1;
  result.clear();
  adb(t, ::fas::json::boolean(), int_value, init_range(result) );
  t << equal<expect>(result, "true" ) << FAS_TESTING_FILE_LINE;

  int_value = -1;
  result.clear();
  adb(t, ::fas::json::boolean(), int_value, init_range(result) );
  t << equal<expect>(result, "true" ) << FAS_TESTING_FILE_LINE;
}

template<typename I, typename AD, typename M,  typename T>
std::ostream& value_test(T& t, I val)
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;

  std::stringstream income;
  income << (sizeof(I) < 4 ? (int) val : val);
  
  AD number_advice;
  std::string result;
  t << is_true<expect>( number_advice.check(t, M(), val) ) << FAS_TESTING_FILE_LINE;
  number_advice(t, M(), val, init_range(result) );
  return t << equal<expect>(result, income.str() ) << result << "!=" << income.str() << ". ";
}

template<typename I, typename T>
void integer_test(T& t, const std::string& desctype = "")
{
  using namespace ::fas::json;
  using namespace ::fas::json::ser;

  value_test<I, ad_integer, integer>( t, static_cast<I>(0) )  << desctype << FAS_TESTING_FILE_LINE;
  value_test<I, ad_integer, integer>( t, static_cast<I>(1) )  << desctype << FAS_TESTING_FILE_LINE ;
  value_test<I, ad_integer, integer>( t, static_cast<I>(-1) )  << desctype << FAS_TESTING_FILE_LINE ;
  value_test<I, ad_integer, integer>( t, static_cast<I>(std::rand()) ) << desctype << FAS_TESTING_FILE_LINE  ;

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

  value_test<I, ad_integer, integer>( t, std::numeric_limits<I>::min() ) << desctype << FAS_TESTING_FILE_LINE ;
  value_test<I, ad_integer, integer>( t, std::numeric_limits<I>::max() ) << desctype << FAS_TESTING_FILE_LINE  ;
}

UNIT(ad_number_test, "test fas::serialization::json::ser::ad_number advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;

#define INTEGER_TEST(T) integer_test<T>(t, "for " #T ". ")

  INTEGER_TEST(int);
  INTEGER_TEST(unsigned int);
  INTEGER_TEST(char);
  INTEGER_TEST(unsigned char);
  INTEGER_TEST(wchar_t);
  INTEGER_TEST(short);
  INTEGER_TEST(unsigned short);
  INTEGER_TEST(long);
  INTEGER_TEST(unsigned long);
  INTEGER_TEST(long long);
  INTEGER_TEST(unsigned long long);
}


template<typename I, typename T>
void real_test(T& t, const std::string& desctype = "")
{
  using namespace ::fas::json;
  using namespace ::fas::json::ser;

  value_test<I, ad_real, real>( t, static_cast<I>(0))  << desctype << FAS_TESTING_FILE_LINE;
  value_test<I, ad_real, real>( t, static_cast<I>(1))  << desctype << FAS_TESTING_FILE_LINE ;
  value_test<I, ad_real, real>( t, static_cast<I>(-1))  << desctype << FAS_TESTING_FILE_LINE ;
  value_test<I, ad_real, real>( t, static_cast<I>(std::rand()) ) << desctype << FAS_TESTING_FILE_LINE  ;
  value_test<I, ad_real, real>( t, std::numeric_limits<I>::min() ) << desctype << FAS_TESTING_FILE_LINE ;
  value_test<I, ad_real, real>( t, std::numeric_limits<I>::max() ) << desctype << FAS_TESTING_FILE_LINE  ;
}


UNIT(ad_real_test, "test fas::serialization::json::ser::ad_real advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;
#define REAL_TEST(T) real_test<T>(t, "for " #T ". ")
  REAL_TEST(float);
  REAL_TEST(double);
  REAL_TEST(long double);
}

BEGIN_SUITE(number_serializer_suite, "number serializer suite")
  ADD_UNIT(ad_number_test)
  ADD_UNIT(ad_boolean_test)
  ADD_UNIT(ad_real_test)
  ADD_ADVICE( ::fas::json::_except_, ::fas::json::ad_except )
END_SUITE(number_serializer_suite)
