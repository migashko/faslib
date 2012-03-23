#include <fas/testing.hpp>

#include <fas/serialization/json/ser/ad_raw.hpp>
#include <fas/serialization/json/ser/ad_range.hpp>
#include <fas/serialization/json/meta/raw.hpp>
#include <fas/serialization/json/meta/range.hpp>
#include <fas/serialization/json/parser/aspect.hpp>
#include <fas/range/range.hpp>


UNIT(raw_test, "raw serialize")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;
  std::string rawstr = "{  \"name\": [\"str\", 1, 2, false] }  ";
  std::string result;
  ad_raw adr;
  adr(t, raw(), rawstr, init_range(result) );
  t << equal<assert>( result, std::string("{\"name\":[\"str\",1,2,false]}") ) << "["<<result <<"]"<< FAS_TESTING_FILE_LINE;
}

UNIT(raw_range_test, "raw range serialize")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;
  const char rawstr[] = "{  \"name\": [\"str\", 1, 2, false] }  ";
  /*std::pair< random_access_range<char*>, random_access_range<char*> >  tmp;
  *(tmp.second++) = *(tmp.first++);*/
  
  random_access_range<const char*> r = ::fas::range(rawstr);
  std::string result;
  ad_range adr;
  adr(t, raw(), r, init_range(result) );
  t << equal<assert>( std::string(result.begin(), result.end()) , std::string("{\"name\":[\"str\",1,2,false]}") ) << "["<<result <<"]"<< FAS_TESTING_FILE_LINE;
}


BEGIN_SUITE(raw_serializer_suite, "raw serializer suite")
  ADD_UNIT(raw_test)
  ADD_UNIT(raw_range_test)
  ADD_ASPECT(::fas::json::parser::aspect)
END_SUITE(raw_serializer_suite)
