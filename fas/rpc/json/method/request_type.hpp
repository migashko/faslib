#ifndef FAS_RPC_JSON_METHOD_REQUEST_TYPE_HPP
#define FAS_RPC_JSON_METHOD_REQUEST_TYPE_HPP

#include <fas/aop/definition.hpp>
#include <fas/rpc/json/tags.hpp>

namespace fas{ namespace rpc{ namespace json{

template<typename V >
struct request_type
  : definition<_request_type_, V > 
{
};

}}}

#endif

