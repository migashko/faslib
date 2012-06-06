#ifndef FAS_RPC_JSON_TEST_ASPECT_HPP
#define FAS_RPC_JSON_TEST_ASPECT_HPP

#include <fas/rpc/json/tags.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace rpc{ namespace json{ namespace test{

typedef type_list_n<
>::type advice_list;

typedef aspect<advice_list> aspect_type;

struct aspect: aspect_type { };
  
}}}}

#endif
