#ifndef FAS_JSONRPC_METHOD_METHOD_ASPECT_TYPE_HPP
#define FAS_JSONRPC_METHOD_METHOD_ASPECT_TYPE_HPP


#include <fas/jsonrpc/method/ad_request_stub.hpp>
#include <fas/jsonrpc/method/ad_notify_stub.hpp>

#include <fas/jsonrpc/method/ad_notify_handler.hpp>
#include <fas/jsonrpc/method/ad_request_handler.hpp>
#include <fas/jsonrpc/method/ad_parse_notify.hpp>
#include <fas/jsonrpc/method/ad_parse_request_stub.hpp>
#include <fas/jsonrpc/method/ad_send_result.hpp>

#include <fas/jsonrpc/method/ad_invalid_request_method.hpp>
#include <fas/jsonrpc/method/ad_invalid_id_method.hpp>
#include <fas/jsonrpc/method/ad_request_error.hpp>
#include <fas/jsonrpc/method/ad_send_request_error.hpp>
#include <fas/jsonrpc/method/ad_notify_error.hpp>
#include <fas/jsonrpc/method/tags.hpp>
#include <fas/jsonrpc/error/tags.hpp>

#include <fas/serialization/json/meta/null.hpp>

#include <fas/aop/aspect.hpp>
#include <fas/aop/stub.hpp>
#include <fas/aop/definition.hpp>
#include <fas/aop/advice.hpp>

#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace jsonrpc{ 
  
typedef type_list_n<
  //advice< _parse_request_, ad_parse_request_stub >,
  advice< _invalid_id_, ad_invalid_id_method >,
  advice< _invalid_request_, ad_invalid_request_method >,
  advice< _request_error_, ad_request_error >,
  advice< _send_request_error_, ad_send_request_error >,
  advice< _notify_error_, ad_notify_error >,
  advice< _send_notify_error_, ad_send_request_error >,
  stub<_context_>
>::type method_advice_list;

typedef ::fas::aspect< method_advice_list > method_aspect_type;

}}

#endif

