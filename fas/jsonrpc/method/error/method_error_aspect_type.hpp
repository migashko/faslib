#ifndef FAS_JSONRPC_METHOD_METHOD_ERROR_ASPECT_TYPE_HPP
#define FAS_JSONRPC_METHOD_METHOD_ERROR_ASPECT_TYPE_HPP

//#include <fas/jsonrpc/method/error/ad_invalid_id_method.hpp>
#include <fas/jsonrpc/method/error/ad_invalid_request_method.hpp>
//#include <fas/jsonrpc/method/error/ad_notify_except.hpp>
//#include <fas/jsonrpc/method/error/ad_request_except.hpp>
#include <fas/jsonrpc/method/error/ad_send_notify_fail.hpp>
#include <fas/jsonrpc/method/error/ad_send_request_fail.hpp>
//#include <fas/jsonrpc/method/error/ad_send_result_fail.hpp>
#include <fas/jsonrpc/method/error/ad_send_error_fail.hpp>

#include <fas/jsonrpc/method/error/tags.hpp>
#include <fas/jsonrpc/error/tags.hpp>

#include <fas/aop/aspect.hpp>
#include <fas/aop/advice.hpp>

#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace jsonrpc{ 
  
typedef type_list_n<

  //advice< _invalid_id_, ad_invalid_id_method >,
  advice< _invalid_request_, ad_invalid_request_method >,

  //advice< _notify_except_, ad_notify_except >,
  //advice< _request_except_, ad_request_except >,
  advice< _send_notify_fail_, ad_send_notify_fail >,
  advice< _send_request_fail_, ad_send_request_fail >,
  //advice< _send_result_fail_, ad_send_result_fail >,
  advice< _send_error_fail_, ad_send_error_fail >

>::type method_error_advice_list;

typedef ::fas::aspect< method_error_advice_list > method_error_aspect_type;

}}

#endif

