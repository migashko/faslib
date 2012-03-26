#include <fas/testing.hpp>

#include <fas/serialization/json/parser/ad_value.hpp>
#include <fas/serialization/json/parser/ad_array.hpp>
#include <fas/serialization/json/parser/ad_member.hpp>
#include <fas/serialization/json/parser/ad_member.hpp>
#include <fas/serialization/json/parser/ad_boolean.hpp>
#include <fas/serialization/json/parser/ad_object.hpp>

#include <fas/serialization/json/except/ad_except.hpp>
#include <fas/serialization/json/except/tags.hpp>
#include <fas/range.hpp>
#include <fstream>
#include <iostream>
#include <iterator>


UNIT(value_test, "parse value")
{
  using namespace fas;
  using namespace fas::testing;
  using namespace fas::json::parse;

  ad_value adv;
  std::string s = "null bla-bla";
  typedef random_access_range<std::string::const_iterator> range_type;
  range_type r( s.begin(), s.end() );

  r = adv(t, r);
  std::string tail(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;

  s = "false bla-bla";
  r = range_type( s.begin(), s.end() );

  r = adv(t, r);
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;

  s = "-127e+2 bla-bla";
  r = range_type( s.begin(), s.end() );

  r = adv(t, r);
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;

  s = "\"строка\" bla-bla";
  r = range_type( s.begin(), s.end() );

  r = adv(t, r);
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
}

UNIT(copy_value_test, "copy parse value")
{
  using namespace fas;
  using namespace fas::testing;
  using namespace fas::json::parse;

  ad_value adv;
  std::string s = "null bla-bla";
  std::string result;
  typedef random_access_range<std::string::const_iterator> range_type;
  range_type r( s.begin(), s.end() );

  r = adv(t, r, init_range(result) ).first;
  std::string tail(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "null", result ) << FAS_TESTING_FILE_LINE;

  result.clear();
  s = "false bla-bla";
  r = range_type( s.begin(), s.end() );

  r = adv(t, r, init_range(result)).first;
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "false", result ) << FAS_TESTING_FILE_LINE;

  result.clear();
  s = "-127e+2 bla-bla";
  r = range_type( s.begin(), s.end() );

  r = adv(t, r, init_range(result)).first;
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "-127e+2", result ) << FAS_TESTING_FILE_LINE;

  result.clear();
  s = "\"строка\" bla-bla";
  r = range_type( s.begin(), s.end() );

  r = adv(t, r, init_range(result)).first;
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "\"строка\"", result ) << FAS_TESTING_FILE_LINE;
}

UNIT(array_test, "parse array")
{
  using namespace fas;
  using namespace fas::testing;
  using namespace fas::json::parse;

  ad_value adv;
  std::string s = "[] bla-bla";
  typedef random_access_range<std::string::const_iterator> range_type;
  range_type r( s.begin(), s.end() );

  r = adv(t, r);
  std::string tail(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;

  s = "[null] bla-bla";
  r = range_type( s.begin(), s.end() );

  r = adv(t, r);
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;

  s = "[1,true,null] bla-bla";
  r = range_type( s.begin(), s.end() );

  r = adv(t, r);
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;

  s = "[/*комментарий*/\"1\",   true, -1000 ] bla-bla";
  r = range_type( s.begin(), s.end() );

  r = adv(t, r);
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;

  s = "[[[[]]]] bla-bla";
  r = range_type( s.begin(), s.end() );
  r = adv(t, r);
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;

  s = "[[[[null],1]]] bla-bla";
  r = range_type( s.begin(), s.end() );
  r = adv(t, r);
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
}

UNIT(copy_array_test, "parse array")
{
  using namespace fas;
  using namespace fas::testing;
  using namespace fas::json::parse;

  ad_value adv;
  std::string s = "[] bla-bla";
  std::string result;
  typedef random_access_range<std::string::const_iterator> range_type;
  range_type r( s.begin(), s.end() );

  r = adv(t, r, init_range(result) ).first;
  std::string tail(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "[]", result ) << FAS_TESTING_FILE_LINE;

  s = "[null] bla-bla";
  result.clear();
  r = range_type( s.begin(), s.end() );

  r = adv(t, r, init_range(result) ).first;
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "[null]", result ) << FAS_TESTING_FILE_LINE;

  s = "[1,true,null] bla-bla";
  result.clear();
  r = range_type( s.begin(), s.end() );

  r = adv(t, r, init_range(result) ).first;
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "[1,true,null]", result ) << FAS_TESTING_FILE_LINE;

  s = "[/*комментарий*/\"1\",   true, -1000 ] bla-bla";
  result.clear();
  r = range_type( s.begin(), s.end() );
  r = adv(t, r, init_range(result) ).first;
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "[\"1\",true,-1000]", result ) << FAS_TESTING_FILE_LINE;

  s = "[[[[]]]] bla-bla";
  result.clear();
  r = range_type( s.begin(), s.end() );
  r = adv(t, r, init_range(result) ).first;
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "[[[[]]]]", result ) << FAS_TESTING_FILE_LINE;

  s = "[[[[null],1]]] bla-bla";
  result.clear();
  r = range_type( s.begin(), s.end() );
  r = adv(t, r, init_range(result) ).first;
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "[[[[null],1]]]", result ) << FAS_TESTING_FILE_LINE;
}


