#include <fas/testing.hpp>

#include <fas/serialization/json/deser/tags.hpp>
#include <fas/serialization/json/deser/ad_array.hpp>
#include <fas/serialization/json/deser/ad_attr.hpp>
#include <fas/serialization/json/deser/ad_primary_list.hpp>
#include <fas/serialization/json/deser/ad_brute_list.hpp>
#include <fas/serialization/json/deser/ad_brute_pair.hpp>

#include <fas/serialization/json/deser/ad_stub.hpp>
#include <fas/serialization/json/deser/ad_sequence.hpp>
#include <fas/serialization/json/deser/ad_string.hpp>
#include <fas/serialization/json/deser/ad_integer.hpp>
#include <fas/serialization/json/deser/ad_enumeration.hpp>
#include <fas/serialization/json/deser/ad_member.hpp>

#include <fas/serialization/json/deser/deserialize_integer.hpp>
#include <fas/serialization/json/deser/deserialize_array.hpp>
#include <fas/serialization/json/meta/integer.hpp>
#include <fas/serialization/json/meta/array.hpp>
#include <fas/serialization/json/meta/string.hpp>
#include <fas/serialization/json/meta/member.hpp>
#include <fas/serialization/json/meta/attr.hpp>
#include <fas/serialization/json/meta/enumeration.hpp>
#include <fas/serialization/json/meta/brute_list.hpp>
#include <fas/serialization/json/meta/brute_pair.hpp>
#include <fas/serialization/json/meta/enumset.hpp>
#include <fas/serialization/json/meta/enumset_value.hpp>

#include <fas/serialization/json/parser/aspect.hpp>

#include "../../foo.hpp"
#include "../../names.hpp"
#include <fas/range/range.hpp>
#include <fas/typemanip/tstring.hpp>
#include <vector>
#include <string>
#include <cstring>

using namespace ::fas;
using namespace ::fas::json;

UNIT(array_deserialize_test1, "test array_deserialize function")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  std::vector<int> result;

  deserialize_array(
    init_range(result),
    range("[1,2,3]"),
    deserialize_integer<int, range_traits<const char*>::range>
  );

  t << equal<assert, int>(result.size(), 3) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[0], 1) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[1], 2) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[2], 3) << FAS_TESTING_FILE_LINE;
}

UNIT(array_deserialize_test2, "test array_deserialize function")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  int result[5]={0};

  deserialize_array(
    init_range(result),
    range("[1,2,3]"),
    deserialize_integer<int, range_traits<const char*>::range>
  );

  t << equal<expect>(result[0], 1) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[1], 2) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[2], 3) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[3], 0) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[4], 0) << FAS_TESTING_FILE_LINE;
}

UNIT(ad_array_test1, "test ad_array advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  std::vector<int> result;
  ad_array ada;

  ada(t, array<integer>(), result, range("[1,\"foo\", 2, true, 3]") );
  
  t << equal<assert, int>(result.size(), 3) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[0], 1) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[1], 2) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[2], 3) << FAS_TESTING_FILE_LINE;

}



UNIT(ad_array_test2, "test ad_array advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  foo f(0);
  ad_attr ada;

  typedef attr<foo, std::vector<int>, &foo::foo4, array<integer> > foo4_json;
  ada(t, foo4_json(), f, range("[20,[],30,{},40]") );
  t << equal<assert, int>(f.foo4.size(), 3) << f.foo4.size() << "|" << FAS_TESTING_FILE_LINE << stop;

  t << equal<expect>(f.foo4[0], 20) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo4[1], 30) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo4[2], 40) << FAS_TESTING_FILE_LINE;
  
}


