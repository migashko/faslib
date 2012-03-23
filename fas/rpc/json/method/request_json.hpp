#ifndef FAS_RPC_JSON_METHOD_REQUEST_JSON_HPP
#define FAS_RPC_JSON_METHOD_REQUEST_JSON_HPP

#include <fas/aop/definition.hpp>
#include <fas/rpc/json/tags.hpp>

namespace fas{ namespace rpc{ namespace json{

template<typename J  >
struct request_json
  : definition<_request_json_, J > 
{
};


}}}

#endif
