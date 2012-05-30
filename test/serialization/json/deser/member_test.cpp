#include <fas/testing.hpp>

#include "../../foo.hpp"
#include "../../bar.hpp"
#include "../../names.hpp"

#include <fas/serialization/json/deser/ad_integer.hpp>
#include <fas/serialization/json/deser/ad_attr.hpp>
#include <fas/serialization/json/deser/ad_field.hpp>
#include <fas/serialization/json/deser/aspect_string.hpp>
#include <fas/serialization/json/deser/ad_separator.hpp>

#include <fas/serialization/json/meta/integer.hpp>
#include <fas/serialization/json/meta/string.hpp>
#include <fas/serialization/json/meta/tstring.hpp>
#include <fas/serialization/json/meta/attr.hpp>
#include <fas/serialization/json/meta/field.hpp>

#include <fas/serialization/json/parser/aspect.hpp>

#include <fas/range/range.hpp>
#include <fas/typemanip/tstring.hpp>
#include <string>



using namespace ::fas::json;

UNIT(ad_field_test1, "test fas::json::deser::ad_field advice")
{
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  foo f(0);
  ad_field adm;

  typedef field< n_foo1, attr<foo, int, &foo::foo1, integer> > foo_foo1;
  adm( t, foo_foo1(), f, fas::range("\"foo1\":-1") );
  t << equal<expect>(f.foo1, -1 ) << FAS_TESTING_FILE_LINE;
  f = foo(0);


  typedef field< n_foo2, attr<foo, std::string, &foo::foo2, string> > foo_foo2;
  adm( t, foo_foo2(), f, fas::range("\"foo2\":\"test-foo2\"") );
  t << equal<expect>(f.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
  f = foo(0);

  typedef field< n_foo3, attr<foo, foo::foo3type, &foo::foo3, string> > foo_foo3;
  adm( t, foo_foo3(), f, fas::range("\"foo3\":\"test-foo3\"") );
  t << equal<expect>( std::string(f.foo3), "test-foo3" ) << FAS_TESTING_FILE_LINE;
  f = foo(0);

  bar b=bar(0);

  typedef field< n_bar1, attr<bar::baz, int, &bar::baz::baz1, integer> > bar_baz_baz1;
  adm( t, bar_baz_baz1(), b.bar1, fas::range("\"bar1\":42") );
  t << equal<expect>( b.bar1.baz1, 42 ) << FAS_TESTING_FILE_LINE;
  b=bar(0);

  typedef field< n_bar1, attr<bar, bar::baz, &bar::bar1, attr<bar::baz, int, &bar::baz::baz1, integer> > > bar_bar1_baz1;
  adm( t, bar_bar1_baz1(), b, fas::range("\"bar1\":42") );
  t << equal<expect>(b.bar1.baz1, 42 ) << FAS_TESTING_FILE_LINE;
  b=bar(0);

  typedef field< n_bar2, attr<bar, foo, &bar::bar2, attr<foo, std::string, &foo::foo2, string> > > bar_bar2_foo2;
  adm( t, bar_bar2_foo2(), b, fas::range("\"bar2\":\"test-foo2\"") );
  t << equal<expect>(b.bar2.foo2, std::string("test-foo2") ) << FAS_TESTING_FILE_LINE;
  b=bar(0);

}

UNIT(ad_field_test2, "test fas::json::deser::ad_field advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;
}

UNIT(ad_field_test4, "test fas::json::deser::ad_field advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;
}

UNIT(ad_field_test5, "test fas::json::deser::ad_field advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;
}

BEGIN_SUITE(member_deserialize_suite, "field deserializer suite")
  ADD_UNIT(ad_field_test1)
  ADD_ADVICE( ::fas::json::deser::_string_, ::fas::json::deser::ad_string)
  ADD_ADVICE( ::fas::json::deser::_cstring_, ::fas::json::deser::ad_cstring)
  ADD_ADVICE( ::fas::json::deser::_integer_, ::fas::json::deser::ad_integer)
  ADD_ADVICE( ::fas::json::deser::_attr_, ::fas::json::deser::ad_attr)
  ADD_ADVICE( ::fas::json::deser::_field_, ::fas::json::deser::ad_field)
  ADD_ASPECT(::fas::json::parse::aspect)
	ADD_ASPECT( ::fas::json::deser::string_aspect )
END_SUITE(member_deserialize_suite)
