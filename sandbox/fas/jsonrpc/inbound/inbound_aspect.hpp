#ifndef FAS_JSONRPC_INBOUND_INBOUND_ASPECT_HPP
#define FAS_JSONRPC_INBOUND_INBOUND_ASPECT_HPP

#include <fas/jsonrpc/inbound/ad_inbound.hpp>
#include <fas/jsonrpc/inbound/ad_parse_incoming.hpp>

#include <fas/jsonrpc/inbound/ad_parse_array.hpp>
#include <fas/jsonrpc/inbound/ad_parse_object.hpp>
#include <fas/jsonrpc/inbound/ad_process_object.hpp>

#include <fas/jsonrpc/inbound/types/deserializer.hpp>
#include <fas/jsonrpc/inbound/types/parser.hpp>

#include <fas/jsonrpc/inbound/error/inbound_error_aspect.hpp>
#include <fas/jsonrpc/inbound/tags.hpp>



#include <fas/aop/aspect.hpp>
#include <fas/aop/advice.hpp>
#include <fas/aop/type_advice.hpp>
#include <fas/type_list/type_list_n.hpp>


namespace fas{ namespace jsonrpc{ 

struct inbound_list: type_list_n<
  advice< _inbound_, ad_inbound >,
  advice< _parse_incoming_, ad_parse_incoming >,
  advice< _parse_object_, ad_parse_object >,
  advice< _parse_array_, ad_parse_array >,
  advice< _process_object_, ad_process_object >,
  type_advice< _deserializer_, inbound_deserializer >,
  type_advice< _parser_, inbound_parser >,
  inbound_error_aspect
>::type {};

struct inbound_aspect: 
  ::fas::aspect<inbound_list> 
{
};
  
}}

#endif
