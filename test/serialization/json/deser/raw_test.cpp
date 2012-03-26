#include <fas/testing.hpp>

#include <fas/serialization/json/deser/ad_raw.hpp>
#include <fas/serialization/json/meta/raw.hpp>
#include <fas/range/range.hpp>
#include <fas/serialization/json/parser/aspect.hpp>

UNIT(raw_test, "deserialize raw value")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;
  
  const char rawstr[] = "{  \"name\": [\"str\", 1, 2, false] }  ";
  std::string result;
  ad_raw adr;
  adr(t, raw(), result, range(rawstr) );
  t << equal<assert>( std::string(result.begin(), result.end()) , std::string("{\"name\":[\"str\",1,2,false]}") ) << "["<<result <<"]"<< FAS_TESTING_FILE_LINE;
}

BEGIN_SUITE(raw_deserialize_suite, "raw deserializer suite")
  ADD_UNIT(raw_test)
  ADD_ASPECT(::fas::json::parse::aspect)
END_SUITE(raw_deserialize_suite)
