#include <fas/testing.hpp>
#include <fas/typemanip/tstring.hpp>
#include <fas/type_list/type_list_n.hpp>
#include <fas/serialization/json/deser/ad_enumeration.hpp>
#include <fas/serialization/json/deser/ad_string.hpp>
#include <fas/serialization/json/meta/enumeration.hpp>
#include <fas/serialization/json/meta/enum_value.hpp>

#include <fas/serialization/json/parser/aspect.hpp>

#include <fas/range/range.hpp>
#include <string>

FAS_NAME(value1);
FAS_NAME(value12);
FAS_NAME(value2);

typedef enum { value1 = 31, value12, value2} test_enum;


UNIT(ad_enumeration_test, "test fas::serialization::json::deser::ad_enumeration advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;
  

  typedef enumeration<
    typename type_list_n<
      enum_value<n_value1, value1>,
      enum_value<n_value2, value2>
    >::type
  > enum_json;

  std::string value="\"value1\"";
  test_enum result = value2;
  ad_enumeration ade;
  ade(t, enum_json(), result, range(value) );
  
  t << message("") << result;
  t << equal<expect>(result, value1 ) << FAS_TESTING_FILE_LINE;
  

  value="\"value2\"";
  result = value1;
  ade(t, enum_json(), result, range(value) );
  t << equal<expect>(result, value2 ) << FAS_TESTING_FILE_LINE;
  
  int intres = 42;
  ade(t, enum_json(), intres, range(value) );
  t << equal<expect>(intres, value2 ) << FAS_TESTING_FILE_LINE;
}

UNIT(ad_enumeration_test0, "test fas::serialization::json::deser::ad_enumeration advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;
  

  
  typedef enumeration<
    typename type_list_n<
    >::type
  > enum_json;

  std::string value="\"value1\"";
  test_enum result = value2;
  ad_enumeration ade;
  ade(t, enum_json(), result, range(value) );
  
  t << message("") << result;
  t << equal<expect>(result, test_enum() ) << FAS_TESTING_FILE_LINE;
  

  value="\"value2\"";
  result = value1;
  ade(t, enum_json(), result, range(value) );
  t << equal<expect>(result, test_enum() ) << FAS_TESTING_FILE_LINE;
  
  int intres = 42;
  ade(t, enum_json(), intres, range(value) );
  t << equal<expect>(intres, test_enum() ) << FAS_TESTING_FILE_LINE;

  
}


UNIT(ad_enumeration_test1, "test fas::serialization::json::deser::ad_enumeration advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;
  
  typedef enumeration<
    typename type_list_n<
      enum_value<n_value12, value12>,
      enum_value<n_value1, value1>,
      enum_value<n_value2, value2>
    >::type
  > enum_json;

  std::string value="\"value1\"";
  test_enum result = value2;
  ad_enumeration ade;
  ade(t, enum_json(), result, range(value) );
  
  t << message("") << result;
  t << equal<expect>(result, value1 ) << FAS_TESTING_FILE_LINE;
  

  value="\"value2\"";
  result = value1;
  ade(t, enum_json(), result, range(value) );
  t << equal<expect>(result, value2 ) << FAS_TESTING_FILE_LINE;
  
  int intres = 42;
  ade(t, enum_json(), intres, range(value) );
  t << equal<expect>(intres, value2 ) << FAS_TESTING_FILE_LINE;
}

BEGIN_SUITE(enumeration_deserialize_suite, "enumeration deserialize suite")
  ADD_UNIT(ad_enumeration_test)
  ADD_UNIT(ad_enumeration_test0)
  ADD_UNIT(ad_enumeration_test1)
  ADD_ASPECT(::fas::json::parser::aspect)
  ADD_ADVICE(::fas::json::deser::_enum_value_, ::fas::json::deser::ad_enum_value)
  ADD_ADVICE(::fas::json::deser::_cstring_, ::fas::json::deser::ad_cstring)
END_SUITE(enumeration_deserialize_suite)
