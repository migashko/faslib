#ifndef FAS_JSONRPC_METHOD_REQUEST_ERROR_AD_ERROR_HPP
#define FAS_JSONRPC_METHOD_REQUEST_ERROR_AD_ERROR_HPP

#include <fas/jsonrpc/outgoing/tags.hpp>
#include <fas/jsonrpc/method/tags.hpp>
//#include <fas/jsonrpc/method/error/tags.hpp>

#include <fas/jsonrpc/outgoing/types/custom_error.hpp>
#include <fas/jsonrpc/outgoing/json/custom_error_json.hpp>
#include <fas/jsonrpc/outgoing/types/error_message_object.hpp>
#include <fas/jsonrpc/outgoing/json/error_message_json.hpp>
#include <fas/jsonrpc/outgoing/json/error_notify_json.hpp>

namespace fas{ namespace jsonrpc{ namespace local{

template<
  typename V = custom_error,
  typename J = custom_error_json
>
struct ad_error
{
  template<typename T, typename M>
  bool operator()(T& t, M& method, const V& user_error, int id)
  {
    return this->_send(t, method, J(), user_error, id );
  }

  template<typename T, typename M>
  bool operator()(T& t, M& method, int code, const std::string& message, int id)
  {
    return this->_send( t, method, custom_error_json(), custom_error(code, message), id );
  }

  template<typename T, typename M>
  bool operator()(T& t, M& method, error_code::type code, int id)
  {
    if ( method.get_aspect().template get<_id_>().has(id) )
    {
      method.get_aspect().template get<_id_>().pop(id);
      if ( t.get_aspect().template get<_send_common_error_>()( t, code, id ) )
        return true;
      method.get_aspect().template get<_error_fail_>()( t, method, code, id );
    }
    else
      method.get_aspect().template get< _invalid_error_id_ >()( t, method, code, id );
    return false;
  }

private:
  
  template<typename T, typename M, typename JJ, typename VV>
  bool _send(T& t, M& method, JJ, const VV& value, int id)
  {
    if ( method.get_aspect().template get<_id_>().has(id) )
    {
      method.get_aspect().template get<_id_>().pop(id);
      
      if ( t.get_aspect().template get<_send_custom_error_>()( t, JJ(), value, id ) )
        return true;
      
      method.get_aspect().template get<_error_fail_>()( t, method, value, id );
    }
    else
      method.get_aspect().template get< _invalid_error_id_ >()( t, method, value, id );
    
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


}}}

#endif
