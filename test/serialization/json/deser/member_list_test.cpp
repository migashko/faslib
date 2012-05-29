#include <fas/testing.hpp>

#include "../../foo.hpp"
#include "../../bar.hpp"
#include "../../names.hpp"

#include <fas/serialization/json/deser/ad_primary_list.hpp>
#include <fas/serialization/json/deser/ad_separator.hpp>
#include <fas/serialization/json/deser/ad_brute_list.hpp>

#include <fas/serialization/json/deser/ad_brute_pair.hpp>

#include <fas/serialization/json/deser/ad_attr.hpp>

#include <fas/serialization/json/deser/ad_field.hpp>
#include <fas/serialization/json/deser/ad_integer.hpp>
#include <fas/serialization/json/deser/ad_string.hpp>
#include <fas/serialization/json/deser/ad_sequence.hpp>
#include <fas/serialization/json/deser/ad_array.hpp>
#include <fas/serialization/json/deser/ad_stub.hpp>

#include <fas/serialization/json/meta/primary_list.hpp>
#include <fas/serialization/json/meta/attr.hpp>
#include <fas/serialization/json/meta/field.hpp>
#include <fas/serialization/json/meta/integer.hpp>
#include <fas/serialization/json/meta/string.hpp>
#include <fas/serialization/json/meta/sequence.hpp>
#include <fas/serialization/json/meta/array.hpp>
#include <fas/serialization/json/meta/stub.hpp>
#include <fas/serialization/json/meta/brute_list.hpp>
#include <fas/serialization/json/meta/brute_pair.hpp>

#include <fas/serialization/json/parser/aspect.hpp>

#include <fas/range/range.hpp>
#include <fas/type_list/empty_list.hpp>
#include <fas/type_list/type_list_n.hpp>