UNIT(member_test, "parse member")
{
  using namespace fas;
  using namespace fas::testing;
  using namespace fas::json::parse;

  ad_member adm;
  std::string s = "\"name\":null bla-bla";
  typedef random_access_range<std::string::const_iterator> range_type;
  range_type r( s.begin(), s.end() );

  r = adm(t, r);
  std::string tail(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;

  s = "\"name\":null bla-bla";
  r = range_type( s.begin(), s.end() );

  r = adm(t, r);
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;

  s = "\"name\":false bla-bla";
  r = range_type( s.begin(), s.end() );

  r = adm(t, r);
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;

  s = "\"name\": /**/ 1234 bla-bla";
  r = range_type( s.begin(), s.end() );

  r = adm(t, r);
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;

  s = "\"name\":[1, 2, 3, \"test\"] bla-bla";
  r = range_type( s.begin(), s.end() );
  r = adm(t, r);
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;

  s = "\"name\":[[],[]] bla-bla";
  r = range_type( s.begin(), s.end() );
  r = adm(t, r);
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
}

UNIT(copy_member_test, "copy parse member")
{
  using namespace fas;
  using namespace fas::testing;
  using namespace fas::json::parse;

  ad_member adm;
  std::string s = "\"name\":null bla-bla";
  std::string result;
  typedef random_access_range<std::string::const_iterator> range_type;
  range_type r( s.begin(), s.end() );

  r = adm(t, r, init_range(result) ).first;
  std::string tail(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "\"name\":null", result ) << "[" << result << "]" << FAS_TESTING_FILE_LINE;

  s = "\"name\":null bla-bla";
  result.clear();
  r = range_type( s.begin(), s.end() );

  r = adm(t, r, init_range(result) ).first;
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "\"name\":null", result ) << FAS_TESTING_FILE_LINE;

  s = "\"name\":false bla-bla";
  result.clear();
  r = range_type( s.begin(), s.end() );

  r = adm(t, r, init_range(result) ).first;
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "\"name\":false", result ) << FAS_TESTING_FILE_LINE;

  s = "\"name\": /**/ 1234 bla-bla";
  result.clear();
  r = range_type( s.begin(), s.end() );

  r = adm(t, r, init_range(result) ).first;
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "\"name\":1234", result ) << FAS_TESTING_FILE_LINE;

  s = "\"name\":[1, 2, 3, \"test\"] bla-bla";
  result.clear();
  r = range_type( s.begin(), s.end() );
  r = adm(t, r, init_range(result) ).first;
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "\"name\":[1,2,3,\"test\"]", result ) << FAS_TESTING_FILE_LINE;

  s = "\"name\":[[],[]] bla-bla";
  result.clear();
  r = range_type( s.begin(), s.end() );
  r = adm(t, r, init_range(result) ).first;
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "\"name\":[[],[]]", result ) << FAS_TESTING_FILE_LINE;
}

