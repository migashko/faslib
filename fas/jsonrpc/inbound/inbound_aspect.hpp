#ifndef FAS_JSONRPC_INBOUND_INBOUND_ASPECT_HPP
#define FAS_JSONRPC_INBOUND_INBOUND_ASPECT_HPP

#include <fas/jsonrpc/inbound/error/inbound_error_aspect.hpp>
#include <fas/jsonrpc/inbound/tags.hpp>

#include <fas/aop/aspect.hpp>
#include <fas/aop/advice.hpp>
#include <fas/type_list/type_list_n.hpp>


namespace fas{ namespace jsonrpc{ 

struct inbound_list: type_list_n<
  inbound_error_aspect
>::type {};

struct inbound_aspect: 
  ::fas::aspect<inbound_list> 
{
};
  
}}

#endif
