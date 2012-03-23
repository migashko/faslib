#include <fas/testing.hpp>
#include <fas/serialization/json/deser/deserialize_string.hpp>
#include <fas/serialization/json/deser/ad_string.hpp>
#include <fas/serialization/json/meta/string.hpp>
#include <fas/serialization/json/meta/tstring.hpp>
#include <fas/range/range.hpp>

#include <fas/serialization/json/parser/aspect.hpp>

template<typename T>
std::ostream& test_deserialize_string(T& t, const std::string& from, const std::string& check)
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  std::string result;
  try
  {
    deserialize_string(
      init_range( result ),
      range( from.begin(), from.end() )
    );

    return t << equal<expect>(check, result) << "[" << check <<"!=" << result << "]";
  }
  catch(const json_error& e)
  {
    std::cout << "[" << from << "]" << std::endl;
    std::cout << e.message( range(from) ) << std::endl;
    throw e;
  }
}

template<typename T>
std::ostream& test_ad_string(T& t, const char* from, const std::string& check)
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  //typedef char result_type[128];
  char result[128] = /*{}*/"12345";
//  result = result_type();
  /*for (int i = 0 ; i < sizeof(result) - 1 ; ++i)
    result[i]='a';*/

  ad_string ads;
  t << is_true<expect>( ads.check(t, string(), from) ) << FAS_TESTING_FILE_LINE;

  ads(t, string(), result, srange(from) );

  return t << equal<expect>(check, std::string(result) ) << "[" << check <<"!=" << result << "]";
}

UNIT(deserialize_string_test, "test deserialize_string function")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  /*test_deserialize_string(t, "", "" ) << FAS_TESTING_FILE_LINE;
  test_deserialize_string(t, 0, "" ) << FAS_TESTING_FILE_LINE;
  */
  test_deserialize_string(t, "\"\"", "" ) << FAS_TESTING_FILE_LINE;
  test_deserialize_string(t, "\"test\"", "test" ) << FAS_TESTING_FILE_LINE;
  test_deserialize_string(t, "\"\\t\"", "\t" ) << FAS_TESTING_FILE_LINE;
  test_deserialize_string(t, "\"\\rtest\\n\"", "\rtest\n" ) << FAS_TESTING_FILE_LINE;
}

UNIT(ad_string_test, "test ad_string advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  test_ad_string(t, "\"\"", "") << FAS_TESTING_FILE_LINE;
  test_ad_string(t, "\"test\"", "test") << FAS_TESTING_FILE_LINE;
  test_ad_string(t, "\"\\t\"", "\t" ) << FAS_TESTING_FILE_LINE;
  test_ad_string(t, "\"\\rtest\\n\"", "\rtest\n" ) << FAS_TESTING_FILE_LINE;
}

BEGIN_SUITE(string_deserialize_suite, "string deserializer suite")
  ADD_UNIT(deserialize_string_test)
  ADD_UNIT(ad_string_test)
  ADD_ASPECT(::fas::json::parser::aspect)
END_SUITE(string_deserialize_suite)
