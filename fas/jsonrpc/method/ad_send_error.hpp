#ifndef FAS_JSONRPC_METHOD_AD_SEND_ERROR_HPP
#define FAS_JSONRPC_METHOD_AD_SEND_ERROR_HPP

#include <fas/jsonrpc/outgoing/tags.hpp>
#include <fas/jsonrpc/method/tags.hpp>
#include <fas/jsonrpc/method/error/tags.hpp>

#include <fas/jsonrpc/error/json/custom_error.hpp>
#include <fas/jsonrpc/error/json/custom_error_json.hpp>
#include <fas/jsonrpc/error/json/error_object.hpp>
#include <fas/jsonrpc/error/json/error_object_json.hpp>

namespace fas{ namespace jsonrpc{

template<
  typename V = custom_error,
  typename J = custom_error_json
>
struct ad_send_method_error
{
  template<typename T, typename M>
  void operator()(T& t, M& method, const V& user_error, int id)
  {
    typedef custom_error_object<V> error_value;
    typedef custom_error_message_json< error_value, V, J> error_json;

    register bool send_ready = method.get_aspect().template get<_method_id_>().has(id);

    if ( send_ready )
    {
      method.get_aspect().template get<_method_id_>().pop(id);
      send_ready = t.get_aspect().template get<_send_>()( t, error_json(), error_value(user_error, id) );
    }

    if ( !send_ready )
      method.get_aspect().template get<_send_error_fail_>()( t, method, user_error, id );
  }

  template<typename T, typename M>
  void operator()(T& t, M& method, error_code::type code, int id)
  {
    register bool send_ready = method.get_aspect().template get<_method_id_>().has(id);

    if ( send_ready )
    {
      method.get_aspect().template get<_method_id_>().pop(id);
      send_ready = t.get_aspect().template get<_send_error_>()( t, code, id );
    }

    if ( !send_ready )
      method.get_aspect().template get<_send_error_fail_>()( t, method, custom_error(code), id );
  }

  template<typename T, typename M>
  void operator()(T& t, M& method, int code, const std::string& message, int id)
  {
    register bool send_ready = method.get_aspect().template get<_method_id_>().has(id);

    if ( send_ready )
    {
      method.get_aspect().template get<_method_id_>().pop(id);
      send_ready = t.get_aspect().template get<_send_error_>()( t, code, message, id );
    }

    if ( !send_ready )
      method.get_aspect().template get<_send_error_fail_>()( t, method, custom_error(code, message), id );
  }

/// Только в ручную (не через method::error)
  template<typename T, typename M>
  void operator()(T& t, M& method, const V& result)
  {
    typedef V error_value;
    typedef custom_error_notify_json< error_value, J> error_json;

    if ( !t.get_aspect().template get<_send_>()( t, error_json(), result ) )
      method.get_aspect().template get<_send_error_fail_>()( t, method, result );
  }
  
};


}}

#endif
