#ifndef FAS_RPC_JSON_METHOD_RESPONSE_JSON_HPP
#define FAS_RPC_JSON_METHOD_RESPONSE_JSON_HPP

#include <fas/aop/definition.hpp>
#include <fas/rpc/json/tags.hpp>

namespace fas{ namespace rpc{ namespace json{

template<typename J  >
struct response_json
  : definition<_response_json_, J > 
{
};

}}}

#endif
