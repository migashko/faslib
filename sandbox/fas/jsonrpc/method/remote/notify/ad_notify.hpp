#ifndef FAS_JSONRPC_METHOD_REMOTE_NOTIFY_AD_NOTIFY_HPP
#define FAS_JSONRPC_METHOD_REMOTE_NOTIFY_AD_NOTIFY_HPP

#include <fas/jsonrpc/outgoing/tags.hpp>
#include <fas/jsonrpc/method/remote/notify/tags.hpp>
//#include <fas/serialization/json/meta/null.hpp>


namespace fas{ namespace jsonrpc{ namespace remote{

template<
  typename V /* = void* */,
  typename J /* = ::fas::json::null */
>
struct ad_notify
{
  typedef J json_type;
  template<typename T, typename M>
  bool operator()(T& t, M& method, const V& params)
  {
    typedef typename M::aspect::template advice_cast< _name_ >::type::name_type name_type;
    if ( t.get_aspect().template get<_send_notify_>()( t, name_type(), json_type(), params ) )
        return true;
    
    method.get_aspect().template get<_notify_fail_>()( t, method, params );
    
    return false;
  }
};

}}}

#endif