UNIT(object_test, "parse object")
{
  using namespace fas;
  using namespace fas::testing;
  using namespace fas::json::parse;

  ad_object ado;
  std::string s = "{} bla-bla";
  typedef random_access_range<std::string::const_iterator> range_type;
  range_type r( s.begin(), s.end() );

  r = ado(t, r);
  std::string tail(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;

  s = "{\"name\":null} bla-bla";
  r = range_type( s.begin(), s.end() );

  r = ado(t, r);
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;

  s = "{\"name\":false , \"name\":{}} bla-bla";
  r = range_type( s.begin(), s.end() );

  r = ado(t, r);
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;

  s = "{\"name\": /**/ 1234, \"name\":{\"name\":[1, 2, null]}} bla-bla";
  r = range_type( s.begin(), s.end() );

  r = ado(t, r);
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;

  s = "{\"name\":[1, 2, 3, \"test\"],\"name\":{\"name\":[]}} bla-bla";
  r = range_type( s.begin(), s.end() );
  r = ado(t, r);
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;

  s = "{\"name\":[[],[]]} bla-bla";
  r = range_type( s.begin(), s.end() );
  r = ado(t, r);
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
}

UNIT(copy_object_test, "copy parse object")
{
  using namespace fas;
  using namespace fas::testing;
  using namespace fas::json::parse;

  ad_object ado;
  std::string s = "{} bla-bla";
  std::string result;
  typedef random_access_range<std::string::const_iterator> range_type;
  range_type r( s.begin(), s.end() );

  r = ado(t, r, init_range(result)).first;
  std::string tail(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "{}", result ) << FAS_TESTING_FILE_LINE;

  s = "{\"name\":null} bla-bla";
  result.clear();
  r = range_type( s.begin(), s.end() );

  r = ado(t, r, init_range(result)).first;
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "{\"name\":null}", result ) << FAS_TESTING_FILE_LINE;

  s = "{\"name\":false , \"name\":{}} bla-bla";
  result.clear();
  r = range_type( s.begin(), s.end() );

  r = ado(t, r, init_range(result)).first;
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "{\"name\":false,\"name\":{}}", result ) << FAS_TESTING_FILE_LINE;

  s = "{\"name\": /**/ 1234, \"name\":{\"name\":[1, 2, null]}} bla-bla";
  result.clear();
  r = range_type( s.begin(), s.end() );

  r = ado(t, r, init_range(result)).first;
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "{\"name\":1234,\"name\":{\"name\":[1,2,null]}}", result ) << FAS_TESTING_FILE_LINE;

  s = "{\"name\":[1, 2, 3, \"test\"],\"name\":{\"name\":[]}} bla-bla";
  result.clear();
  r = range_type( s.begin(), s.end() );
  r = ado(t, r, init_range(result)).first;
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "{\"name\":[1,2,3,\"test\"],\"name\":{\"name\":[]}}", result ) << FAS_TESTING_FILE_LINE;

  s = "{\"name\":[[],[]]} bla-bla";
  result.clear();
  r = range_type( s.begin(), s.end() );
  r = ado(t, r, init_range(result)).first;
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "{\"name\":[[],[]]}", result ) << FAS_TESTING_FILE_LINE;
}

#include <fas/serialization/json/parser/ad_null.hpp>
#include <fas/serialization/json/parser/ad_boolean.hpp>
#include <fas/serialization/json/parser/ad_number.hpp>
#include <fas/serialization/json/parser/ad_string.hpp>
#include <fas/serialization/json/parser/ad_space.hpp>


BEGIN_SUITE(object_parser_suite, "object json parser suite")
  ADD_UNIT(value_test)
  ADD_UNIT(copy_value_test)
  ADD_UNIT(array_test)
  ADD_UNIT(copy_array_test)
  ADD_UNIT(member_test)
  ADD_UNIT(copy_member_test)
  ADD_UNIT(object_test)
  ADD_UNIT(copy_object_test)
  ADD_ADVICE( ::fas::json::parse::_null_, ::fas::json::parse::ad_null)
  ADD_ADVICE( ::fas::json::parse::_boolean_, ::fas::json::parse::ad_boolean)
  ADD_ADVICE( ::fas::json::parse::_number_, ::fas::json::parse::ad_number)
  ADD_ADVICE( ::fas::json::parse::_string_, ::fas::json::parse::ad_string)

  ADD_ADVICE( ::fas::json::parse::_value_, ::fas::json::parse::ad_value)
  ADD_ADVICE( ::fas::json::parse::_array_, ::fas::json::parse::ad_array)
  ADD_ADVICE( ::fas::json::parse::_space_, ::fas::json::parse::ad_space)
  ADD_ADVICE( ::fas::json::parse::_member_, ::fas::json::parse::ad_member)
  ADD_ADVICE( ::fas::json::parse::_name_, ::fas::json::parse::ad_string)

  ADD_ADVICE( ::fas::json::parse::_object_, ::fas::json::parse::ad_object)
  
  ADD_ADVICE( ::fas::json::_except_, ::fas::json::ad_except)
END_SUITE(object_parser_suite)
