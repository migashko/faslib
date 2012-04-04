#include <fas/testing.hpp>

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/serializer.hpp>
#include <fas/serialization/json/meta.hpp>

#include <fas/range/range.hpp>
#include <fas/range/orange.hpp>

#include "../../bar.hpp"
#include "../../names.hpp"

namespace aj = ::fas::json;
typedef aj::object<
  aj::brute_pair<
    fas::type_list_n<
      aj::member< n_foo1, aj::attr<foo, int, &foo::foo1, aj::integer> >,
      aj::member< n_foo2, aj::attr<foo, std::string, &foo::foo2, aj::string> >,
      aj::member< n_foo3, aj::attr<foo, foo::foo3type, &foo::foo3, aj::string> >,
      aj::member< n_foo5, aj::attr<foo, foo::foo5type, &foo::foo5, aj::array<aj::integer> > >,
      aj::member< n_foo4, aj::attr<foo, std::vector<int>, &foo::foo4, aj::array<aj::integer> >  >,
      aj::member< n_foo6, aj::attr<foo, std::vector<std::string>, &foo::foo6, aj::array<aj::string> >  >
    >::type
    ,
    fas::type_list_n<
    >::type
    >
  > foo_json1;

UNIT(serializer_test, "test deserializer")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;
  
  serializer<> ser;


  foo f;
  std::string result;
  std::string json = 
      "{\"foo1\":-1,\"foo2\":\"test-foo2\",\"foo3\":\"test-foo3\","
      "\"foo5\":[0,1,2,3,4],\"foo4\":[20,30,40],\"foo6\":[\"test-foo6-1\",\"test-foo6-2\"]}";

  ser( foo_json1(), f, orange(result) );
  
  t << equal<expect>(result, json) << FAS_TESTING_FILE_LINE;
  
  t << message(result);
  t << message(json);
  
  std::cout << "sizeof = " << sizeof(serializer<>::aspect) << std::endl;
  std::cout << "sizeof = " << sizeof(serializer<>::aspect_type) << std::endl;

}

typedef aj::object<
    aj::block<
    aj::brute_pair<
    fas::type_list_n<
      aj::block< aj::member< n_foo1, aj::block< aj::attr<foo, int, &foo::foo1, aj::integer> > > >,
      aj::block< aj::member< n_foo2, aj::attr<foo, std::string, &foo::foo2, aj::string> > >,
      aj::block< aj::member< n_foo3, aj::attr<foo, foo::foo3type, &foo::foo3, aj::string> > >,
      aj::block< aj::member< n_foo5, aj::attr<foo, foo::foo5type, &foo::foo5, aj::array< aj::integer> > > >,
      aj::block< aj::member< n_foo4, aj::attr<foo, std::vector<int>, &foo::foo4, aj::block< aj::array< aj::block< aj::sequence< aj::block<aj::integer> > > > > > > >,
      aj::block<
        aj::member<
          n_foo6, 
          aj::attr<
            foo, 
            std::vector<std::string>, 
            &foo::foo6, 
            aj::array<
              fas::type_list_n<
                aj::block< aj::sequence< aj::block< aj::string> > >
              >::type
            > 
          > 
        >
      >
    >::type
    ,
    fas::type_list_n<
    >::type
    >
    >
  > foo_json2;


UNIT(serializer_block_test, "test deserializer")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;
  
  serializer<> ser;
  
  //typedef block< ::fas::json::stub > st;

  
  foo f;
  std::string result;
  std::string json = 
      "{\"foo1\":-1,\"foo2\":\"test-foo2\",\"foo3\":\"test-foo3\","
      "\"foo5\":[0,1,2,3,4],\"foo4\":[20,30,40],\"foo6\":[\"test-foo6-1\",\"test-foo6-2\"]}";

  ser( foo_json2(), f, orange(result) );
  
  // t << equal<expect>(result, json) << FAS_TESTING_FILE_LINE << result;
  
  t << message("") << std::endl << result;
  t << message(json);
}

BEGIN_SUITE(serializer_suite, "serializer suite")
  ADD_UNIT(serializer_test)
  ADD_UNIT(serializer_block_test)
END_SUITE(serializer_suite)
