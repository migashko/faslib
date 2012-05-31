#include <fas/testing.hpp>

#include <fas/serialization/json/deser/tags.hpp>
#include <fas/serialization/json/deser/ad_array.hpp>
#include <fas/serialization/json/deser/ad_object.hpp>
#include <fas/serialization/json/deser/ad_attr.hpp>
#include <fas/serialization/json/deser/ad_primary_list.hpp>
#include <fas/serialization/json/deser/ad_separator.hpp>
#include <fas/serialization/json/deser/ad_brute_list.hpp>
#include <fas/serialization/json/deser/ad_brute_pair.hpp>

#include <fas/serialization/json/deser/ad_stub.hpp>
#include <fas/serialization/json/deser/ad_sequence.hpp>
#include <fas/serialization/json/deser/aspect_string.hpp>
#include <fas/serialization/json/deser/ad_integer.hpp>
#include <fas/serialization/json/deser/ad_field.hpp>

#include <fas/serialization/json/deser/deserialize_integer.hpp>
#include <fas/serialization/json/deser/deserialize_array.hpp>
#include <fas/serialization/json/meta/integer.hpp>
#include <fas/serialization/json/meta/array.hpp>
#include <fas/serialization/json/meta/string.hpp>
#include <fas/serialization/json/meta/field.hpp>
#include <fas/serialization/json/meta/attr.hpp>
#include <fas/serialization/json/meta/fieldx.hpp>
#include <fas/serialization/json/meta/first.hpp>
#include <fas/serialization/json/meta/second.hpp>
#include <fas/serialization/json/meta/object.hpp>
#include <fas/serialization/json/meta/brute_pair.hpp>

#include <fas/serialization/json/parser/aspect.hpp>

#include "../../foo.hpp"
#include "../../bar.hpp"
#include "../../names.hpp"
#include <fas/range.hpp>
#include <fas/typemanip/tstring.hpp>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>

namespace aj = ::fas::json;
UNIT(ad_object_test1, "test ad_object advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  std::vector<int> result;
  ad_object ado;
  
  ado(t, object< sequence<integer> >(), result, range("{1,2,3}") );
  t << equal<assert, int>(result.size(), 3 ) << FAS_TESTING_FILE_LINE;
  t << is_true<expect>(1);
  t << equal<expect>(result[0], 1 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[1], 2 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[2], 3 ) << FAS_TESTING_FILE_LINE;
}



UNIT(ad_object_test2, "test ad_object advice")
{
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  foo f(0);
  ad_field adm;
  typedef field< n_foo4,  attr<foo, std::vector<int>, &foo::foo4, array<integer> > > foo4_json;
  adm(t, foo4_json(), f, fas::range("\"foo4\":[20,30,40]") );
  t << equal<assert, int>(f.foo4.size(), 3 ) << FAS_TESTING_FILE_LINE;
  t << is_true<expect>(1);
  t << equal<expect>(f.foo4[0], 20 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo4[1], 30 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo4[2], 40 ) << FAS_TESTING_FILE_LINE;
}


