#ifndef FAS_RPC_JSON_METHOD_ASPECT_HPP
#define FAS_RPC_JSON_METHOD_ASPECT_HPP

#include <fas/rpc/json/tags.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/alias.hpp>
#include <fas/type_list/type_list_n.hpp>

#include <fas/rpc/json/method/ad_ids.hpp>
#include <fas/rpc/json/method/ids.hpp>

#include <fas/rpc/json/method/name.hpp>
#include <fas/rpc/json/method/request.hpp>
#include <fas/rpc/json/method/request_type.hpp>
#include <fas/rpc/json/method/request_json.hpp>

#include <fas/rpc/json/method/notify.hpp>
#include <fas/rpc/json/method/notify_type.hpp>
#include <fas/rpc/json/method/notify_json.hpp>

#include <fas/rpc/json/method/ad_invoke_request_notimpl.hpp>
#include <fas/rpc/json/method/ad_invoke_notify_notimpl.hpp>
#include <fas/rpc/json/method/ad_invoke_result_notimpl.hpp>
#include <fas/rpc/json/method/ad_invoke_error_notimpl.hpp>

#include <fas/rpc/json/method/ad_invalid_id.hpp>
#include <fas/rpc/json/method/ad_invalid_request.hpp>
#include <fas/rpc/json/method/ad_not_impl.hpp>
#include <fas/rpc/json/method/ad_switch_deserialize.hpp>
#include <fas/rpc/json/method/ad_parse_error.hpp>

namespace fas{ namespace rpc{ namespace json{ 

//struct _switch_deserialize_;
//struct _deserialize_params_;

typedef type_list_n<
  stub<_error_>,
  advice< _ids_, ad_no_ids >,
  advice< _call_ids_, ad_no_ids >,
  advice< _invalid_id_, ad_invalid_id>,
  advice< _not_impl_, ad_not_impl>,
  advice< _invoke_request_handler_, ad_invoke_request_notimpl>,
  advice< _invoke_notify_handler_,  ad_invoke_notify_notimpl>,
  advice< _invoke_result_handler_,  ad_invoke_result_notimpl>,
  advice< _invoke_error_handler_,   ad_invoke_error_notimpl>,
   alias< _deserialize_params_, _switch_deserialize_ >,
  advice< _switch_deserialize_, ad_switch_deserialize >,
   alias< _deserialize_error_, _invalid_request_>,
  advice< _invalid_request_, ad_invalid_request>,
  advice< _parse_error_, ad_parse_error>
>::type method_advice_list;

typedef aspect< method_advice_list > method_aspect_type;

struct method_aspect: method_aspect_type { };
  
}}}

#endif
