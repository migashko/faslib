#ifndef FAS_JSONRPC_METHOD_NAME_HPP
#define FAS_JSONRPC_METHOD_NAME_HPP

// #include <fas/jsonrpc/tags.hpp>
#include <fas/jsonrpc/method/ad_name.hpp>
#include <fas/jsonrpc/method/tags.hpp>
#include <fas/aop/advice.hpp>

namespace fas{ namespace jsonrpc{ 

template<typename N>
struct name
  : advice<_name_, ad_name<N> >
{
};
  
}}

#endif
