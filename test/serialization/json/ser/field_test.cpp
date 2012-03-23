#include <fas/testing.hpp>

#include "../../foo.hpp"
#include "../../bar.hpp"



#include <fas/serialization/json/ser/ad_integer.hpp>
#include <fas/serialization/json/ser/ad_attr.hpp>
#include <fas/serialization/json/ser/ad_string.hpp>
#include <fas/serialization/json/ser/ad_null.hpp>

#include <fas/serialization/json/meta/integer.hpp>
#include <fas/serialization/json/meta/string.hpp>
#include <fas/serialization/json/meta/attr.hpp>

#include <fas/serialization/json/except/ad_except.hpp>

#include <fas/range/range.hpp>
#include <fas/typemanip/tstring.hpp>

#include <string>


using namespace ::fas;
using namespace ::fas::json;

UNIT(attr_test, "test fas::json::attr meta")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;

  foo f;
  
  typedef attr<foo, int, &foo::foo1, integer> foo_foo1;
  t << equal<expect>(foo_foo1().ref(f), -1 ) << FAS_TESTING_FILE_LINE;
  
  typedef attr<foo, std::string, &foo::foo2, string> foo_foo2;
  t << equal<expect>(foo_foo2().ref(f), "test-foo2" ) <<  FAS_TESTING_FILE_LINE;

  /*!!
  typedef attr<foo, char[20], &foo::foo3, string> foo_foo3;
  t << equal<expect>(foo_foo3().ref(f), std::string("test-foo3") ) << "[" << foo_foo3().ref(f) << "]" << FAS_TESTING_FILE_LINE;
  */
  
  bar b;
  
  typedef attr<bar::baz, int, &bar::baz::baz1, integer> bar_baz_baz1;
  t << equal<expect>(bar_baz_baz1().ref(b.bar1), 42 ) << FAS_TESTING_FILE_LINE;
  
  typedef attr<bar, bar::baz, &bar::bar1, bar_baz_baz1> bar_bar1_baz1;
  t << equal<expect>(bar_bar1_baz1().ref(b).baz1, 42 ) << FAS_TESTING_FILE_LINE;
  
  typedef attr<bar, foo, &bar::bar2, foo_foo2> bar_bar1_foo2;
  t << equal<expect>( bar_bar1_foo2().ref(b).foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
}

UNIT(ad_field_test1, "test fas::json::ser::ad_field advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;

  foo f;
  ad_attr adf;
  std::string result;
  
  typedef attr<foo, int, &foo::foo1, integer> foo_foo1;
  adf( t, foo_foo1(), f, init_range(result) );
  t << equal<expect>(result, "-1" ) << FAS_TESTING_FILE_LINE;
  result.clear();

  typedef attr<foo, std::string, &foo::foo2, string> foo_foo2;
  adf( t, foo_foo2(), f, init_range(result) );
  t << equal<expect>(result, "\"test-foo2\"" ) << FAS_TESTING_FILE_LINE;
  result.clear();


  typedef attr<foo, foo::foo3type, &foo::foo3, string> foo_foo3;
  adf( t, foo_foo3(), f, init_range(result) );
  
  t << equal<expect>(result, "\"test-foo3\"" ) << FAS_TESTING_FILE_LINE;
  result.clear();
  
  bar b;
  
  typedef attr<bar::baz, int, &bar::baz::baz1, integer> bar_baz_baz1;
  adf( t, bar_baz_baz1(), b.bar1, init_range(result) );
  t << equal<expect>( result, "42" ) << FAS_TESTING_FILE_LINE;
  result.clear();
  
  typedef attr<bar, bar::baz, &bar::bar1, bar_baz_baz1> bar_bar1_baz1;
  adf( t, bar_bar1_baz1(), b, init_range(result) );
  t << equal<expect>(result, "42" ) << FAS_TESTING_FILE_LINE;
  result.clear();
  
  typedef attr<bar, foo, &bar::bar2, foo_foo2> bar_bar1_foo2;
  adf( t, bar_bar1_foo2(), b, init_range(result) );
  t << equal<expect>(result, "\"test-foo2\"" ) << FAS_TESTING_FILE_LINE;
  result.clear();
}


UNIT(ad_field_test2, "test fas::json::ser::ad_field advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;
}



UNIT(ad_field_test4, "test fas::json::ser::ad_field advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;
}

UNIT(ad_field_test5, "test fas::json::ser::ad_field advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;
  
}

BEGIN_SUITE(field_serialize_suite, "field serializer suite")
  ADD_UNIT(attr_test)
  ADD_UNIT(ad_field_test1)
  ADD_UNIT(ad_field_test2)
  
  ADD_ADVICE( ::fas::json::ser::_string_, ::fas::json::ser::ad_string)
  ADD_ADVICE( ::fas::json::ser::_integer_, ::fas::json::ser::ad_integer)
  ADD_ADVICE( ::fas::json::ser::_attr_, ::fas::json::ser::ad_attr)
  ADD_ADVICE( ::fas::json::ser::_null_, ::fas::json::ser::ad_null)
  ADD_ADVICE( ::fas::json::_except_, ::fas::json::ad_except)
END_SUITE(field_serialize_suite)
