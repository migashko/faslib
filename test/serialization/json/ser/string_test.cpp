#include <fas/testing.hpp>
#include <fas/serialization/json/ser/serialize_string.hpp>
#include <fas/serialization/json/ser/ad_string.hpp>
#include <fas/serialization/json/ser/ad_null.hpp>
#include <fas/serialization/json/except/ad_except.hpp>

#include <fas/serialization/json/meta/string.hpp>
#include <fas/range/range.hpp>
#include <fas/range/init_range.hpp>

template<typename T>
std::ostream& test_serialize_string(T& t, const std::string& from, const std::string& check)
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;

  std::string result;
  serialize_string(
    range( from.begin(), from.end() ),
    init_range( result )
  );

  return t << equal<expect>(check, result) << check <<"!=" << result;
}


template<typename T>
std::ostream& test_ad_string(T& t, const char* from, const std::string& check)
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;

  char result[1024]; //={0};

  ad_string ads;
  t << is_true<expect>( ads.check(t, string(), from) ) << FAS_TESTING_FILE_LINE;

   *( ads(t, string(), from, init_range( result ) ) ) = '\0';
  return t << equal<expect>(check, result) << check <<"!=" << result;
}

UNIT(serialize_string_test, "test serialize_string function")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;

  test_serialize_string(t, "", "\"\"") << FAS_TESTING_FILE_LINE;
  test_serialize_string(t, "test", "\"test\"") << FAS_TESTING_FILE_LINE;
  test_serialize_string(t, "\t", "\"\\t\"") << FAS_TESTING_FILE_LINE;
  test_serialize_string(t, "\rtest\n", "\"\\rtest\\n\"") << FAS_TESTING_FILE_LINE;
}


UNIT(ad_string_test, "test serializer::ad_number advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;

  test_ad_string(t, "", "\"\"") << FAS_TESTING_FILE_LINE;
  test_ad_string(t, "test", "\"test\"") << FAS_TESTING_FILE_LINE;
  test_ad_string(t, "\t", "\"\\t\"") << FAS_TESTING_FILE_LINE;
  test_ad_string(t, "\rtest\n", "\"\\rtest\\n\"") << FAS_TESTING_FILE_LINE;
}

BEGIN_SUITE(string_serializer_suite, "string serializer suite")
  ADD_UNIT(serialize_string_test)
  ADD_UNIT(ad_string_test)
  ADD_ADVICE( ::fas::json::_except_, ::fas::json::ad_except )
  ADD_ADVICE( ::fas::json::ser::_null_, ::fas::json::ser::ad_null )
END_SUITE(string_serializer_suite)
