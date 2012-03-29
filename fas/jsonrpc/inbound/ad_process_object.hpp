#ifndef FAS_JSONRPC_INBOUND_AD_PROCESS_OBJECT_HPP
#define FAS_JSONRPC_INBOUND_AD_PROCESS_OBJECT_HPP

#include <fas/jsonrpc/invoke/tags.hpp>
//#include <fas/jsonrpc/invoke/remote/tags.hpp>


namespace fas{ namespace jsonrpc{

struct ad_process_object
{
  template<typename T, typename Obj>
  void operator()(T& t, const Obj& obj )
  {
    if ( obj.is_notify() )
    {
      t.get_aspect().template get< _invoke_notify_ >()(t, obj.name_range(), obj.params_range() );
    }
    else if ( obj.is_request() )
    {
      t.get_aspect().template get< _invoke_request_ >()(t, obj.name_range(), obj.params_range(), obj.get_id() );
    }
    else if ( obj.is_result() )
    {
      std::cout << "ad_process_object" << std::endl;
      t.get_aspect().template get< _invoke_result_ >()(t, obj.result_range(), obj.get_id() );
    }
    else if ( obj.is_error() )
    {
      if ( obj.has_id() ) 
        t.get_aspect().template get< _invoke_error_ >()(t, obj.result_range(), obj.get_id() );
      else
        t.get_aspect().template get< _invoke_other_error_ >()(t, obj.result_range() );
      
    }
    else
    {
      // Ошибка без id
      
      // Сюда не должен заходть, т.к. должны передавать валидный объект
      // t.get_aspect().template get<_send_error_>()(t, error_code::internal_error);
    }
  }
};


}}

#endif

