#ifndef FAS_JSONRPC_OUTGOING_AD_SEND_CUSTOM_ERROR_HPP
#define FAS_JSONRPC_OUTGOING_AD_SEND_CUSTOM_ERROR_HPP

#include <fas/jsonrpc/outgoing/json/common_error_notify_json.hpp>
#include <fas/jsonrpc/outgoing/json/common_error_message_json.hpp>
#include <fas/jsonrpc/outgoing/json/error_message_json.hpp>
#include <fas/jsonrpc/outgoing/json/error_notify_json.hpp>
#include <fas/jsonrpc/outgoing/json/custom_error_json.hpp>

#include <fas/jsonrpc/outgoing/types/common_error.hpp>
#include <fas/jsonrpc/outgoing/types/custom_error.hpp>
#include <fas/jsonrpc/outgoing/types/error_message_object.hpp>

#include <fas/jsonrpc/outgoing/tags.hpp>
#include <fas/jsonrpc/error_code.hpp>

namespace fas{ namespace jsonrpc{ 

struct ad_send_custom_error
{
  template<typename T, typename J, typename V>
  bool operator() (T& t, J, const V& error, int id)
  {
    typedef error_message_object<V> error_object;
    typedef error_message_json< error_object, V, J > error_json;
    
    return t.get_aspect().template get<_send_>()
    (
      t,
      error_json(),
      error_object( error, id)
    );
  }

  template<typename T, typename J, typename V>
  bool operator() (T& t, J, const V& error)
  {
    typedef error_notify_json< V, J > error_json;
    return t.get_aspect().template get<_send_>()(t, error_json(), error );
  }
};

}}

#endif