UNIT(ad_object_test3, "test ad_object advice")
{
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  typedef object<
    brute_pair<
    fas::type_list_n<
      field< n_foo1, attr<foo, int, &foo::foo1, integer> >,
      field< n_foo2, attr<foo, std::string, &foo::foo2, string> >,
      field< n_foo3, attr<foo, foo::foo3type, &foo::foo3, string> >,
      field< n_foo5, attr<foo, foo::foo5type, &foo::foo5, array<integer> > >,
      field< n_foo4, attr<foo, std::vector<int>, &foo::foo4, array<integer> >  >,
      field< n_foo6, attr<foo, std::vector<std::string>, &foo::foo6, array<string> >  >
    >::type
    ,
    fas::type_list_n<
    >::type
    >
  > foo_json;

  foo f(0);
  ad_object ado;
  const char json[] = 
      "{\"foo1\":-1,\"foo2\":\"test-foo2\",\"foo3\":\"test-foo3\","
      "\"foo5\":[6,5,4,3,2],\"foo4\":[20,30,40],\"foo6\":[\"test-foo6-1\",\"test-foo6-2\"]}";

  ado(t, foo_json(), f, fas::range(json) );
  
  t << equal<expect>(f.foo1, -1 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo3, std::string("test-foo3") ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo5[0], 6 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo5[1], 5 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo5[2], 4 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo5[3], 3 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo5[4], 2 ) << FAS_TESTING_FILE_LINE;
  
  t << equal<assert, int>(f.foo4.size(), 3 ) << FAS_TESTING_FILE_LINE 
    << stop;
  
  t << equal<expect>(f.foo4[0], 20 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo4[1], 30 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo4[2], 40 ) << FAS_TESTING_FILE_LINE;

  t << equal<assert, int>(f.foo6.size(), 2 ) << FAS_TESTING_FILE_LINE 
    << stop;
    
  t << equal<expect>(f.foo6[0], "test-foo6-1" ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo6[1], "test-foo6-2" ) << FAS_TESTING_FILE_LINE;
    /*
  foo f;
  ad_object ado;
  std::string result;
  ado(t, foo_json(), f, (result) );

  // t << message(result);
  /// {"foo1":-1,"foo2":"test-foo2","foo3":"test-foo3","foo5":[0,1,2,3,4],"foo4":[20,30,40],"foo6":["test-foo6-1","test-foo6-2"]}
  t << equal<expect>(result,
                     "{\"foo1\":-1,\"foo2\":\"test-foo2\",\"foo3\":\"test-foo3\","
                     "\"foo5\":[0,1,2,3,4],\"foo4\":[20,30,40],\"foo6\":[\"test-foo6-1\",\"test-foo6-2\"]}"
                    ) << FAS_TESTING_FILE_LINE;
    */
}

UNIT(ad_object_test3f, "test ad_object advice")
{
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  typedef object<
    brute_pair<
    fas::type_list_n<
      field< n_foo1, attr<foo, int, &foo::foo1, integer> >,
      field< n_foo2, attr<foo, std::string, &foo::foo2, string> >,
      field< n_foo3, attr<foo, foo::foo3type, &foo::foo3, string> >,
      field< n_foo5, attr<foo, foo::foo5type, &foo::foo5, array<integer> > >,
      field< n_foo4, attr<foo, std::vector<int>, &foo::foo4, array<integer> >  >,
      field< n_foo6, attr<foo, std::vector<std::string>, &foo::foo6, array<string> >  >
    >::type
    ,
    fas::type_list_n<
    >::type
    >
  > foo_json;

  foo f(0);
  ad_object ado;
  const char json[] =
      "{\"foo1\":-1,\"foo2\":\"test-foo2\",\"foo3\":\"test-foo3\","
      "\"foo5\":[6,5,4,3,2],\"foo4\":[20,30,40],\"foo6\":[\"test-foo6-1\",\"test-foo6-2\"]}";

  /*std::stringstream fi;
  fi << json;*/
  std::ofstream fo("ad_object_test3f.txt");
  fo << json;
  fo.close();
  std::ifstream fi("ad_object_test3f.txt");
  
  
  std::string ostr;

  /*fas::typerange<std::string>::orange ora(ostr);
  *(ora++) = '1';
  *(ora++) = '2';*/
  
  typedef fas::input_range_wrapper<
    fas::typerange<std::ifstream>::range,
    fas::typerange<std::string>::orange
  > irw_type;

  irw_type trt( fas::range(fi), fas::orange(ostr) );
  try{
    ado(t, foo_json(), f, trt );
  }
  catch(json_error& e)
  {
    //std::cout<<
    std::copy( std::istreambuf_iterator<char>(fi),  std::istreambuf_iterator<char>(), std::ostreambuf_iterator<char>(std::cout) ) ;
    t << fail( e.message(fas::range(fi)) );
  }
  

  t << equal<expect>(f.foo1, -1 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo3, std::string("test-foo3") ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo5[0], 6 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo5[1], 5 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo5[2], 4 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo5[3], 3 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo5[4], 2 ) << FAS_TESTING_FILE_LINE;

  t << equal<assert, int>(f.foo4.size(), 3 ) << FAS_TESTING_FILE_LINE
    << stop;

  t << equal<expect>(f.foo4[0], 20 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo4[1], 30 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo4[2], 40 ) << FAS_TESTING_FILE_LINE;

  t << equal<assert, int>(f.foo6.size(), 2 ) << FAS_TESTING_FILE_LINE
    << stop;

  t << equal<expect>(f.foo6[0], "test-foo6-1" ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo6[1], "test-foo6-2" ) << FAS_TESTING_FILE_LINE;
}

