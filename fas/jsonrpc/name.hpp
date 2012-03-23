#ifndef FAS_JSONRPC_NAME_HPP
#define FAS_JSONRPC_NAME_HPP

#include <fas/jsonrpc/tags.hpp>
#include <fas/jsonrpc/ad_name.hpp>

namespace fas{ namespace jsonrpc{ 

template<typename N>
struct name
  : advice<_name_, ad_name<N> > 
{
};
  
}}

#endif