UNIT(ad_primary_list_test1, "test fas::json::deser::ad_primary_list advice")
{
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;
  
  typedef fas::type_list_n<
      field< n_foo1, attr<foo, int, &foo::foo1, integer> >,
      field< n_foo2, attr<foo, std::string, &foo::foo2, string> >,
      field< n_foo3, attr<foo, foo::foo3type, &foo::foo3, string> >,
      field< n_foo5, attr<foo, foo::foo5type, &foo::foo5, array<integer> > >, // Игнорим в этом тесте
      field< n_bar1, attr<bar, bar::baz, &bar::bar1, attr<bar::baz, int, &bar::baz::baz1, integer> > >,
      field< n_bar2, attr<bar, foo, &bar::bar2, attr<foo, std::string, &foo::foo2, string> > >
  >::type field_list_type;
  
  typedef primary_list< field_list_type > primary_list_type;
  
  std::string json = "\"foo1\" : 10 , \"foo2\" : \"test-foo2\" , \"foo3\" : \"test-foo3\" , \"bar1\" : 47, \"bar2\" : \"test-foo2\" }";
  
  bar b(0);
  ad_primary_list apr;
  apr(t, primary_list_type(), b, fas::range(json) );
  
  t << equal<expect>(b.foo1, 10 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo3, std::string("test-foo3") ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar1.baz1, 47 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar2.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;

  std::cout << "===============" << std::endl;
  
  json = "\"foo1\" : 10 , \"foo2\" : \"test-foo2\" , \"barX\" : 47, \"foo3\" : \"test-foo3\" , \"foo5\" : [0,1,2,3,4] , \"bar1\" : 47 , \"bar2\" : \"test-foo2\" }";
  b = bar(0);
  apr(t, primary_list_type(), b, fas::range(json) );

  t << equal<expect>(b.foo1, 10 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo3, std::string("test-foo3") ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar1.baz1, 47 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar2.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;

  
  std::cout << "===============" << std::endl;
  
  json = "\"foo2\":\"test-foo2\",\"foo3\":\"test-foo3\",\"bar1\":47,\"bar2\":\"test-foo2\",\"foo1\":10";
  b = bar(0);
  apr(t, primary_list_type(), b, fas::range(json) );

  t << equal<expect>(b.foo1, 10 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo3, std::string("test-foo3") ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar1.baz1, 47 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar2.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;

  std::cout << "===============" << std::endl;
  json = "\"bar2\":\"test-foo2\",\"foo2\":\"test-foo2\",\"barX\":47,\"foo3\":\"test-foo3\",\"bar1\":47,\"foo1\":10";
  b = bar(0);
  apr(t, primary_list_type(), b, fas::range(json) );

  t << equal<expect>(b.foo1, 10 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo3, std::string("test-foo3") ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar1.baz1, 47 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar2.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;

}

UNIT(ad_brute_list_test1, "test fas::json::deser::ad_brute_list advice")
{
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;
  
  typedef fas::type_list_n<
      field< n_foo1, attr<foo, int, &foo::foo1, integer> >,
      field< n_foo2, attr<foo, std::string, &foo::foo2, string> >,
      field< n_foo3, attr<foo, foo::foo3type, &foo::foo3, string> >,
      field< n_foo5, attr<foo, foo::foo5type, &foo::foo5, array<integer> > >, // Игнорим в этом тесте
      field< n_bar1, attr<bar, bar::baz, &bar::bar1, attr<bar::baz, int, &bar::baz::baz1, integer> > >,
      field< n_bar2, attr<bar, foo, &bar::bar2, attr<foo, std::string, &foo::foo2, string> > >
  >::type field_list_type;
  
  typedef brute_list< field_list_type > brute_list_type;
  
  std::string json = "\"foo1\" : 10 , \"foo2\" : \"test-foo2\" , \"foo3\" : \"test-foo3\" , \"bar1\" : 47, \"bar2\" : \"test-foo2\" }";
  
  bar b(0);
  ad_brute_list apr;
  apr(t, brute_list_type(), b, fas::range(json) );
  
  t << equal<expect>(b.foo1, 10 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo3, std::string("test-foo3") ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar1.baz1, 47 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar2.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;

  std::cout << "===============" << std::endl;
  
  json = "\"foo1\" : 10 , \"foo2\" : \"test-foo2\" , \"barX\" : 47, \"foo3\" : \"test-foo3\" , \"foo5\" : [0,1,2,3,4] , \"bar1\" : 47 , \"bar2\" : \"test-foo2\" ";
  b = bar(0);
  apr(t, brute_list_type(), b, fas::range(json) );

  t << equal<expect>(b.foo1, 10 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo3, std::string("test-foo3") ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar1.baz1, 47 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar2.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;

  
  std::cout << "===============" << std::endl;
  
  json = "\"foo2\":\"test-foo2\",\"foo3\":\"test-foo3\",\"bar1\":47,\"bar2\":\"test-foo2\",\"foo1\":10";
  b = bar(0);
  apr(t, brute_list_type(), b, fas::range(json) );

  t << equal<expect>(b.foo1, 10 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo3, std::string("test-foo3") ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar1.baz1, 47 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar2.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;

  std::cout << "===============" << std::endl;
  json = "\"bar2\":\"test-foo2\",\"foo2\":\"test-foo2\",\"barX\":47,\"foo3\":\"test-foo3\",\"bar1\":47,\"foo1\":10";
  b = bar(0);
  apr(t, brute_list_type(), b, fas::range(json) );

  t << equal<expect>(b.foo1, 10 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo3, std::string("test-foo3") ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar1.baz1, 47 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar2.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
}


UNIT(ad_pair_test1, "test fas::json::deser::ad_brute_list advice")
{
  
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;
  
  typedef fas::type_list_n<
      field< n_foo1, attr<foo, int, &foo::foo1, integer> >,
      field< n_foo2, attr<foo, std::string, &foo::foo2, string> >,
      field< n_foo3, attr<foo, foo::foo3type, &foo::foo3, string> >
  >::type field_list1_type;

  typedef fas::type_list_n<
      field< n_foo5, attr<foo, foo::foo5type, &foo::foo5, array<integer> > >, // Игнорим в этом тесте
      field< n_bar1, attr<bar, bar::baz, &bar::bar1, attr<bar::baz, int, &bar::baz::baz1, integer> > >,
      field< n_bar2, attr<bar, foo, &bar::bar2, attr<foo, std::string, &foo::foo2, string> > >
  >::type field_list2_type;

  typedef ::fas::json::brute_pair< field_list1_type, field_list2_type > pair_type;
  
  std::string json = "\"foo1\" : 12 , \"foo2\" : \"test-foo2x\" , \"foo3\" : \"test-foo3x\" , \"bar1\" : 47, \"bar2\" : \"test-foo2\" }";
  
  bar b(0);
  ad_brute_pair apr;
  apr(t, pair_type(), b, fas::range(json) );
  
  t << equal<expect>(b.foo1, 12 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(std::string(b.foo2), std::string("test-foo2x") ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo3, std::string("test-foo3x") ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar1.baz1, 47 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar2.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;

  std::cout << "===============" << std::endl;
  
  json = "\"foo1\" : 10 , \"foo2\" : \"test-foo2\" , \"barX\" : 47, \"foo3\" : \"test-foo3\" , \"foo5\" : [0,1,2,3,4] , \"bar1\" : 47 , \"bar2\" : \"test-foo2\" ";
  b = bar(0);
  apr(t, pair_type(), b, fas::range(json) );

  t << equal<expect>(b.foo1, 10 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo3, std::string("test-foo3") ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar1.baz1, 47 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar2.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;

  
  std::cout << "===============" << std::endl;
  
  json = "\"foo2\":\"test-foo2\",\"foo3\":\"test-foo3\",\"bar1\":47,\"bar2\":\"test-foo2\",\"foo1\":10";
  b = bar(0);
  apr(t, pair_type(), b, fas::range(json) );

  t << equal<expect>(b.foo1, 10 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo3, std::string("test-foo3") ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar1.baz1, 47 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar2.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;

  std::cout << "===============" << std::endl;
  json = "\"bar2\":\"test-foo2\",\"foo2\":\"test-foo2\",\"barX\":47,\"foo3\":\"test-foo3\",\"bar1\":47,\"foo1\":10";
  b = bar(0);
  apr(t, pair_type(), b, fas::range(json) );

  t << equal<expect>(b.foo1, 10 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo3, std::string("test-foo3") ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar1.baz1, 47 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar2.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;

}

UNIT(ad_field_list_test1, "test fas::json::deser::ad_field_list advice")
{
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  foo f = foo(0);
  ad_primary_list adfl;


  typedef primary_list< fas::empty_list > foo_list1;
  adfl(t, foo_list1(), f, fas::range("") );
  t << equal<expect>(f, foo(0) ) << FAS_TESTING_FILE_LINE;
  f = foo(0);
  
  typedef primary_list< field< n_foo1, attr<foo, int, &foo::foo1, integer> > > foo_list2;
  adfl(t, foo_list2(), f, fas::range("\"foo1\":-1") );
  t << equal<expect>(f.foo1, -1 ) << FAS_TESTING_FILE_LINE;
  f = foo(0);

  typedef primary_list< 
    fas::type_list_n<
      field< n_foo1, attr<foo, int, &foo::foo1, integer> >,
      field< n_foo2, attr<foo, std::string, &foo::foo2, string> >
    >::type
  > foo_list3;
  adfl(t, foo_list3(), f, fas::range("\"foo1\":-1,\"foo2\":\"test-foo2\"}") );
  t << equal<expect>(f.foo1, -1 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
  f = foo(0);

  typedef primary_list< 
    fas::type_list_n<
      field< n_foo1, attr<foo, int, &foo::foo1, integer> >,
      field< n_foo2, attr<foo, std::string, &foo::foo2, string> >,
      field< n_foo3, attr<foo, foo::foo3type, &foo::foo3, string> >
    >::type
  > foo_list4;
  adfl(t, foo_list4(), f, fas::range("\"foo1\":-1,\"foo2\":\"test-foo2\",\"foo3\":\"test-foo3\"") );
  t << equal<expect>(f.foo1, -1 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo3, std::string("test-foo3") ) << FAS_TESTING_FILE_LINE;
  f = foo(0);

}


UNIT(ad_field_list_test2, "test fas::json::deser::ad_field_list advice")
{
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  
  bar b(0);
  ad_primary_list adfl;
  std::string result;

  typedef primary_list< 
    fas::type_list_n<
      field< n_foo1, attr<foo, int, &foo::foo1, integer> >,
      field< n_foo2, attr<foo, std::string, &foo::foo2, string> >,
      field< n_foo3, attr<foo, foo::foo3type, &foo::foo3, string> >,
      field< n_bar1, attr<bar, bar::baz, &bar::bar1, attr<bar::baz, int, &bar::baz::baz1, integer> > >,
      field< n_bar2, attr<bar, foo, &bar::bar2, attr<foo, std::string, &foo::foo2, string> > >
    >::type
  > bar_list1;
  adfl(t, bar_list1(), b, fas::range("\"foo1\":-1,\"foo2\":\"test-foo2\",\"foo3\":\"test-foo3\",\"bar1\":42,\"bar2\":\"test-foo2\"") );
  t << equal<expect>(b.foo1, -1 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo3, std::string("test-foo3") ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar1.baz1, 42 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar2.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
}

UNIT(ad_field_list_test3, "test fas::json::deser::ad_field_list advice")
{
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  
  bar b(0);
  ad_primary_list adfl;
  std::string result;

  typedef primary_list< 
    fas::type_list_n<
      field< n_foo1, attr<foo, int, &foo::foo1, integer> >,
      field< n_foo2, attr<foo, std::string, &foo::foo2, string> >,
      field< n_foo3, attr<foo, foo::foo3type, &foo::foo3, string> >,
      field< n_bar1, attr<bar, bar::baz, &bar::bar1, attr<bar::baz, int, &bar::baz::baz1, integer> > >,
      field< n_bar2, attr<bar, foo, &bar::bar2, attr<foo, std::string, &foo::foo2, string> > >,
      field< n_foo5, attr<foo, foo::foo5type, &foo::foo5, array<integer> > >,
      field< n_foo6, attr<foo, std::vector<std::string>, &foo::foo6, array<string> > >
    >::type
  > bar_list1;
  adfl(t, bar_list1(), b, fas::range("\"foo1\":-1,\"foo2\":\"test-foo2\",\"foo3\":\"test-foo3\","
              "\"bar1\":42,\"bar2\":\"test-foo2\",\"foo5\":[0,1,2,3,4],\"foo6\":[\"test-foo6-1\",\"test-foo6-2\"]") );

  t << equal<expect>(b.foo1, -1 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo3, std::string("test-foo3") ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar1.baz1, 42 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.bar2.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
/*  t << equal<assert>(b.foo5.size(), 5 ) << FAS_TESTING_FILE_LINE;
  t << message("") << colors::red << "break";*/
  t << equal<expect>(b.foo5[0], 0 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo5[1], 1 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo5[2], 2 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo5[3], 3 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo5[4], 4 ) << FAS_TESTING_FILE_LINE;
  t << equal<assert, int>(b.foo6.size(), 2 ) << FAS_TESTING_FILE_LINE << stop;
  t << equal<expect>(b.foo6[0], "test-foo6-1" ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(b.foo6[1], "test-foo6-2" ) << FAS_TESTING_FILE_LINE;
}


BEGIN_SUITE(member_list_deserialize_suite, "field_list deserializer suite")
  ADD_UNIT(ad_primary_list_test1)
  ADD_UNIT(ad_brute_list_test1)
  ADD_UNIT(ad_pair_test1)
  ADD_UNIT(ad_field_list_test1)
  ADD_UNIT(ad_field_list_test2)
  ADD_UNIT(ad_field_list_test3)
  

  ADD_ADVICE( ::fas::json::deser::_integer_, ::fas::json::deser::ad_integer)
  ADD_ADVICE( ::fas::json::deser::_string_, ::fas::json::deser::ad_string)
  ADD_ADVICE( ::fas::json::deser::_cstring_, ::fas::json::deser::ad_cstring)
  ADD_ADVICE( ::fas::json::deser::_attr_, ::fas::json::deser::ad_attr)
  //ADD_ADVICE( ::fas::json::deser::_field_list_, ::fas::json::deser::ad_field_list)
  ADD_ADVICE( ::fas::json::deser::_field_, ::fas::json::deser::ad_field)
  //ADD_ADVICE( ::fas::json::deser::_field_list_, ::fas::json::deser::ad_field_list)
  ADD_ADVICE( ::fas::json::deser::_sequence_, ::fas::json::deser::ad_sequence)
  ADD_ADVICE( ::fas::json::deser::_array_, ::fas::json::deser::ad_array)
  ADD_ADVICE( ::fas::json::deser::_stub_, ::fas::json::deser::ad_stub)
  ADD_ADVICE( ::fas::json::deser::_primary_list_, ::fas::json::deser::ad_primary_list)
  ADD_ADVICE( ::fas::json::deser::_brute_list_, ::fas::json::deser::ad_brute_list)
	ADD_ADVICE( ::fas::json::deser::_separator_, ::fas::json::deser::ad_separator)
  ADD_ASPECT(::fas::json::parse::aspect)

END_SUITE(member_list_deserialize_suite)