UNIT(ad_array_test3, "test ad_array advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;


  typedef array<
    type_list_n<
      attr<foo, int, &foo::foo1, integer>,
      attr<foo, std::string, &foo::foo2, string>,
      attr<foo, foo::foo3type, &foo::foo3, string>,
      attr<foo, foo::foo5type, &foo::foo5, array<integer> >,
      attr<foo, std::vector<int>, &foo::foo4, array<integer> >,
      attr<foo, std::vector<std::string>, &foo::foo6, array<string> >
    >::type 
  > foo_json;

  foo f(0);
  ad_array ada;
  string_range<const char*> r = string_range<const char*>("[-1,\"test-foo2\",\"test-foo3\",[1,2,3,4,5],[20,30,40],[\"test-foo6-1\",\"test-foo6-2\"]]");
  try
  {
    r = ada(t, foo_json(), f, r );
  }
  catch(const json_error& e)
  {
    t << fail(e.what() ) << e.message(r) << std::endl;
    throw;
  }

  t << message("TRACE") << std::string(r.begin(), r.end());
  //ada(t, foo_json(), f, ("[-1,\"test-foo2\",\"test-foo3\",[0,1,2,3,4],[20,30,40],[\"test-foo6-1\",\"test-foo6-2\"]]") );

  t << equal<expect>(f.foo1, -1 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo3, std::string("test-foo3") ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo5[0], 1 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo5[1], 2 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo5[2], 3 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo5[3], 4 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo5[4], 5 ) << FAS_TESTING_FILE_LINE;

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

UNIT(ad_array_test4, "test ad_array advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  
  typedef array<
    brute_pair<
    type_list_n<
      attr<foo, int, &foo::foo1, integer>,
      attr<foo, std::string, &foo::foo2, string>,
      attr<foo, foo::foo3type, &foo::foo3, string>,
      attr<foo, foo::foo5type, &foo::foo5, sequence<integer> >
    >::type 
    ,
    type_list_n<
      attr<foo, std::vector<int>, &foo::foo4, sequence<integer> >,
      attr<foo, std::vector<std::string>, &foo::foo6, sequence<string> >
    >::type
    >
  > foo_json;

  foo f(0);
  ad_array ada;
  
  string_range<const char*> r = string_range<const char*>("[-1,\"test-foo2\",\"test-foo3\",1,2,3,4,5,20,30,40,\"test-foo6-1\",\"test-foo6-2\"]");
  try
  {
    r = ada(t, foo_json(), f, r );
  }
  catch(const json_error& e)
  {
    t << fail(e.what() ) << e.message(r) << std::endl;
    throw;
  }

  t << equal<expect>(f.foo1, -1 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo2, "test-foo2" ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo3, std::string("test-foo3") ) << FAS_TESTING_FILE_LINE;

  t << equal<expect>(f.foo5[0], 1 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo5[1], 2 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo5[2], 3 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo5[3], 4 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo5[4], 5 ) << FAS_TESTING_FILE_LINE;

  
  t << equal<assert, int>(f.foo4.size(), 3 ) << FAS_TESTING_FILE_LINE
    << stop;
  
  t << equal<expect>(f.foo4[0], 20 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo4[1], 30 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo4[2], 40 ) << FAS_TESTING_FILE_LINE;

  t << equal<assert, int>(f.foo6.size(), 2 ) << FAS_TESTING_FILE_LINE
    << stop;
  t << equal<expect>(f.foo6[0], "test-foo6-1" ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(f.foo6[1], "test-foo6-2" ) << FAS_TESTING_FILE_LINE;


/*  std::cout << separator<>()() << std::endl;
  std::cout << separator<'a'>()() << std::endl;
  */
  /*
  std::string result;
  t << message("") << blue << "-1-" <<std::endl; 
  ada(t, foo_json(), f, (result) );
  t << message("") << blue << "-2-" <<std::endl; 
  t << message("result");
  /// [-1,"test-foo2","test-foo3",0,1,2,3,4,20,30,40,"test-foo6-1","test-foo6-2"]
  t << equal<expect>(result, "[-1,\"test-foo2\",\"test-foo3\",0,1,2,3,4,20,30,40,\"test-foo6-1\",\"test-foo6-2\"]") << FAS_TESTING_FILE_LINE;
  t << message("result");
  */
  //t << fail("test fail");
}


namespace test_array{ 
FAS_NAME(value1);
FAS_NAME(value2);
FAS_NAME(value3);

typedef enum { value1 = 0x1, value2 = 0x2, value3 = 0x4 } test_enum;
}

UNIT(ad_enumset_test, "test fas::serialization::json::ser::enumset")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;
  using namespace test_array;
  

  typedef enumset<
    typename type_list_n<
      enumset_value<n_value1, value1>,
      enumset_value<n_value2, value2>,
      enumset_value<n_value3, value3>
    >::type
  > enum_json;

// #warning int result = -1; не работает т.к. enumset не сбрасывает в ноль
  int result = 0;
  ad_array ade;
  std::string value = "[ \"value1\" , \"value3\"  ]";
  
  ade(t, enum_json(), result, range(value) );
  
  t << equal<expect>(result, value1|value3)  << result <<  FAS_TESTING_FILE_LINE;

  result = 0;
  value = "[]";
  ade(t, enum_json(), result, range(value) );
  t << equal<expect>(result, 0 ) << result << FAS_TESTING_FILE_LINE;

  result = 0;
  value = "[\"value1\",\"value2\",\"value3\"]";
  ade(t, enum_json(), result, range(value) );
  t << equal<expect>(result, value1|value2|value3 ) << result << FAS_TESTING_FILE_LINE;

}

BEGIN_SUITE(array_deserialize_suite, "array serializer suite")
  ADD_UNIT(array_deserialize_test1)
  ADD_UNIT(array_deserialize_test2)
  ADD_UNIT(ad_array_test1)
  ADD_UNIT(ad_array_test2)
  ADD_UNIT(ad_array_test3)
  ADD_UNIT(ad_array_test4)
  ADD_UNIT(ad_enumset_test)
  ADD_ADVICE( ::fas::json::deser::_string_, ::fas::json::deser::ad_string)
  ADD_ADVICE( ::fas::json::deser::_cstring_, ::fas::json::deser::ad_cstring)
  ADD_ADVICE( ::fas::json::deser::_integer_, ::fas::json::deser::ad_integer)
  ADD_ADVICE( ::fas::json::deser::_sequence_, ::fas::json::deser::ad_sequence)
  ADD_ADVICE( ::fas::json::deser::_array_, ::fas::json::deser::ad_array)
  //ADD_ADVICE( ::fas::json::deser::_member_list_, ::fas::json::deser::ad_member_list)
  //ADD_ADVICE( ::fas::json::deser::_field_list_, ::fas::json::deser::ad_field_list)
  //ADD_ADVICE( ::fas::json::deser::_field_list2_, ::fas::json::deser::ad_field_list2)
  ADD_ADVICE( ::fas::json::deser::_attr_, ::fas::json::deser::ad_attr)
  ADD_ADVICE( ::fas::json::deser::_primary_list_, ::fas::json::deser::ad_primary_list)
  ADD_ADVICE( ::fas::json::deser::_brute_list_, ::fas::json::deser::ad_brute_list)
  ADD_ADVICE( ::fas::json::deser::_brute_pair_, ::fas::json::deser::ad_brute_pair)
  ADD_ADVICE( ::fas::json::deser::_stub_, ::fas::json::deser::ad_stub)
  ADD_ADVICE( ::fas::json::deser::_enumset_value_, ::fas::json::deser::ad_enumset_value)

  ADD_ASPECT(::fas::json::parse::aspect)
END_SUITE(array_deserialize_suite)
