#ifndef FAS_JSONRPC_INVOKE_PROCESS_OBJECT_HPP
#define FAS_JSONRPC_INVOKE_PROCESS_OBJECT_HPP

#include <fas/jsonrpc/invoke/tags.hpp>
#include <fas/jsonrpc/invoke/remote/tags.hpp>


namespace fas{ namespace jsonrpc{

struct ad_process_object
{
  template<typename T, typename Obj>
  void operator()(T& t, const Obj& obj )
  {
    if ( obj.is_notify() )
    {
      t.get_aspect().template get<_foreach_notify_>()(t, obj);
    }
    else if ( obj.is_request() )
    {
      t.get_aspect().template get<_foreach_request_>()(t, obj);
    }
    else if ( obj.is_result() )
    {
      t.get_aspect().template get<_foreach_response_>()(t, obj);
    }
    else if ( obj.is_error() )
    {
      t.get_aspect().template get<_foreach_error_>()(t, obj);
    }
    else
    {
      t.get_aspect().template get<_send_error_>()(t, error_code::internal_error);
    }
  }
};


}}

#endif

