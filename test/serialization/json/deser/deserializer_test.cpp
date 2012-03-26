#include <fas/testing.hpp>

#include <fas/serialization/json/deser/tags.hpp>
#include <fas/serialization/json/deserializer.hpp>
#include <fas/serialization/json/meta.hpp>

#include "../../bar.hpp"
#include "../../names.hpp"

UNIT(deserializer_test, "test deserializer")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;
  
  deserializer<> deser;

  typedef object<
    brute_pair<
    type_list_n<
      member< n_foo1, attr<foo, int, &foo::foo1, integer> >,
      member< n_foo2, attr<foo, std::string, &foo::foo2, string> >,
      member< n_foo3, attr<foo, foo::foo3type, &foo::foo3, string> >,
      member< n_foo5, attr<foo, foo::foo5type, &foo::foo5, array<integer> > >,
      member< n_foo4, attr<foo, std::vector<int>, &foo::foo4, array<integer> >  >,
      member< n_foo6, attr<foo, std::vector<std::string>, &foo::foo6, array<string> >  >
    >::type
    ,
    type_list_n<
    >::type
    >
  > foo_json;

  foo f(0);
  const char json[] = 
      "{\"foo1\":-1,\"foo2\":\"test-foo2\",\"foo3\":\"test-foo3\","
      "\"foo5\":[6,5,4,3,2],\"foo4\":[20,30,40],\"foo6\":[\"test-foo6-1\",\"test-foo6-2\"]}";

  deser( foo_json(), f, fas::range(json) );
  
  
  std::cout << "sizeof = " << sizeof(deser) << std::endl;
  std::cout << "sizeof = " << sizeof(deserializer<>) << std::endl;
  std::cout << "sizeof = " << sizeof(deserializer<>::aspect) << std::endl;
  std::cout << "sizeof = " << sizeof(deserializer<>::aspect_type) << std::endl;
}


BEGIN_SUITE(deserializer_suite, "deserializer suite")
  ADD_UNIT(deserializer_test)
END_SUITE(deserializer_suite)
