#include <fas/testing.hpp>

#include "../../foo.hpp"
#include "../../bar.hpp"

#include <fas/serialization/json/ser/ad_primary_list.hpp>
/*#include <fas/serialization/json/ser/ad_brute_list.hpp>
#include <fas/serialization/json/ser/ad_brute_pair.hpp>*/

#include <fas/serialization/json/ser/ad_attr.hpp>
#include <fas/serialization/json/ser/ad_integer.hpp>
#include <fas/serialization/json/ser/ad_string.hpp>
#include <fas/serialization/json/ser/ad_sequence.hpp>
#include <fas/serialization/json/ser/ad_null.hpp>

#include <fas/serialization/json/except/ad_except.hpp>

#include <fas/serialization/json/meta/primary_list.hpp>
#include <fas/serialization/json/meta/attr.hpp>
#include <fas/serialization/json/meta/integer.hpp>
#include <fas/serialization/json/meta/string.hpp>
#include <fas/serialization/json/meta/sequence.hpp>



#include <fas/range/range.hpp>
#include <fas/range/init_range.hpp>

#include <fas/type_list/empty_list.hpp>

UNIT(ad_field_list_test1, "test fas::json::ser::ad_field_list advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;

  foo f;
  ad_primary_list adfl;
  std::string result;
  
  typedef primary_list< empty_list > foo_list1;
  adfl(t, foo_list1(), f, init_range(result) );
  t << equal<expect>(result, "" ) << FAS_TESTING_FILE_LINE;
  result.clear();
  
  typedef primary_list< attr<foo, int, &foo::foo1, integer> > foo_list2;
  adfl(t, foo_list2(), f, init_range(result) );
  t << equal<expect>(result, "-1" ) << FAS_TESTING_FILE_LINE;
  result.clear();
  
  typedef primary_list< 
    type_list_n<
      attr<foo, int, &foo::foo1, integer>,
      attr<foo, std::string, &foo::foo2, string>
    >::type
  > foo_list3;
  adfl(t, foo_list3(), f, init_range(result) );
  t << equal<expect>(result, "-1,\"test-foo2\"" ) << FAS_TESTING_FILE_LINE;
  result.clear();
  
  // typedef char char20[20];
  typedef primary_list< 
    type_list_n<
      attr<foo, int, &foo::foo1, integer>,
      attr<foo, std::string, &foo::foo2, string>,
      attr<foo, foo::foo3type, &foo::foo3, string>
    >::type
  > foo_list4;
  adfl(t, foo_list4(), f, init_range(result) );
  t << equal<expect>(result, "-1,\"test-foo2\",\"test-foo3\"" ) << FAS_TESTING_FILE_LINE;
  result.clear();
}


UNIT(ad_field_list_test2, "test fas::json::ser::ad_field_list advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;

  bar b;
  ad_primary_list adfl;
  std::string result;

  typedef primary_list< 
    type_list_n<
      attr<foo, int, &foo::foo1, integer>,
      attr<foo, std::string, &foo::foo2, string>,
      attr<foo, foo::foo3type, &foo::foo3, string>,
      attr<bar, bar::baz, &bar::bar1, attr<bar::baz, int, &bar::baz::baz1, integer> >,
      attr<bar, foo, &bar::bar2, attr<foo, std::string, &foo::foo2, string> >
    >::type
  > bar_list1;
  adfl(t, bar_list1(), b, init_range(result) );
  t << equal<expect>(result, "-1,\"test-foo2\",\"test-foo3\",42,\"test-foo2\"" ) << FAS_TESTING_FILE_LINE;
  result.clear();
}

UNIT(ad_field_list_test3, "test fas::json::ser::ad_field_list advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;

  bar b;
  ad_primary_list adfl;
  std::string result;

  typedef primary_list< 
    type_list_n<
      attr<foo, int, &foo::foo1, integer>,
      attr<foo, std::string, &foo::foo2, string>,
      attr<foo, foo::foo3type, &foo::foo3, string>,
      attr<bar, bar::baz, &bar::bar1, attr<bar::baz, int, &bar::baz::baz1, integer> >,
      attr<bar, foo, &bar::bar2, attr<foo, std::string, &foo::foo2, string> >,
      attr<foo, foo::foo5type, &foo::foo5, sequence<integer/*, 5*/> >,
      attr<foo, std::vector<std::string>, &foo::foo6, sequence<string> >
    >::type
  > bar_list1;
  std::cout << std::endl;
  for (int i = 0 ; i < 5; ++i)
    std::cout <<  (int)(b.foo5[i]) << std::endl;

  adfl(t, bar_list1(), b, init_range(result) );
  t << equal<expect>(result, "-1,\"test-foo2\",\"test-foo3\",42,\"test-foo2\",0,1,2,3,4,\"test-foo6-1\",\"test-foo6-2\"" ) << FAS_TESTING_FILE_LINE;
  std::cout << std::endl << result << std::endl << "-1,\"test-foo2\",\"test-foo3\",42,\"test-foo2\",0,1,2,3,4,\"test-foo6-1\",\"test-foo6-2\"" << std::endl;
  for (int i = 0 ; i < 5; ++i)
      std::cout <<  (int)(b.foo5[i]) << std::endl;
  result.clear();
}


BEGIN_SUITE(field_list_serialize_suite, "field_list serializer suite")
  ADD_UNIT(ad_field_list_test1)
  ADD_UNIT(ad_field_list_test2)
  ADD_UNIT(ad_field_list_test3)
  ADD_ADVICE( ::fas::json::ser::_integer_, ::fas::json::ser::ad_integer)
  ADD_ADVICE( ::fas::json::ser::_string_, ::fas::json::ser::ad_string)
  ADD_ADVICE( ::fas::json::ser::_null_, ::fas::json::ser::ad_null)
  ADD_ADVICE( ::fas::json::ser::_attr_, ::fas::json::ser::ad_attr)
  ADD_ADVICE( ::fas::json::ser::_sequence_, ::fas::json::ser::ad_sequence)
  ADD_ADVICE( ::fas::json::_except_, ::fas::json::ad_except)
END_SUITE(field_list_serialize_suite)
