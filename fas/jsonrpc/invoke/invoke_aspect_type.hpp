#ifndef FAS_JSONRPC_INVOKE_INVOKE_ASPECT_TYPE_HPP
#define FAS_JSONRPC_INVOKE_INVOKE_ASPECT_TYPE_HPP

#include <fas/jsonrpc/invoke/ad_parse_incoming.hpp>
#include <fas/jsonrpc/invoke/ad_process_incoming.hpp>
#include <fas/jsonrpc/invoke/ad_parse_object.hpp>
#include <fas/jsonrpc/invoke/ad_parse_array.hpp>
#include <fas/jsonrpc/invoke/ad_process_object.hpp>

#include <fas/jsonrpc/invoke/ad_foreach_notify.hpp>
#include <fas/jsonrpc/invoke/ad_foreach_request.hpp>

#include <fas/aop/aspect.hpp>
#include <fas/aop/advice.hpp>
#include <fas/type_list/type_list_n.hpp>

#include <fas/jsonrpc/invoke/tags.hpp>

namespace fas{ namespace jsonrpc{

typedef type_list_n<
  advice<_parse_incoming_, ad_parse_incoming >,
  advice<_process_incoming_, ad_process_incoming >,
  advice<_parse_object_, ad_parse_object >,
  advice<_parse_array_, ad_parse_array >,
  advice<_process_object_, ad_process_object >,
  advice<_foreach_notify_, ad_foreach_notify >,
  advice<_foreach_request_, ad_foreach_request >
>::type invoke_advice_list;

typedef ::fas::aspect< invoke_advice_list > invoke_aspect_type;

}}

#endif