UNIT(ad_object_test4, "test ad_object advice")
{
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;
  
  typedef object<
      field< n_baz1, attr<bar::baz, int, &bar::baz::baz1, integer> >
  > baz_json;

  typedef object<
    fas::type_list_n<
      field< n_bar1, attr<bar, bar::baz, &bar::bar1, baz_json> >
    >::type
  > bar_json;

    /*
  bar f;
  ad_object ado;
  std::string result;
  ado(t, bar_json(), f, (result) );
  //t << message(result);
  /// {"bar1":{"baz1":42}}
  t << equal<expect>(result, "{\"bar1\":{\"baz1\":42}}") << FAS_TESTING_FILE_LINE;
    */
}

UNIT(ad_object_test5, "test ad_object advice")
{
 
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  typedef object<
    field< n_foo1, attr<foo, int, &foo::foo1, integer> >
  > foo_json;

  typedef object<
      field< n_baz1, attr<bar::baz, int, &bar::baz::baz1, integer> >
  > baz_json;

  typedef object<
    fas::type_list_n<
      field< n_bar1, attr<bar, bar::baz, &bar::bar1, baz_json> >,
      field< n_bar2, attr<bar, foo, &bar::bar2, foo_json> >,
      field< n_bar3, attr<bar, std::vector<foo>, &bar::bar3, array<foo_json> > >,
      field< n_bar4, attr<bar, bar::bar4type, &bar::bar4, array<foo_json> > >,
      field< n_bar5, attr<bar, bar::foo_set, &bar::bar5, array<foo_json> > >
    >::type
  > bar_json;

    /*
  bar f;
  ad_object ado;
  std::string result;
  ado(t, bar_json(), f, (result) );
  //t << message(result);
  /// {"bar1":{"baz1":42},"bar2":{"foo1":-1},"bar3":[{"foo1":-1}],"bar4":[{"foo1":-1},{"foo1":-1}],"bar5":[{"foo1":1},{"foo1":2}]}
  t << equal<expect>( result,
                      "{\"bar1\":{\"baz1\":42},\"bar2\":{\"foo1\":-1},\"bar3\":[{\"foo1\":-1}],"
                      "\"bar4\":[{\"foo1\":-1},{\"foo1\":-1}],\"bar5\":[{\"foo1\":1},{\"foo1\":2}]}"
                    ) << FAS_TESTING_FILE_LINE;
    */
}


UNIT(ad_object_test6, "test ad_object advice")
{
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  typedef object<
    field< n_foo1, attr<foo, int, &foo::foo1, integer> >
  > foo_json;

  typedef std::pair<std::string, foo> foo_pair;

  typedef object<
      brute_pair<
        field< n_key, aj::fieldX< std::string, aj::first, aj::string>/*attr< foo_pair, std::string, &foo_pair::first, string> */ >,
        field< n_value, aj::fieldX< std::string, aj::second, foo_json>/*attr< foo_pair, foo, &foo_pair::second, foo_json>*/ >
      >
  > foo6_map_json;

  typedef object<
      field<
        aj::fieldX< std::string, aj::first, aj::string>,
        aj::fieldX< std::string, aj::second, foo_json>
	  /*
        attr< foo_pair, std::string, &foo_pair::first, string>,
        attr< foo_pair, foo, &foo_pair::second, foo_json>
      */>
  > foo7_map_json;


  typedef object<
    fas::type_list_n<
      field< n_bar6, attr<bar, bar::foo_map, &bar::bar6, array<foo6_map_json> > >,
      field< n_bar7, attr<bar, bar::foo_map, &bar::bar7, array<foo7_map_json> > >
    >::type
  > bar_json;

    /*
  bar f;
  ad_object ado;
  std::string result;
  ado(t, bar_json(), f, (result) );
  //t << message(result);
///  {
///       "bar6":[
///          {"key":"bar6-1","value":{"foo1":-1}},
///          {"key":"bar6-2","value":{"foo1":-1}}
///       ],
///       "bar7":[
///          {"bar7-1":{"foo1":-1}},
///          {"bar7-2":{"foo1":-1}}
///       ]
///      }
  
  t << equal<expect>( result,
                      "{\"bar6\":[{\"key\":\"bar6-1\",\"value\":{\"foo1\":-1}},{\"key\":\"bar6-2\",\"value\":{\"foo1\":-1}}],"
                      "\"bar7\":[{\"bar7-1\":{\"foo1\":-1}},{\"bar7-2\":{\"foo1\":-1}}]}"
                    ) << FAS_TESTING_FILE_LINE;
    */
}

