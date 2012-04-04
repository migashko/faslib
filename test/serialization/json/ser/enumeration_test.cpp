#include <fas/testing.hpp>
#include <fas/typemanip/tstring.hpp>
#include <fas/type_list/type_list_n.hpp>
#include <fas/serialization/json/ser/ad_enumeration.hpp>
#include <fas/serialization/json/ser/ad_enum_value.hpp>
#include <fas/serialization/json/ser/ad_string.hpp>

#include <fas/serialization/json/except/ad_except.hpp>

#include <fas/serialization/json/meta/enumeration.hpp>
#include <fas/serialization/json/meta/enum_value.hpp>

#include <fas/range/range.hpp>
#include <fas/range/init_range.hpp>
#include <string>

FAS_NAME(value1);
FAS_NAME(value2);
FAS_NAME(value3);

typedef enum { value1 = 0x1, value2 = 0x2, value3 = 0x4 } test_enum;


UNIT(ad_enumeration_test, "test fas::serialization::json::ser::ad_boolean advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;
  

  typedef enumeration<
    typename type_list_n<
      enum_value<n_value1, value1>,
      enum_value<n_value2, value2>
    >::type
  > enum_json;

  std::string result;
  ad_enumeration ade;
  test_enum value = value1;
  
  ade(t, enum_json(), value, init_range(result) );
  
  t << equal<expect>(result, std::string("\"value1\"") ) << FAS_TESTING_FILE_LINE;
  
  
  result.clear();
  value = value2;
  ade(t, enum_json(), value, init_range(result) );
  t << equal<expect>(result, std::string("\"value2\"") ) << FAS_TESTING_FILE_LINE;
}

UNIT(ad_enumeration_test0, "test fas::serialization::json::ser::ad_boolean advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;
  

  typedef enumeration<
    typename type_list_n<
    >::type
  > enum_json;

  std::string result;
  ad_enumeration ade;
  test_enum value = value1;
  
  ade(t, enum_json(), value, init_range(result) );
  
  t << equal<expect>(result, std::string("\"\"") ) << "[" << result << "]"<< FAS_TESTING_FILE_LINE;
  
  
  result.clear();
  value = value2;
  ade(t, enum_json(), value, init_range(result) );
  t << equal<expect>(result, std::string("\"\"") ) << FAS_TESTING_FILE_LINE;
}


UNIT(ad_enumeration_test1, "test fas::serialization::json::ser::ad_boolean advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;
  

  typedef enumeration<
    typename type_list_n<
      enum_value<n_value2, value2>
    >::type
  > enum_json;

  std::string result;
  ad_enumeration ade;
  test_enum value = value1;
  //value = (test_enum)3;
  
  ade(t, enum_json(), value, init_range(result) );
  
  t << equal<expect>(result, std::string("\"\"") ) << "[" << result << "]"<< FAS_TESTING_FILE_LINE;
  
  
  result.clear();
  value = value2;
  ade(t, enum_json(), value, init_range(result) );
  t << equal<expect>(result, std::string("\"value2\"") ) << FAS_TESTING_FILE_LINE;
}


BEGIN_SUITE(enumeration_serialize_suite, "enumeration serialize suite")
  ADD_UNIT(ad_enumeration_test)
  ADD_UNIT(ad_enumeration_test0)
  ADD_UNIT(ad_enumeration_test1)
  ADD_ADVICE( ::fas::json::ser::_enum_value_, ::fas::json::ser::ad_enum_value)
  ADD_ADVICE( ::fas::json::ser::_cstring_, ::fas::json::ser::ad_cstring)
  ADD_ADVICE( ::fas::json::_except_, ::fas::json::ad_except)
END_SUITE(enumeration_serialize_suite)
