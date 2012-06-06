#ifndef FAS_JSONRPC_METHOD_REMOTE_REQUEST_AD_REQUEST_HPP
#define FAS_JSONRPC_METHOD_REMOTE_REQUEST_AD_REQUEST_HPP

#include <fas/jsonrpc/outgoing/tags.hpp>
#include <fas/jsonrpc/method/remote/request/tags.hpp>

#include <fas/jsonrpc/types.hpp>
#include <fas/jsonrpc/invoke/tags.hpp>

namespace fas{ namespace jsonrpc{ namespace remote{

template<
  typename V /*= void* */,
  typename J /*= ::fas::json::null*/
>
struct ad_request
{
  template<typename T, typename M>
  id_t operator()(T& t, M& method, const V& params)
  {
    typedef ::fas::jsonrpc::_id_ _global_id_;
    typedef typename M::aspect::template advice_cast< _name_ >::type::name_type name_type;
    
    id_t id = t.get_aspect().template get< _global_id_ >().new_id();
    
    if ( !method.get_aspect().template get< _id_ >().has(id) )
    {
      method.get_aspect().template get< _id_ >().push(id);
      t.get_aspect().template get< _global_id_ >().push(id);
    
      if ( t.get_aspect().template get<_send_request_>()( t, name_type(), J(), params, id ) )
        return id;
    
      method.get_aspect().template get<_request_fail_>()( t, method, params, id );
    }
    else
      method.get_aspect().template get<_invalid_request_id_>()( t, method, params, id );
    
    return t.get_aspect().template get< _global_id_ >().fail_id();
  }
};


}}}

#endif
