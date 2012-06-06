#include <iostream>
#include <fas/testing.hpp>
#include <fas/typemanip/tstring.hpp>
#include <fas/type_list/type_list_n.hpp>
#include <fas/serialization/json/ser/aspect.hpp>
#include <fas/serialization/json/serializer.hpp>
#include <fas/serialization/json/ser/ad_block.hpp>
#include <fas/serialization/json/ser/ad_comment.hpp>
#include <fas/serialization/json/meta.hpp>
#include <fas/serialization/json/meta/comment.hpp>
#include <fas/serialization/json/meta/block.hpp>

#include <fas/range/range.hpp>
#include <fas/range/orange.hpp>
#include <string>

//namespace test{ namespace formatting{
FAS_NAME(enum1);
FAS_NAME(enum2);

FAS_NAME(foo1);
FAS_NAME(foo2);
FAS_NAME(foo3);

FAS_STRING(str_enum1, "this is enum1" )
FAS_STRING(str_enum2, "this is enum2" )
FAS_STRING(str_foo1, "this is foo1" )
FAS_STRING(str_foo2, "this is foo2" )
FAS_STRING(str_foo3, "this is foo3" )

namespace {
struct foo
{
  typedef enum { enum1, enum2} foo_enum;
  typedef foo_enum foo_enum_array[3];
  
  int foo1;
  int foo2;
  
  foo_enum_array foo3;
  foo()
    : foo1(47)
    , foo2(12) 
  {
    foo3[0]=enum2;
    foo3[1]=enum1;
    foo3[2]=enum2;
  }
};
}
//}}

namespace aj = ::fas::json;

  typedef aj::object<
    fas::type_list_n<
      aj::comment< str_foo1, aj::field<n_foo1, aj::attr<foo, int, &foo::foo1, aj::integer> > >,
      aj::comment< str_foo2, aj::field<n_foo2, aj::attr<foo, int, &foo::foo2, aj::integer> > >,
      aj::comment< str_foo3, aj::field<n_foo3, aj::attr<foo, foo::foo_enum_array, &foo::foo3,
                          aj::array<
                          aj::enumeration<
                            fas::type_list_n<
                              aj::comment< fas::empty_type, aj::enum_value< n_enum1, foo::enum1>, str_enum1 >,
                              aj::comment< fas::empty_type, aj::enum_value< n_enum2, foo::enum2>, str_enum2 >
                            >::type
                          >
                          >
                         > 
                >
      >
    >::type
  > foo_json;

UNIT(ad_comment_test, "test fas::serialization::json::ser::ad_comment_test advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;
//  using namespace ::test::formatting;
  


  std::string result;
  
  serializer<> ser;
  
  foo f = foo();
  ser(foo_json(), f, orange(result) );
  std::cout<< result << std::endl;
  
  
  
  
  
  /*
  typedef enumeration<
    typename type_list_n<
      enum_value<n_value1, value1>,
      enum_value<n_value2, value2>
    >::type
  > enum_json;

  std::string result;
  ad_enumeration ade;
  test_enum value = value1;
  
  ade(t, enum_json(), value, (result) );
  
  t << equal<expect>(result, std::string("\"value1\"") ) << FAS_TESTING_FILE_LINE;
  
  
  result.clear();
  value = value2;
  ade(t, enum_json(), value, (result) );
  t << equal<expect>(result, std::string("\"value2\"") ) << FAS_TESTING_FILE_LINE;
  */
}

/*
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
  
  ade(t, enum_json(), value, (result) );
  
  t << equal<expect>(result, std::string("\"\"") ) << "[" << result << "]"<< FAS_TESTING_FILE_LINE;
  
  
  result.clear();
  value = value2;
  ade(t, enum_json(), value, (result) );
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
  
  ade(t, enum_json(), value, (result) );
  
  t << equal<expect>(result, std::string("\"\"") ) << "[" << result << "]"<< FAS_TESTING_FILE_LINE;
  
  
  result.clear();
  value = value2;
  ade(t, enum_json(), value, (result) );
  t << equal<expect>(result, std::string("\"value2\"") ) << FAS_TESTING_FILE_LINE;
}
*/

BEGIN_SUITE(formatting_serialize_suite, "formatting serialize suite")
  ADD_UNIT(ad_comment_test)
  ADD_ASPECT(::fas::json::ser::aspect)
  //ADD_ADVICE( ::fas::json::ser::_enum_value_, ::fas::json::ser::ad_enum_value)
  /*ADD_ADVICE(ad_enumeration)*/
END_SUITE(formatting_serialize_suite)

