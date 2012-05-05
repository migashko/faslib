#include <fas/testing.hpp>

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/ser/ad_array.hpp>
#include <fas/serialization/json/ser/ad_attr.hpp>
#include <fas/serialization/json/ser/ad_primary_list.hpp>
#include <fas/serialization/json/ser/ad_brute_list.hpp>
#include <fas/serialization/json/ser/ad_brute_pair.hpp>
#include <fas/serialization/json/ser/ad_null.hpp>

#include <fas/serialization/json/ser/ad_stub.hpp>
#include <fas/serialization/json/ser/ad_sequence.hpp>
#include <fas/serialization/json/ser/ad_string.hpp>
#include <fas/serialization/json/ser/ad_enumeration.hpp>
#include <fas/serialization/json/ser/ad_enumset_value.hpp>
#include <fas/serialization/json/ser/ad_integer.hpp>
#include <fas/serialization/json/ser/ad_member.hpp>

#include <fas/serialization/json/except/ad_except.hpp>

#include <fas/serialization/json/ser/serialize_integer.hpp>
#include <fas/serialization/json/ser/serialize_array.hpp>
#include <fas/serialization/json/meta/integer.hpp>
#include <fas/serialization/json/meta/array.hpp>
#include <fas/serialization/json/meta/enumeration.hpp>
#include <fas/serialization/json/meta/string.hpp>
#include <fas/serialization/json/meta/member.hpp>
#include <fas/serialization/json/meta/attr.hpp>
#include <fas/serialization/json/meta/brute_pair.hpp>
#include <fas/serialization/json/meta/enumset.hpp>
#include <fas/serialization/json/meta/enumset_value.hpp>

#include "../../foo.hpp"
#include "../../names.hpp"
#include <fas/range/range.hpp>
#include <fas/range/orange.hpp>
#include <fas/typemanip/tstring.hpp>
#include <vector>
#include <string>
#include <cstring>


namespace aj = ::fas::json;


UNIT(array_serialize_test, "test array_serialize function")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;

  std::string result;
  std::vector<int> value;
  value.push_back(1);
  value.push_back(2);
  value.push_back(3);

  serialize_array(
    range(value),
    orange(result),
    serialize_integer<int, typerange<std::string>::orange >
  );

  t << equal<expect>(result, "[1,2,3]") << FAS_TESTING_FILE_LINE;
}

UNIT(ad_array_test1, "test ad_array advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;

  std::string result;
  std::vector<int> value;
  value.push_back(1);
  value.push_back(2);
  value.push_back(3);

  ad_array ada;
  ada(t, array<integer>(), value, orange(result) );
  t << equal<expect>(result, "[1,2,3]") << FAS_TESTING_FILE_LINE;
}



UNIT(ad_array_test2, "test ad_array advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;

  foo f;
  ad_attr ada;
  std::string result;

  typedef attr<foo, std::vector<int>, &foo::foo4, array<integer> > foo4_json;
  ada(t, foo4_json(), f, orange(result) );
  t << equal<expect>(result, "[20,30,40]") << FAS_TESTING_FILE_LINE;
}


UNIT(ad_array_test3, "test ad_array advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;

  typedef array<
    brute_pair<
    type_list_n<
      attr<foo, int, &foo::foo1, integer>,
      attr<foo, std::string, &foo::foo2, string>,
      attr<foo, foo::foo3type, &foo::foo3, string>
    >::type 
    ,
    type_list_n<
      attr<foo, foo::foo5type, &foo::foo5, array<integer> >,
      attr<foo, std::vector<int>, &foo::foo4, array<integer> >,
      attr<foo, std::vector<std::string>, &foo::foo6, array<string> >
    >::type
    >
  > foo_json;

  foo f;
  ad_array ada;
  std::string result;
  ada(t, foo_json(), f, orange(result) );

  // t << message(result);
  /// [-1,"test-foo2","test-foo3",[0,1,2,3,4],[20,30,40],["test-foo6-1","test-foo6-2"]]
  t << equal<expect>(result, "[-1,\"test-foo2\",\"test-foo3\",[0,1,2,3,4],[20,30,40],[\"test-foo6-1\",\"test-foo6-2\"]]") << FAS_TESTING_FILE_LINE;
}

