#ifndef FAS_JSONRPC_METHOD_REMOTE_NOTIFY_HPP
#define FAS_JSONRPC_METHOD_REMOTE_NOTIFY_HPP

#include <fas/jsonrpc/method/tags.hpp>
#include <fas/jsonrpc/json/notify_object_json.hpp>
#include <fas/jsonrpc/method/remote/ad_send_notify.hpp>

#include <fas/serialization/json/meta/null.hpp>
#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/definition.hpp>

namespace fas{ namespace jsonrpc{ 
  
template< typename V = const void*, typename J = ::fas::json::null >
struct remote_notify: type_list_n<
      advice< _send_notify_, ad_send_notify< V, J, notify_object_json > >
    >::type
{};

  
}}

#endif
