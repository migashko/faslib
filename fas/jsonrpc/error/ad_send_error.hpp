#ifndef FAS_JSONRPC_ERROR_AD_ERROR_HPP
#define FAS_JSONRPC_ERROR_AD_ERROR_HPP

#include <fas/jsonrpc/outgoing/tags.hpp>
#include <fas/jsonrpc/error/error_code.hpp>
#include <fas/jsonrpc/error/json/error_notify_json.hpp>



namespace fas{ namespace jsonrpc{ 

struct ad_send_error
{
  
  template<typename T>
  void operator() (T& t, error_code::type code, int id)
  {
    
    /*
    t.get_aspect().template get<_serializer_>()
    (
      error_object_json(),
      static_cast<int>(code),
      tm.get_aspect().template get<_result_buffer_manager_>().initial_range(t)
    );
    */
  }
  

  template<typename T>
  void operator() (T& t, error_code::type code)
  {
    t.get_aspect().template get<_send_>()(t, error_notify_json(), static_cast<int>(code) );
    /*
    typedef typename T::aspect::template advice_cast< _serializer_ >::type  serializer;
    t.get_aspect().template get<_outgoing_buffer_manager_>().clear(t);

    serializer ser;
    ser(error_notify_json(), static_cast<int>(code), t.get_aspect().template get<_outgoing_buffer_manager_>().init_range(t) );
    */
    
    /*
    t.get_aspect().template get<_serializer_>()
    (
      //error_object_json(),
      error_json(),
      static_cast<int>(code),
      t.get_aspect().template get<_outgoing_buffer_manager_>().initial_range(t)
    );*/
    
    
    //t.get_aspect().template get<_output_>()( t, t.get_aspect().template get<_outgoing_buffer_manager_>().range(t) );
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
