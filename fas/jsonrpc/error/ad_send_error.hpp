#ifndef FAS_JSONRPC_ERROR_AD_ERROR_HPP
#define FAS_JSONRPC_ERROR_AD_ERROR_HPP

#include <fas/jsonrpc/outgoing/tags.hpp>
#include <fas/jsonrpc/error/error_code.hpp>
#include <fas/jsonrpc/error/json/error_notify_json.hpp>
#include <fas/jsonrpc/error/json/common_error_json.hpp>
#include <fas/jsonrpc/error/json/common_error.hpp>



namespace fas{ namespace jsonrpc{ 

struct ad_send_error
{
  
  template<typename T>
  void operator() (T& t, error_code::type code, int id)
  {
    t.get_aspect().template get<_send_>()(t, common_error_json(), common_error(code, id) );
  }
  

  template<typename T>
  void operator() (T& t, error_code::type code)
  {
    t.get_aspect().template get<_send_>()(t, error_notify_json(), static_cast<int>(code) );
  }


  template<typename T>
  void operator() (T& t, int code, const std::string& message, int id)
  {
  }

  template<typename T>
  void operator() (T& t, int code, const std::string& message)
  {
  }

  
};

}}

#endif
