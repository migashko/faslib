#ifndef FAS_JSONRPC_METHOD_METHOD_ASPECT_TYPE_HPP
#define FAS_JSONRPC_METHOD_METHOD_ASPECT_TYPE_HPP


#include <fas/jsonrpc/method/ad_request_stub.hpp>
#include <fas/jsonrpc/method/ad_notify_stub.hpp>

#include <fas/jsonrpc/method/ad_notify_handler.hpp>
#include <fas/jsonrpc/method/ad_request_handler.hpp>
#include <fas/jsonrpc/method/ad_parse_notify.hpp>
#include <fas/jsonrpc/method/ad_parse_request.hpp>
#include <fas/jsonrpc/method/ad_send_result.hpp>
#include <fas/jsonrpc/tags.hpp>

#include <fas/serialization/json/meta/null.hpp>

#include <fas/aop/aspect.hpp>
#include <fas/aop/stub.hpp>
#include <fas/aop/definition.hpp>
#include <fas/aop/advice.hpp>

#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace jsonrpc{ 
  
typedef type_list_n<
  advice< _notify_, ad_notify_stub >,
  definition<_notify_value_, empty_type>,
  definition<_notify_json_, ::fas::json::null>,

  advice< _request_, ad_request_stub >,
  definition<_request_value_, empty_type>,
  definition<_request_json_, ::fas::json::null>,
  definition<_result_value_, empty_type>,
  definition<_result_json_, ::fas::json::null>,

  stub<_context_>,
  
  advice< _notify_handler_, ad_notify_handler >,
  advice< _request_handler_, ad_request_handler >,
  
  advice< _parse_notify_, ad_parse_notify >,
  advice< _parse_request_, ad_parse_request >,
  advice< _send_result_, ad_send_result >
>::type method_advice_list;

typedef ::fas::aspect< method_advice_list > method_aspect_type;

}}

#endif

