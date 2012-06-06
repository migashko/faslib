#include <fas/testing.hpp>
#include <fas/serialization/json/deser/ad_integer.hpp>
#include <fas/serialization/json/deser/ad_boolean.hpp>
#include <fas/serialization/json/deser/ad_real.hpp>
#include <fas/serialization/json/meta/integer.hpp>
#include <fas/serialization/json/meta/boolean.hpp>
#include <fas/serialization/json/meta/real.hpp>

#include <fas/serialization/json/parser/aspect.hpp>

#include <fas/range/range.hpp>
#include <sstream>
#include <limits>

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif


namespace aj = ::fas::json;

UNIT(ad_boolean_test, "test fas::json::deser::ad_boolean advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  
  ad_boolean adb;
  std::string value = "false";
  bool result = true;

  t << is_true<expect>( adb.check(t, aj::boolean(), range(value) ) ) << FAS_TESTING_FILE_LINE;
  adb(t, aj::boolean(), result, range(value) );
  t << equal<expect>(result, false ) << FAS_TESTING_FILE_LINE;

  value = "true";
  result = false;
  t << is_true<expect>( adb.check(t, aj::boolean(), range(value) ) ) << FAS_TESTING_FILE_LINE;
  adb(t, aj::boolean(), result, range(value) );
  t << equal<expect>(result, true ) << FAS_TESTING_FILE_LINE;

  value = "true";
  int int_result = -1;
  adb(t, aj::boolean(), int_result, range(value) );
  t << equal<expect>(int_result, 1 ) << FAS_TESTING_FILE_LINE;

  value = "false";
  int_result = -1;
  adb(t, aj::boolean(), int_result, range(value) );
  t << equal<expect>(int_result, 0 ) << FAS_TESTING_FILE_LINE;

}


template<typename I, typename AD, typename M,  typename T>
std::ostream& value_test(T& t, I val, I rng = I() )
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  std::stringstream income;
  income << (sizeof(I) < 4 ? (int) val : val );
  AD number_advice;
  I result = I();
  t << is_true<expect>( number_advice.check(t, M(), range(income.str()) ) ) << FAS_TESTING_FILE_LINE;
  std::cout << income.str() << std::endl;
  std::string incomestr = income.str();
  std::cout << "[" << incomestr << "]" << std::endl;
  number_advice(t, M(), result, range(incomestr) );
  // return t << equal<expect>(result, val ) << result << "!=" << val << ". ";
  return t << is_true<expect>( result == val || ( (result > val - rng) && (result < val + rng) ) ) << result << "!=" << val << ". ";
}


template<typename I, typename T>
void integer_test(T& t, const std::string& desctype = "")
{
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  value_test<I, ad_integer, integer>( t, static_cast<I>(0) ) << desctype << FAS_TESTING_FILE_LINE;
  value_test<I, ad_integer, integer>( t, static_cast<I>(1) ) << desctype << FAS_TESTING_FILE_LINE ;
  value_test<I, ad_integer, integer>( t, static_cast<I>(-1) )  << desctype << FAS_TESTING_FILE_LINE ;
  value_test<I, ad_integer, integer>( t, std::numeric_limits<I>::min() ) << desctype << FAS_TESTING_FILE_LINE ;
  value_test<I, ad_integer, integer>( t, static_cast<I>(std::rand()) ) << desctype << FAS_TESTING_FILE_LINE  ;
  value_test<I, ad_integer, integer>( t, std::numeric_limits<I>::max() ) << desctype << FAS_TESTING_FILE_LINE  ;
}

UNIT(ad_number_test, "test fas::json::deser::ad_number advice")
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
  using namespace ::fas::json::deser;

  value_test<I, ad_real, real>( t, static_cast<I>(0) )  << desctype << FAS_TESTING_FILE_LINE;
  value_test<I, ad_real, real>( t, static_cast<I>(1) )  << desctype << FAS_TESTING_FILE_LINE ;
  value_test<I, ad_real, real>( t, static_cast<I>(-1) )  << desctype << FAS_TESTING_FILE_LINE ;
  value_test<I, ad_real, real>( t, static_cast<I>(std::rand()%100), static_cast<I>(0.1) ) << desctype << FAS_TESTING_FILE_LINE  ;
  value_test<I, ad_real, real>( t, std::numeric_limits<I>::min()*10,
                                   std::numeric_limits<I>::min()/1000 ) << desctype << FAS_TESTING_FILE_LINE ;
  value_test<I, ad_real, real>( t, std::numeric_limits<I>::max(),
                                   std::numeric_limits<I>::max()/1000 ) << desctype << FAS_TESTING_FILE_LINE  ;
  
}


UNIT(ad_real_test, "test fas::json::deser::ad_real advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;
#define REAL_TEST(T) real_test<T>(t, "for " #T ". ")
  REAL_TEST(float);
  REAL_TEST(double);
  REAL_TEST(long double);
}


BEGIN_SUITE(number_deserialize_suite, "number deserializer suite")
  ADD_UNIT(ad_boolean_test)
  ADD_UNIT(ad_number_test)
  ADD_UNIT(ad_real_test)
  ADD_ASPECT(::fas::json::parse::aspect)
END_SUITE(number_deserialize_suite)
