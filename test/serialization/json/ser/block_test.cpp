#include <fas/testing.hpp>

#include "../../foo.hpp"
#include "../../bar.hpp"



#include <fas/serialization/json/ser/ad_integer.hpp>
#include <fas/serialization/json/ser/ad_field.hpp>
#include <fas/serialization/json/ser/ad_string.hpp>
#include <fas/serialization/json/ser/ad_block.hpp>

#include <fas/serialization/json/meta/integer.hpp>
#include <fas/serialization/json/meta/string.hpp>
#include <fas/serialization/json/meta/attr.hpp>
#include <fas/serialization/json/meta/block.hpp>

#include <fas/range/.hpp>
#include <fas/typemanip/tstring.hpp>

#include <string>


using namespace ::fas;
using namespace ::fas::json;

UNIT(block_test, "test fas::json::attr meta")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;

  typedef object<
  > foo_json;
  /*
  foo f;
  
  typedef attr<foo, int, &foo::foo1, integer> foo_foo1;
  t << equal<expect>(foo_foo1().get_value(f), -1 ) << FAS_TESTING_FILE_LINE;
  
  typedef attr<foo, std::string, &foo::foo2, string> foo_foo2;
  t << equal<expect>(foo_foo2().get_value(f), "test-foo2" ) <<  FAS_TESTING_FILE_LINE;
  
  typedef attr<foo, char[20], &foo::foo3, string> foo_foo3;
  t << equal<expect>(foo_foo3().get_value(f), std::string("test-foo3") ) << "[" << foo_foo3().get_value(f) << "]" << FAS_TESTING_FILE_LINE;
  
  bar b;
  
  typedef attr<bar::baz, int, &bar::baz::baz1, integer> bar_baz_baz1;
  t << equal<expect>(bar_baz_baz1().get_value(b.bar1), 42 ) << FAS_TESTING_FILE_LINE;
  
  typedef attr<bar, bar::baz, &bar::bar1, bar_baz_baz1> bar_bar1_baz1;
  t << equal<expect>(bar_bar1_baz1().get_value(b).baz1, 42 ) << FAS_TESTING_FILE_LINE;
  
  typedef attr<bar, foo, &bar::bar2, foo_foo2> bar_bar1_foo2;
  t << equal<expect>( bar_bar1_foo2().get_value(b).foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
  */
}


BEGIN_SUITE(field_serialize_suite, "field serializer suite")
  ADD_UNIT(block_test)
  
  ADD_ADVICE( ::fas::json::ser::_string_, ::fas::json::ser::ad_string)
  ADD_ADVICE( ::fas::json::ser::_integer_, ::fas::json::ser::ad_integer)
  ADD_ADVICE( ::fas::json::ser::_field_, ::fas::json::ser::ad_field)
  ADD_ADVICE( ::fas::json::ser::_block_, ::fas::json::ser::ad_field)
END_SUITE(field_serialize_suite)
