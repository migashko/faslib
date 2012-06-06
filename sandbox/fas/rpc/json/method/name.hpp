#ifndef FAS_RPC_JSON_METHOD_NAME_HPP
#define FAS_RPC_JSON_METHOD_NAME_HPP

#include <fas/rpc/json/tags.hpp>
#include <fas/rpc/json/method/ad_name.hpp>

namespace fas{ namespace rpc{ namespace json{ 

template<typename N>
struct name
  : advice<_name_, ad_name<N> > 
{
};
  
}}}

#endif
