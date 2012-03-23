#ifndef FAS_SERIALIZATION_JSON_RPC_METHOD_CALL_REQUEST_HPP
#define FAS_SERIALIZATION_JSON_RPC_METHOD_CALL_REQUEST_HPP

#include <fas/aop/advice.hpp>
#include <fas/serialization/json/rpc/method/tags.hpp>
namespace fas{ namespace json{ namespace rpc{ namespace method{

template<typename VJ /*=value_json*/ >
struct call_request
  : advice<_call_request_, VJ > 
{
};

}}}}

#endif
