#ifndef FAS_JSONRPC_ERROR_ERROR_ASPECT_TYPE_HPP
#define FAS_JSONRPC_ERROR_ERROR_ASPECT_TYPE_HPP

#include <fas/jsonrpc/error/ad_invalid_request.hpp>
#include <fas/jsonrpc/error/ad_method_not_found.hpp>
#include <fas/jsonrpc/error/ad_not_impl.hpp>
#include <fas/jsonrpc/error/ad_parsing_error.hpp>
#include <fas/jsonrpc/error/ad_send_error.hpp>

#include <fas/jsonrpc/error/tags.hpp>

#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>

#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace jsonrpc{
  
typedef type_list_n<
  advice< _invalid_request_, ad_invalid_request >,
  advice< _method_not_found_, ad_method_not_found >,
  advice< _not_impl_, ad_not_impl >,
  advice< _parsing_error_, ad_parsing_error >,
  advice< _send_error_, ad_send_error >
>::type error_advice_list;

typedef aspect<error_advice_list> error_aspect_type;

}}

#endif
