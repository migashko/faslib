#ifndef FAS_JSONRPC_ERROR_AD_ERROR_HPP
#define FAS_JSONRPC_ERROR_AD_ERROR_HPP

#include <fas/jsonrpc/outgoing/tags.hpp>
#include <fas/jsonrpc/error/error_code.hpp>
#include <fas/jsonrpc/error/json/error_notify_json.hpp>
#include <fas/jsonrpc/error/json/common_error_json.hpp>
#include <fas/jsonrpc/error/json/common_error.hpp>
#include <fas/jsonrpc/error/json/error_object.hpp>
#include <fas/jsonrpc/error/json/custom_error.hpp>
#include <fas/jsonrpc/error/json/custom_error_json.hpp>
#include <fas/jsonrpc/error/json/error_object_json.hpp>
#include <fas/jsonrpc/error/json/error_message_json.hpp>



namespace fas{ namespace jsonrpc{ 

struct ad_send_error
{
  
  template<typename T>
  bool operator() (T& t, error_code::type code, int id)
  {
    return t.get_aspect().template get<_send_>()(t, error_message_json(), common_error(code, id) );
  }
  

  template<typename T>
  bool operator() (T& t, error_code::type code)
  {
    return t.get_aspect().template get<_send_>()(t, error_notify_json(), static_cast<int>(code) );
  }


  template<typename T>
  bool operator() (T& t, int code, const std::string& message, int id)
  {
    typedef custom_error_object<custom_error> error_object;
    typedef custom_error_message_json< error_object, custom_error, custom_error_json > error_json;
    
    return t.get_aspect().template get<_send_>()(t, error_json(), error_object(custom_error(code, message), id) );
  }

  template<typename T>
  bool operator() (T& t, int code, const std::string& message)
  {
    //typedef custom_error_object<custom_error> error_object;
    typedef custom_error_notify_json< custom_error, custom_error_json > error_json;
    
    return t.get_aspect().template get<_send_>()(t, error_json(), custom_error(code, message) );
  }

  
};

}}

#endif
