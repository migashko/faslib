#include <fas/testing.hpp>

#include "../../foo.hpp"
#include "../../bar.hpp"



#include <fas/serialization/json/deser/ad_integer.hpp>
#include <fas/serialization/json/deser/ad_attr.hpp>
#include <fas/serialization/json/deser/aspect_string.hpp>
#include <fas/serialization/json/deser/ad_sequence.hpp>
#include <fas/serialization/json/deser/ad_separator.hpp>

#include <fas/serialization/json/meta/integer.hpp>
#include <fas/serialization/json/meta/string.hpp>
#include <fas/serialization/json/meta/attr.hpp>
#include <fas/serialization/json/meta/sequence.hpp>

#include <fas/range/range.hpp>
#include <fas/typemanip/tstring.hpp>

#include <string>

#include <fas/serialization/json/parser/aspect.hpp>

using namespace ::fas;
using namespace ::fas::json;

UNIT(attr_test, "test fas::json::attr meta")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  foo f(0);
  
  typedef attr<foo, int, &foo::foo1, integer> foo_foo1;
  foo_foo1()(f) = -1;
  t << equal<expect>(foo_foo1()(f), -1 ) << FAS_TESTING_FILE_LINE;
  
  typedef attr<foo, std::string, &foo::foo2, string> foo_foo2;
  foo_foo2()(f) = "test-foo2";
  t << equal<expect>(foo_foo2()(f), "test-foo2" ) <<  FAS_TESTING_FILE_LINE;
  
  typedef attr<foo, foo::foo3type, &foo::foo3, string> foo_foo3;
  std::strcpy( foo_foo3()(f), "test-foo3" );
  t << equal<expect>(foo_foo3()(f), std::string("test-foo3") ) << "[" << foo_foo3()(f) << "]" << FAS_TESTING_FILE_LINE;
  
  bar b(0);
  
  typedef attr<bar::baz, int, &bar::baz::baz1, integer> bar_baz_baz1;
  bar_baz_baz1()(b.bar1) = 42;
  t << equal<expect>(bar_baz_baz1()(b.bar1), 42 ) << FAS_TESTING_FILE_LINE;
  
  typedef attr<bar, bar::baz, &bar::bar1, bar_baz_baz1> bar_bar1_baz1;
  bar_bar1_baz1()(b).baz1 = 42;
  t << equal<expect>(bar_bar1_baz1()(b).baz1, 42 ) << FAS_TESTING_FILE_LINE;
  
  typedef attr<bar, foo, &bar::bar2, foo_foo2> bar_bar1_foo2;
  bar_bar1_foo2()(b).foo2 = "test-foo2";
  t << equal<expect>( bar_bar1_foo2()(b).foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
}

UNIT(ad_field_test1, "test fas::json::deser::ad_field advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  foo f(0);
  ad_attr adf;
  
  typedef attr<foo, int, &foo::foo1, integer> foo_foo1;
  adf( t, foo_foo1(), f, range("-1") );
  t << equal<expect>(f.foo1, -1 ) << FAS_TESTING_FILE_LINE;
  
  typedef attr<foo, std::string, &foo::foo2, string> foo_foo2;
  adf( t, foo_foo2(), f, range("\"test-foo2\"") );
  t << equal<expect>(f.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
  
  typedef attr<foo, foo::foo3type, &foo::foo3, string> foo_foo3;
  adf( t, foo_foo3(), f, range("\"test-foo3\"") );
  t << equal<expect>(f.foo3, std::string("test-foo3") ) << FAS_TESTING_FILE_LINE;
  
  
  bar b(0);
  
  typedef attr<bar::baz, int, &bar::baz::baz1, integer> bar_baz_baz1;
  adf( t, bar_baz_baz1(), b.bar1, range("42") );
  t << equal<expect>( b.bar1.baz1, 42 ) << FAS_TESTING_FILE_LINE;
  
  
  typedef attr<bar, bar::baz, &bar::bar1, bar_baz_baz1> bar_bar1_baz1;
  adf( t, bar_bar1_baz1(), b, range("42") );
  t << equal<expect>( b.bar1.baz1, 42 ) << FAS_TESTING_FILE_LINE;
  
  
  typedef attr<bar, foo, &bar::bar2, foo_foo2> bar_bar1_foo2;
  adf( t, bar_bar1_foo2(), b, range("\"test-foo2\"") );
  t << equal<expect>(b.bar2.foo2, "test-foo2" ) << b.bar2.foo2 << "|" <<FAS_TESTING_FILE_LINE;
  
}


UNIT(ad_field_test2, "test fas::json::deser::ad_field advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;
  
  foo f(0);
  ad_attr adf;

  typedef attr<foo, foo::foo5type, &foo::foo5, sequence<integer> > bar_foo5;
  
  adf(t, bar_foo5(), f, range("0,1,2,3,4") );
  t << equal<expect>(f.foo5[0], 0 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo5[1], 1 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo5[2], 2 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo5[3], 3 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo5[4], 4 ) << FAS_TESTING_FILE_LINE;

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

BEGIN_SUITE(field_deserialize_suite, "field deserializer suite")
  ADD_UNIT(attr_test)
  ADD_UNIT(ad_field_test1)
  ADD_UNIT(ad_field_test2)
  
  ADD_ADVICE( ::fas::json::deser::_string_, ::fas::json::deser::ad_string)
  ADD_ADVICE( ::fas::json::deser::_integer_, ::fas::json::deser::ad_integer)
  ADD_ADVICE( ::fas::json::deser::_attr_, ::fas::json::deser::ad_attr)
  ADD_ADVICE( ::fas::json::deser::_sequence_, ::fas::json::deser::ad_sequence)
  ADD_ASPECT(::fas::json::parse::aspect)
	ADD_ASPECT( ::fas::json::deser::string_aspect )
END_SUITE(field_deserialize_suite)
