#ifndef FAS_JSONRPC_METHOD_REQUEST_AD_REQUEST_ERROR_HPP
#define FAS_JSONRPC_METHOD_REQUEST_AD_REQUEST_ERROR_HPP

#include <fas/jsonrpc/outgoing/tags.hpp>
#include <fas/jsonrpc/method/tags.hpp>
#include <fas/jsonrpc/method/error/tags.hpp>

#include <fas/jsonrpc/outgoing/types/custom_error.hpp>
#include <fas/jsonrpc/outgoing/json/custom_error_json.hpp>
#include <fas/jsonrpc/outgoing/types/error_message_object.hpp>
#include <fas/jsonrpc/outgoing/json/error_message_json.hpp>
#include <fas/jsonrpc/outgoing/json/error_notify_json.hpp>

namespace fas{ namespace jsonrpc{

template<
  typename V = custom_error,
  typename J = custom_error_json
>
struct ad_request_error
{
  template<typename T, typename M>
  void operator()(T& t, M& method, const V& user_error, int id)
  {
    /*
    typedef error_message_object<V> error_value;
    typedef error_message_json< error_value, V, J> error_json;
      */

    this->_send(t, method, J(), user_error, id );
    /*
    register bool send_ready = method.get_aspect().template get<_request_id_>().has(id);

    if ( send_ready )
    {
      method.get_aspect().template get<_request_id_>().pop(id);
      send_ready = t.get_aspect().template get<_send_>()( t, error_json(), error_value(user_error, id) );
    }

    if ( !send_ready )
      method.get_aspect().template get<_send_error_fail_>()( t, method, user_error, id );
    */
  }

  template<typename T, typename M>
  void operator()(T& t, M& method, error_code::type code, int id)
  {
    
    this->_send(t, method, common_error_code_json(), code, id );
    /*
    register bool send_ready = method.get_aspect().template get<_request_id_>().has(id);

    if ( send_ready )
    {
      method.get_aspect().template get<_request_id_>().pop(id);
      send_ready = t.get_aspect().template get<_send_error_>()( t, code, id );
    }

    if ( !send_ready )
      method.get_aspect().template get<_send_error_fail_>()( t, method, custom_error(code), id );*/
  }

  template<typename T, typename M>
  void operator()(T& t, M& method, int code, const std::string& message, int id)
  {
    this->_send( t, method, custom_error_json(), custom_error(code, message) );
    /*
    register bool send_ready = method.get_aspect().template get<_request_id_>().has(id);

    if ( send_ready )
    {
      method.get_aspect().template get<_request_id_>().pop(id);
      send_ready = t.get_aspect().template get<_send_error_>()( t, code, message, id );
    }

    if ( !send_ready )
      method.get_aspect().template get<_send_error_fail_>()( t, method, custom_error(code, message), id );
    */
  }


private:
  template<typename T, typename M, typename JJ, typename VV>
  bool _send(T& t, M& method, JJ, const VV& value, int id)
  {
    if ( method.get_aspect().template get<_request_id_>().has(id) )
    {
      method.get_aspect().template get<_request_id_>().pop(id);
      if ( t.get_aspect().template get<_send_error_>()( t, JJ(), value, id ) )
        return true;
      method.get_aspect().template get<_send_error_fail_>()( t, method, value.error, id );
    }
    else
      method.get_aspect().template get< _invalid_error_id_ >()( t, method, value.error, id );
    return false;
  }

  
/// Только в ручную (не через method::error)
/*
  template<typename T, typename M>
  void operator()(T& t, M& method, const V& result)
  {
    typedef V error_value;
    typedef error_notify_json< error_value, J> error_json;

    if ( !t.get_aspect().template get<_send_>()( t, error_json(), result ) )
      method.get_aspect().template get<_send_error_fail_>()( t, method, result );
  }
  */
  
};


}}

#endif