UNIT(ad_array_test4, "test ad_array advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;

  typedef array<
    brute_pair<
    type_list_n<
      attr<foo, int, &foo::foo1, integer>,
      attr<foo, std::string, &foo::foo2, string>,
      attr<foo, foo::foo3type, &foo::foo3, string>
    >::type 
    ,
    type_list_n<
      attr<foo, foo::foo5type, &foo::foo5, sequence<integer> >,
      attr<foo, std::vector<int>, &foo::foo4, sequence<integer> >,
      attr<foo, std::vector<std::string>, &foo::foo6, sequence<string> >
    >::type
    >
  > foo_json;

  foo f;
  ad_array ada;
  std::string result;
  ada(t, foo_json(), f, orange(result) );
  //t << message(result);
  /// [-1,"test-foo2","test-foo3",0,1,2,3,4,20,30,40,"test-foo6-1","test-foo6-2"]
  t << equal<expect>(result, "[-1,\"test-foo2\",\"test-foo3\",0,1,2,3,4,20,30,40,\"test-foo6-1\",\"test-foo6-2\"]") << FAS_TESTING_FILE_LINE;
}

UNIT(ad_array_test5, "test ad_array advice")
{
  using namespace ::fas::testing;
  using namespace ::fas::json::ser;
  
  //typedef aj::array< aj::string> one_item_json;
  /*std::string svalue="value";
  std::vector<std::string> value;
  value.push_back(svalue);
  */
  typedef aj::array< aj::integer > one_item_json;
  int value=10;
  
  std::string result;
  ad_array ada;
  ada(t, one_item_json(), value, fas::orange(result) );
  t << equal<expect>(result, "[\"value\"]") << FAS_TESTING_FILE_LINE 
    << std::endl << result;
  
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
  using namespace ::fas::json::ser;
  using namespace test_array;
  

  typedef enumset<
    typename type_list_n<
      enumset_value<n_value1, value1>,
      enumset_value<n_value2, value2>,
      enumset_value<n_value3, value3>
    >::type
  > enum_json;

  std::string result;
  ad_array ade;
  int value = value1 | value3;
  
  ade(t, enum_json(), value, orange(result) );
  
  t << equal<expect>(result, std::string("[\"value1\",\"value3\"]") ) << result <<  FAS_TESTING_FILE_LINE;

  result.clear();
  value = 0;
  ade(t, enum_json(), value, orange(result) );
  t << equal<expect>(result, std::string("[]") ) << result << FAS_TESTING_FILE_LINE;

  result.clear();
  value = value1 | value2 | value3;
  ade(t, enum_json(), value, orange(result) );
  t << equal<expect>(result, std::string("[\"value1\",\"value2\",\"value3\"]") ) << result << FAS_TESTING_FILE_LINE;

}

BEGIN_SUITE(array_serializer_suite, "array serializer suite")
  ADD_UNIT(array_serialize_test)
  ADD_UNIT(ad_array_test1)
  ADD_UNIT(ad_array_test2)
  ADD_UNIT(ad_array_test3)
  ADD_UNIT(ad_array_test4)
  ADD_UNIT(ad_array_test5)
  ADD_UNIT(ad_enumset_test)
  ADD_ADVICE( ::fas::json::ser::_string_, ::fas::json::ser::ad_string)
  ADD_ADVICE( ::fas::json::ser::_integer_, ::fas::json::ser::ad_integer)
  ADD_ADVICE( ::fas::json::ser::_sequence_, ::fas::json::ser::ad_sequence)
  ADD_ADVICE( ::fas::json::ser::_array_, ::fas::json::ser::ad_array)
  //ADD_ADVICE( ::fas::json::ser::_member_list_, ::fas::json::ser::ad_member_list)
  ADD_ADVICE( ::fas::json::ser::_enumset_value_, ::fas::json::ser::ad_enumset_value)
  ADD_ADVICE( ::fas::json::ser::_attr_, ::fas::json::ser::ad_attr)
  ADD_ADVICE( ::fas::json::ser::_brute_list_, ::fas::json::ser::ad_brute_list)
  ADD_ADVICE( ::fas::json::ser::_primary_list_, ::fas::json::ser::ad_primary_list)
  ADD_ADVICE( ::fas::json::ser::_brute_pair_, ::fas::json::ser::ad_brute_pair)
  ADD_ADVICE( ::fas::json::ser::_stub_, ::fas::json::ser::ad_stub)
  ADD_ADVICE( ::fas::json::ser::_null_, ::fas::json::ser::ad_null)
  ADD_ADVICE( ::fas::json::ser::_cstring_, ::fas::json::ser::ad_cstring)
  ADD_ADVICE( ::fas::json::_except_, ::fas::json::ad_except)
END_SUITE(array_serializer_suite)
