#include <fas/testing.hpp>

#include "../../foo.hpp"
#include "../../bar.hpp"
#include "../../names.hpp"


#include <fas/serialization/json/ser/ad_attr.hpp>

#include <fas/serialization/json/ser/ad_field.hpp>
#include <fas/serialization/json/ser/ad_integer.hpp>
#include <fas/serialization/json/ser/ad_string.hpp>
#include <fas/serialization/json/ser/ad_sequence.hpp>
#include <fas/serialization/json/ser/ad_array.hpp>
#include <fas/serialization/json/ser/ad_stub.hpp>
#include <fas/serialization/json/ser/ad_primary_list.hpp>

#include <fas/serialization/json/meta/primary_list.hpp>
#include <fas/serialization/json/meta/attr.hpp>
#include <fas/serialization/json/meta/field.hpp>
#include <fas/serialization/json/meta/integer.hpp>
#include <fas/serialization/json/meta/string.hpp>
#include <fas/serialization/json/meta/sequence.hpp>
#include <fas/serialization/json/meta/array.hpp>
#include <fas/serialization/json/meta/stub.hpp>

#include <fas/range/range.hpp>

#include <fas/type_list/empty_list.hpp>

/*
UNIT(ad_field_list_test1, "test fas::json::ser::ad_field_list advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;

  foo f;
  ad_field_list adfl;
  std::string result;
  
  typedef field_list< empty_list > foo_list1;
  adfl(t, foo_list1(), f, (result) );
  t << equal<expect>(result, "" ) << FAS_TESTING_FILE_LINE;
  result.clear();
  
  typedef field_list< field< n_foo1, attr<foo, int, &foo::foo1, integer> > > foo_list2;
  adfl(t, foo_list2(), f, (result) );
  t << equal<expect>(result, "\"foo1\":-1" ) << FAS_TESTING_FILE_LINE;
  result.clear();
  
  typedef field_list< 
    type_list_n<
      field< n_foo1, attr<foo, int, &foo::foo1, integer> >,
      field< n_foo2, attr<foo, std::string, &foo::foo2, string> >
    >::type
  > foo_list3;
  adfl(t, foo_list3(), f, (result) );
  t << equal<expect>(result, "\"foo1\":-1,\"foo2\":\"test-foo2\"" ) << FAS_TESTING_FILE_LINE;
  result.clear();
  
  typedef field_list< 
    type_list_n<
      field< n_foo1, attr<foo, int, &foo::foo1, integer> >,
      field< n_foo2, attr<foo, std::string, &foo::foo2, string> >,
      field< n_foo3, attr<foo, char[20], &foo::foo3, string> >
    >::type
  > foo_list4;
  adfl(t, foo_list4(), f, (result) );
  t << equal<expect>(result, "\"foo1\":-1,\"foo2\":\"test-foo2\",\"foo3\":\"test-foo3\"" ) << FAS_TESTING_FILE_LINE;
  result.clear();
}


UNIT(ad_field_list_test2, "test fas::json::ser::ad_field_list advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;

  bar b;
  ad_field_list adfl;
  std::string result;

  typedef field_list< 
    type_list_n<
      field< n_foo1, attr<foo, int, &foo::foo1, integer> >,
      field< n_foo2, attr<foo, std::string, &foo::foo2, string> >,
      field< n_foo3, attr<foo, char[20], &foo::foo3, string> >,
      field< n_bar1, attr<bar, bar::baz, &bar::bar1, attr<bar::baz, int, &bar::baz::baz1, integer> > >,
      field< n_bar2, attr<bar, foo, &bar::bar2, attr<foo, std::string, &foo::foo2, string> > >
    >::type
  > bar_list1;
  adfl(t, bar_list1(), b, (result) );
  t << equal<expect>(result, "\"foo1\":-1,\"foo2\":\"test-foo2\",\"foo3\":\"test-foo3\",\"bar1\":42,\"bar2\":\"test-foo2\"" ) << FAS_TESTING_FILE_LINE;
  result.clear();
}

UNIT(ad_field_list_test3, "test fas::json::ser::ad_field_list advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;

  bar b;
  ad_field_list adfl;
  std::string result;

  typedef field_list< 
    type_list_n<
      field< n_foo1, attr<foo, int, &foo::foo1, integer> >,
      field< n_foo2, attr<foo, std::string, &foo::foo2, string> >,
      field< n_foo3, attr<foo, char[20], &foo::foo3, string> >,
      field< n_bar1, attr<bar, bar::baz, &bar::bar1, attr<bar::baz, int, &bar::baz::baz1, integer> > >,
      field< n_bar2, attr<bar, foo, &bar::bar2, attr<foo, std::string, &foo::foo2, string> > >,
      field< n_foo5, attr<foo, int[5], &foo::foo5, array<integer> > >,
      field< n_foo6, attr<foo, std::vector<std::string>, &foo::foo6, array<string> > >
    >::type
  > bar_list1;
  adfl(t, bar_list1(), b, (result) );
  //t << message(result);
  t << equal<expect>(result, "\"foo1\":-1,\"foo2\":\"test-foo2\",\"foo3\":\"test-foo3\",\"bar1\":42,\"bar2\":\"test-foo2\",\"foo5\":[0,1,2,3,4],\"foo6\":[\"test-foo6-1\",\"test-foo6-2\"]" ) << FAS_TESTING_FILE_LINE;
  result.clear();
}
*/


BEGIN_SUITE(field_list_serialize_suite_temp, "field_list serializer suite")
/*
  ADD_UNIT(ad_field_list_test1)
  ADD_UNIT(ad_field_list_test2)
  ADD_UNIT(ad_field_list_test3)
  */
  ADD_ADVICE( ::fas::json::ser::_integer_, ::fas::json::ser::ad_integer)
  ADD_ADVICE( ::fas::json::ser::_string_, ::fas::json::ser::ad_string)
  ADD_ADVICE( ::fas::json::ser::_cstring_, ::fas::json::ser::ad_cstring)
  ADD_ADVICE( ::fas::json::ser::_attr_, ::fas::json::ser::ad_attr)
  ADD_ADVICE( ::fas::json::ser::_primary_list_, ::fas::json::ser::ad_primary_list)
  ADD_ADVICE( ::fas::json::ser::_field_, ::fas::json::ser::ad_field)
  //ADD_ADVICE( ::fas::json::ser::_field_list_, ::fas::json::ser::ad_field_list)
  ADD_ADVICE( ::fas::json::ser::_sequence_, ::fas::json::ser::ad_sequence)
  ADD_ADVICE( ::fas::json::ser::_array_, ::fas::json::ser::ad_array)
  ADD_ADVICE( ::fas::json::ser::_stub_, ::fas::json::ser::ad_stub)
END_SUITE(field_list_serialize_suite_temp)
