#include <fas/testing.hpp>

#include "../../foo.hpp"
#include "../../bar.hpp"

#include <fas/serialization/json/deser/ad_primary_list.hpp>
#include <fas/serialization/json/deser/ad_separator.hpp>
#include <fas/serialization/json/deser/ad_brute_list.hpp>
#include <fas/serialization/json/deser/ad_brute_pair.hpp>

#include <fas/serialization/json/deser/ad_attr.hpp>
#include <fas/serialization/json/deser/ad_integer.hpp>
#include <fas/serialization/json/deser/ad_string.hpp>
#include <fas/serialization/json/deser/ad_sequence.hpp>

#include <fas/serialization/json/meta/primary_list.hpp>
#include <fas/serialization/json/meta/attr.hpp>
#include <fas/serialization/json/meta/integer.hpp>
#include <fas/serialization/json/meta/string.hpp>
#include <fas/serialization/json/meta/member.hpp>
#include <fas/serialization/json/meta/sequence.hpp>

#include <fas/serialization/json/parser/aspect.hpp>

#include <fas/range/range.hpp>

#include <fas/type_list/empty_list.hpp>



UNIT(ad_field_list_test1, "test fas::json::deser::ad_field_list advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  
  foo f(0);
  ad_primary_list adfl;
  
  typedef primary_list< empty_list > foo_list1;
  adfl(t, foo_list1(), f, range("") );
  t << equal<expect>(f, foo(0) ) << FAS_TESTING_FILE_LINE;
  
  typedef primary_list< attr<foo, int, &foo::foo1, integer> > foo_list2;
  adfl(t, foo_list2(), f, range("-1") );
  t << equal<expect>(f.foo1, -1 ) << FAS_TESTING_FILE_LINE;
  f = foo(0);
  
  typedef primary_list< 
    type_list_n<
      attr<foo, int, &foo::foo1, integer>,
      attr<foo, std::string, &foo::foo2, string>
    >::type
  > foo_list3;
  adfl(t, foo_list3(), f, range("-1,\"test-foo2\"") );
  t << equal<expect>(f.foo1, -1 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
  f = foo(0);

  typedef primary_list< 
    type_list_n<
      attr<foo, int, &foo::foo1, integer>,
      attr<foo, std::string, &foo::foo2, string>,
      attr<foo, foo::foo3type, &foo::foo3, string>
    >::type
  > foo_list4;
  adfl(t, foo_list4(), f, range("-1,\"test-foo2\",\"test-foo3\"") );
  t << equal<expect>(f.foo1, -1 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo3, std::string("test-foo3") ) << FAS_TESTING_FILE_LINE;
}


UNIT(ad_field_list_test2, "test fas::json::deser::ad_field_list advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;
  
  bar b(0);
  ad_primary_list adfl;

  typedef primary_list< 
    type_list_n<
      attr<foo, int, &foo::foo1, integer>,
      attr<foo, std::string, &foo::foo2, string>,
      attr<foo, foo::foo3type, &foo::foo3, string>,
      attr<bar, bar::baz, &bar::bar1, attr<bar::baz, int, &bar::baz::baz1, integer> >,
      attr<bar, foo, &bar::bar2, attr<foo, std::string, &foo::foo2, string> >
    >::type
  > bar_list1;
  adfl(t, bar_list1(), b, range("-1,\"test-foo2\",\"test-foo3\",42,\"test-foo2\"") );
  t << equal<expect>(b.foo1, -1 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo3, std::string("test-foo3") ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar1.baz1, 42 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar2.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
}

UNIT(ad_field_list_test3, "test fas::json::deser::ad_field_list advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  
  bar b(0);
  ad_primary_list adfl;

  typedef primary_list< 
    type_list_n<
      attr<foo, int, &foo::foo1, integer>,
      attr<foo, std::string, &foo::foo2, string>,
      attr<foo, foo::foo3type, &foo::foo3, string>,
      attr<bar, bar::baz, &bar::bar1, attr<bar::baz, int, &bar::baz::baz1, integer> >,
      attr<bar, foo, &bar::bar2, attr<foo, std::string, &foo::foo2, string> >,
      attr<bar, foo, &bar::bar2, attr<foo, foo::foo5type, &foo::foo5, sequence<integer> > >,
      attr<bar, foo, &bar::bar2, attr<foo, std::vector<std::string>, &foo::foo6, sequence<string> > >
    >::type
  > bar_list1;

  string_range<const char*> r = string_range<const char*>("-1,\"test-foo2\",\"test-foo3\",42,\"test-foo2\",0,1,2,3,4,\"test-foo6-1\",\"test-foo6-2\"");
  try
  {
    adfl(t, bar_list1(), b, r );
  }
  catch(const json_error& e)
  {
    std::cout << e.message(r) << std::endl;
    throw;
  }
  
  t << equal<expect>(b.foo1, -1 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo3, std::string("test-foo3") ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar1.baz1, 42 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar2.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar2.foo5[0], 0 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar2.foo5[1], 1 ) << b.bar2.foo5[1] << "|" << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar2.foo5[2], 2 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar2.foo5[3], 3 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar2.foo5[4], 4 ) << FAS_TESTING_FILE_LINE;
// не десериализуется т.к. остаток сожрал foo5 
// на самом деле он не сожрал т.к. фиксированного размера 
  t << equal<assert>(b.bar2.foo6.size(), (size_t)2 ) << FAS_TESTING_FILE_LINE;
//  t << is_true<assert>(1);
//#warning после assert выполняется следующая команда, что может привести к краху 
  t << equal<expect>(b.bar2.foo6[0], "test-foo6-1" ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar2.foo6[1], "test-foo6-2" ) << FAS_TESTING_FILE_LINE;
  

  
}


BEGIN_SUITE(field_list_deserialize_suite, "field_list deserializer suite")
  
  ADD_UNIT(ad_field_list_test1)
  ADD_UNIT(ad_field_list_test2)
  ADD_UNIT(ad_field_list_test3)
  ADD_ADVICE( ::fas::json::deser::_integer_, ::fas::json::deser::ad_integer)
  ADD_ADVICE( ::fas::json::deser::_string_, ::fas::json::deser::ad_string)
  ADD_ADVICE( ::fas::json::deser::_attr_, ::fas::json::deser::ad_attr)
  ADD_ADVICE( ::fas::json::deser::_sequence_, ::fas::json::deser::ad_sequence)
	ADD_ADVICE( ::fas::json::deser::_separator_, ::fas::json::deser::ad_separator)
  ADD_ASPECT(::fas::json::parse::aspect)
END_SUITE(field_list_deserialize_suite)
