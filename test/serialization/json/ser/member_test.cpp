#include <fas/testing.hpp>

#include "../../foo.hpp"
#include "../../bar.hpp"
#include "../../names.hpp"

#include <fas/serialization/json/ser/ad_integer.hpp>
#include <fas/serialization/json/ser/ad_attr.hpp>
#include <fas/serialization/json/ser/ad_field.hpp>
#include <fas/serialization/json/ser/ad_string.hpp>
#include <fas/serialization/json/ser/ad_null.hpp>
#include <fas/serialization/json/except/ad_except.hpp>
//#include <fas/serialization/json/ser/ad_cstring.hpp>

#include <fas/serialization/json/meta/integer.hpp>
#include <fas/serialization/json/meta/string.hpp>
#include <fas/serialization/json/meta/tstring.hpp>
#include <fas/serialization/json/meta/attr.hpp>
#include <fas/serialization/json/meta/field.hpp>

#include <fas/range/range.hpp>
#include <fas/range/orange.hpp>

#include <fas/typemanip/tstring.hpp>

#include <string>


using namespace ::fas::json;

UNIT(ad_field_test1, "test fas::json::ser::ad_field advice")
{
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;

  foo f;
  ad_field adm;
  std::string result;
  
  typedef field< n_foo1, attr<foo, int, &foo::foo1, integer> > foo_foo1;
  adm( t, foo_foo1(), f, fas::orange(result) );
  t << equal<expect>(result, "\"foo1\":-1" ) << FAS_TESTING_FILE_LINE;
  result.clear();

  typedef field< n_foo2, attr<foo, std::string, &foo::foo2, string> > foo_foo2;
  adm( t, foo_foo2(), f, fas::orange(result) );
  t << equal<expect>(result, "\"foo2\":\"test-foo2\"" ) << FAS_TESTING_FILE_LINE;
  result.clear();

  typedef field< n_foo3, attr<foo, foo::foo3type, &foo::foo3, string> > foo_foo3;
  adm( t, foo_foo3(), f, fas::orange(result) );
  t << equal<expect>(result, "\"foo3\":\"test-foo3\"" ) << FAS_TESTING_FILE_LINE;
  result.clear();
  
  bar b;
  
  typedef field< n_bar1, attr<bar::baz, int, &bar::baz::baz1, integer> > bar_baz_baz1;
  adm( t, bar_baz_baz1(), b.bar1, fas::orange(result) );
  t << equal<expect>( result, "\"bar1\":42" ) << FAS_TESTING_FILE_LINE;
  result.clear();
  
  typedef field< n_bar1, attr<bar, bar::baz, &bar::bar1, attr<bar::baz, int, &bar::baz::baz1, integer> > > bar_bar1_baz1;
  adm( t, bar_bar1_baz1(), b, fas::orange(result) );
  t << equal<expect>(result, "\"bar1\":42" ) << FAS_TESTING_FILE_LINE;
  result.clear();
  
  typedef field< n_bar2, attr<bar, foo, &bar::bar2, attr<foo, std::string, &foo::foo2, string> > > bar_bar1_foo2;
  adm( t, bar_bar1_foo2(), b, fas::orange(result) );
  t << equal<expect>(result, "\"bar2\":\"test-foo2\"" ) << FAS_TESTING_FILE_LINE;
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
  ADD_UNIT(ad_field_test1)
  ADD_UNIT(ad_field_test2)
  
  ADD_ADVICE( ::fas::json::ser::_string_, ::fas::json::ser::ad_string)
  ADD_ADVICE( ::fas::json::ser::_cstring_, ::fas::json::ser::ad_cstring)
  ADD_ADVICE( ::fas::json::ser::_integer_, ::fas::json::ser::ad_integer)
  ADD_ADVICE( ::fas::json::ser::_attr_, ::fas::json::ser::ad_attr)
  ADD_ADVICE( ::fas::json::ser::_field_, ::fas::json::ser::ad_field)
  ADD_ADVICE( ::fas::json::ser::_null_, ::fas::json::ser::ad_null)
  ADD_ADVICE( ::fas::json::_except_, ::fas::json::ad_except)
END_SUITE(field_serialize_suite)
