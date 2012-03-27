#ifndef FAS_JSONRPC_METHOD_AD_SEND_NOTIFY_HPP
#define FAS_JSONRPC_METHOD_AD_SEND_NOTIFY_HPP

#include <fas/jsonrpc/outgoing/tags.hpp>
#include <fas/jsonrpc/method/tags.hpp>
#include <fas/jsonrpc/method/error/tags.hpp>

#include <fas/serialization/json/meta/null.hpp>
#include <fas/jsonrpc/json/notify_object_json.hpp>


//#include <fas/jsonrpc/response_object.hpp>
//#include <fas/jsonrpc/response_object_json.hpp>
//#include <fas/adv/ad_aspect_select.hpp>
//#include <fas/range/range.hpp>

namespace fas{ namespace jsonrpc{

template<
  typename V = void* ,
  typename J = ::fas::json::null,
  template<typename, typename> class OJ = notify_object_json
>
struct ad_send_notify
{
  template<typename T, typename M>
  void operator()(T& t, M& method, const V& params)
  {
    typedef typename M::aspect::template advice_cast<_name_>::type::name_type name_type;
    typedef notify_object_json< name_type, J> notify_json;
    
    if ( !t.get_aspect().template get<_send_>()( t, notify_json(), params ) )
      method.get_aspect().template get< _send_notify_fail_ >()(t, method, params);
  }
};


}}

#endif
