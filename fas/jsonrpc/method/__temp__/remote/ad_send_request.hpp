#ifndef FAS_JSONRPC_METHOD_AD_SEND_REQUEST_HPP
#define FAS_JSONRPC_METHOD_AD_SEND_REQUEST_HPP

#include <fas/jsonrpc/outgoing/tags.hpp>
#include <fas/jsonrpc/method/tags.hpp>
#include <fas/jsonrpc/method/error/tags.hpp>
#include <fas/jsonrpc/invoke/tags.hpp>

#include <fas/serialization/json/meta/null.hpp>
#include <fas/jsonrpc/json/request_object.hpp>
#include <fas/jsonrpc/json/request_object_json.hpp>


//#include <fas/jsonrpc/response_object.hpp>
//#include <fas/jsonrpc/response_object_json.hpp>
//#include <fas/adv/ad_aspect_select.hpp>
//#include <fas/range/range.hpp>

namespace fas{ namespace jsonrpc{

template<
  typename V = void* ,
  typename J = ::fas::json::null,
  template <typename> class VO = request_object,
  template<typename, typename, typename, typename> class OJ = request_object_json
>
struct ad_send_request
{
  template<typename T, typename M>
  int operator()(T& t, M& method, const V& params)
  {
    typedef typename M::aspect::template advice_cast<_name_>::type::name_type name_type;
    
    typedef request_object<V> request_value;
    typedef request_object_json< name_type, request_value, V, J> request_json;

    
    int id = t.get_aspect().template get< _remote_id_ >().new_id();
    method.get_aspect().template get< _remote_id_ >().push(id);
    if ( !t.get_aspect().template get<_send_>()( t, request_json(), request_value(params, id) ) )
    {
      t.get_aspect().template get< _remote_id_ >().pop(id);
      method.get_aspect().template get< _remote_id_ >().pop(id);
      method.get_aspect().template get< _send_request_fail_ >()(t, method, params, id);
      return -1;
    }
    return id;
    
  }
};


}}

#endif
