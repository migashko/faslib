#ifndef FAS_JSONRPC_METHOD_REMOTE_NOTIFY_HPP
#define FAS_JSONRPC_METHOD_REMOTE_NOTIFY_HPP


#include <fas/jsonrpc/method/remote/notify/tags.hpp>
#include <fas/jsonrpc/method/remote/notify/ad_notify.hpp>
#include <fas/jsonrpc/method/remote/notify/ad_notify_fail.hpp>


#include <fas/serialization/json/meta/null.hpp>

#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/type_list/type_list_n.hpp>


namespace fas{ namespace jsonrpc{ namespace remote{
  
template<
  typename V = const void*,
  typename J = ::fas::json::null
>
struct notify: ::fas::aspect< 
  typename type_list_n<
    advice< _notify_, ad_notify< V, J  > >,
    advice< _notify_fail_, ad_notify_fail >
  >::type >
{};
  
}}}

#endif
