#ifndef FAS_JSONRPC_INBOUND_ERROR_INBOUND_ERROR_ASPECT_HPP
#define FAS_JSONRPC_INBOUND_ERROR_INBOUND_ERROR_ASPECT_HPP

#include <fas/jsonrpc/inbound/error/tags.hpp>
#include <fas/jsonrpc/inbound/error/ad_parse_error.hpp>
#include <fas/jsonrpc/inbound/error/ad_invalid_request.hpp>

#include <fas/aop/aspect.hpp>
#include <fas/aop/advice.hpp>
#include <fas/type_list/type_list_n.hpp>


namespace fas{ namespace jsonrpc{ 

struct inbound_error_list: type_list_n<
  advice< _parse_error_, ad_parse_error >,
  advice< _invalid_request_, ad_invalid_request>
>::type {};

struct inbound_error_aspect: 
  ::fas::aspect<inbound_error_list> 
{
};
  
}}

#endif