UNIT(ad_object_test7, "test ad_object advice")
{
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;


  typedef object<
    field< n_foo1, attr<foo, int, &foo::foo1, integer> >
  > foo_json;

  typedef std::pair<std::string, foo> foo_pair;


  typedef field<
	  aj::fieldX< std::string, aj::first, aj::string>,
	  aj::fieldX< std::string, aj::second, aj::string>
	  /*
    attr< foo_pair, std::string, &foo_pair::first, string>,
    attr< foo_pair, foo, &foo_pair::second, foo_json>*/

  > foo_field_json;


  typedef object<
    fas::type_list_n<
      attr<bar, bar::foo_map, &bar::bar6, sequence<foo_field_json> >,
      attr<bar, bar::foo_map, &bar::bar7, sequence<foo_field_json> >
    >::type
  > bar_json;
/*
  bar f;
  ad_object ado;
  std::string result;
  ado(t, bar_json(), f, (result) );
  //t << message(result);
/// {
///    "bar6-1":{"foo1":-1},
///    "bar6-2":{"foo1":-1},
///    "bar7-1":{"foo1":-1},
///    "bar7-2":{"foo1":-1}
/// }

  t << equal<expect>( result,
                      "{\"bar6-1\":{\"foo1\":-1},\"bar6-2\":{\"foo1\":-1},\"bar7-1\":{\"foo1\":-1},\"bar7-2\":{\"foo1\":-1}}"
                    ) << FAS_TESTING_FILE_LINE;
  */
}

BEGIN_SUITE(object_deserialize_suite, "object deserializer suite")
  ADD_UNIT(ad_object_test1)
  ADD_UNIT(ad_object_test2)
  ADD_UNIT(ad_object_test3)
  ADD_UNIT(ad_object_test3f)
  ADD_UNIT(ad_object_test4)
  ADD_UNIT(ad_object_test5)
  ADD_UNIT(ad_object_test6)
  ADD_UNIT(ad_object_test7)
  ADD_ADVICE( ::fas::json::deser::_string_, ::fas::json::deser::ad_string)
  ADD_ADVICE( ::fas::json::deser::_cstring_, ::fas::json::deser::ad_cstring)
  ADD_ADVICE( ::fas::json::deser::_integer_, ::fas::json::deser::ad_integer)
  ADD_ADVICE( ::fas::json::deser::_sequence_, ::fas::json::deser::ad_sequence)
  ADD_ADVICE( ::fas::json::deser::_array_, ::fas::json::deser::ad_array)
  ADD_ADVICE( ::fas::json::deser::_object_, ::fas::json::deser::ad_object)
  ADD_ADVICE( ::fas::json::deser::_field_, ::fas::json::deser::ad_field)
  //ADD_ADVICE( ::fas::json::deser::_field_list_, ::fas::json::deser::ad_field_list)
  ADD_ADVICE( ::fas::json::deser::_attr_, ::fas::json::deser::ad_attr)
  //ADD_ADVICE( ::fas::json::deser::_field_list_, ::fas::json::deser::ad_field_list)
  //ADD_ADVICE( ::fas::json::deser::_field_list2_, ::fas::json::deser::ad_field_list2)
  ADD_ADVICE( ::fas::json::deser::_primary_list_, ::fas::json::deser::ad_primary_list)
  ADD_ADVICE( ::fas::json::deser::_brute_list_, ::fas::json::deser::ad_brute_list)
  ADD_ADVICE( ::fas::json::deser::_brute_pair_, ::fas::json::deser::ad_brute_pair)
  ADD_ADVICE( ::fas::json::deser::_stub_, ::fas::json::deser::ad_stub)
	ADD_ADVICE( ::fas::json::deser::_comma_, ::fas::json::deser::ad_comma)
  ADD_ASPECT(::fas::json::parse::aspect)
	ADD_ASPECT( ::fas::json::deser::string_aspect )
END_SUITE(object_deserialize_suite)
