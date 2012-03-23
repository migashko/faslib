#ifndef FAS_RPC_JSON_METHOD_NOTIFY_HPP
#define FAS_RPC_JSON_METHOD_NOTIFY_HPP

#include <fas/rpc/json/tags.hpp>
#include <fas/aop/advice.hpp>


namespace fas{ namespace rpc{ namespace json{

template<typename H>
struct notify
  : advice<_notify_, H >
{
  
};
  
}}}

#endif
