#ifndef FAS_JSONRPC_INBOUND_ERROR_INBOUND_ERROR_ASPECT_HPP
#define FAS_JSONRPC_INBOUND_ERROR_INBOUND_ERROR_ASPECT_HPP

#include <fas/jsonrpc/inbound/error/tags.hpp>

#include <fas/aop/aspect.hpp>
#include <fas/aop/advice.hpp>
#include <fas/type_list/type_list_n.hpp>


namespace fas{ namespace jsonrpc{ 

struct inbound_error_list: type_list_n<

>::type {};

struct inbound_error_aspect: 
  ::fas::aspect<inbound_error_list> 
{
};
  
}}

#endif
