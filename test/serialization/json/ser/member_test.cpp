#include <fas/testing.hpp>

#include "../../foo.hpp"
#include "../../bar.hpp"
#include "../../names.hpp"

#include <fas/serialization/json/ser/ad_integer.hpp>
#include <fas/serialization/json/ser/ad_attr.hpp>
#include <fas/serialization/json/ser/ad_member.hpp>
#include <fas/serialization/json/ser/ad_string.hpp>
#include <fas/serialization/json/ser/ad_null.hpp>
#include <fas/serialization/json/except/ad_except.hpp>
//#include <fas/serialization/json/ser/ad_cstring.hpp>

#include <fas/serialization/json/meta/integer.hpp>
#include <fas/serialization/json/meta/string.hpp>
#include <fas/serialization/json/meta/tstring.hpp>
#include <fas/serialization/json/meta/attr.hpp>
#include <fas/serialization/json/meta/member.hpp>

#include <fas/range/range.hpp>
#include <fas/typemanip/tstring.hpp>

#include <string>


using namespace ::fas;
using namespace ::fas::json;

UNIT(ad_member_test1, "test fas::json::ser::ad_member advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;

  foo f;
  ad_member adm;
  std::string result;
  
  typedef member< n_foo1, attr<foo, int, &foo::foo1, integer> > foo_foo1;
  adm( t, foo_foo1(), f, init_range(result) );
  t << equal<expect>(result, "\"foo1\":-1" ) << FAS_TESTING_FILE_LINE;
  result.clear();

  typedef member< n_foo2, attr<foo, std::string, &foo::foo2, string> > foo_foo2;
  adm( t, foo_foo2(), f, init_range(result) );
  t << equal<expect>(result, "\"foo2\":\"test-foo2\"" ) << FAS_TESTING_FILE_LINE;
  result.clear();

  typedef member< n_foo3, attr<foo, foo::foo3type, &foo::foo3, string> > foo_foo3;
  adm( t, foo_foo3(), f, init_range(result) );
  t << equal<expect>(result, "\"foo3\":\"test-foo3\"" ) << FAS_TESTING_FILE_LINE;
  result.clear();
  
  bar b;
  
  typedef member< n_bar1, attr<bar::baz, int, &bar::baz::baz1, integer> > bar_baz_baz1;
  adm( t, bar_baz_baz1(), b.bar1, init_range(result) );
  t << equal<expect>( result, "\"bar1\":42" ) << FAS_TESTING_FILE_LINE;
  result.clear();
  
  typedef member< n_bar1, attr<bar, bar::baz, &bar::bar1, attr<bar::baz, int, &bar::baz::baz1, integer> > > bar_bar1_baz1;
  adm( t, bar_bar1_baz1(), b, init_range(result) );
  t << equal<expect>(result, "\"bar1\":42" ) << FAS_TESTING_FILE_LINE;
  result.clear();
  
  typedef member< n_bar2, attr<bar, foo, &bar::bar2, attr<foo, std::string, &foo::foo2, string> > > bar_bar1_foo2;
  adm( t, bar_bar1_foo2(), b, init_range(result) );
  t << equal<expect>(result, "\"bar2\":\"test-foo2\"" ) << FAS_TESTING_FILE_LINE;
  result.clear();
}

UNIT(ad_member_test2, "test fas::json::ser::ad_member advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;
}

UNIT(ad_member_test4, "test fas::json::ser::ad_member advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;
}

UNIT(ad_member_test5, "test fas::json::ser::ad_member advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;
  
}

BEGIN_SUITE(member_serialize_suite, "member serializer suite")
  ADD_UNIT(ad_member_test1)
  ADD_UNIT(ad_member_test2)
  
  ADD_ADVICE( ::fas::json::ser::_string_, ::fas::json::ser::ad_string)
  ADD_ADVICE( ::fas::json::ser::_cstring_, ::fas::json::ser::ad_cstring)
  ADD_ADVICE( ::fas::json::ser::_integer_, ::fas::json::ser::ad_integer)
  ADD_ADVICE( ::fas::json::ser::_attr_, ::fas::json::ser::ad_attr)
  ADD_ADVICE( ::fas::json::ser::_member_, ::fas::json::ser::ad_member)
  ADD_ADVICE( ::fas::json::ser::_null_, ::fas::json::ser::ad_null)
  ADD_ADVICE( ::fas::json::_except_, ::fas::json::ad_except)
END_SUITE(member_serialize_suite)
