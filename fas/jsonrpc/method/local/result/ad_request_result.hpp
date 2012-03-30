#ifndef FAS_JSONRPC_METHOD_REQUEST_AD_REQUEST_RESULT_HPP
#define FAS_JSONRPC_METHOD_REQUEST_AD_REQUEST_RESULT_HPP

#include <fas/jsonrpc/outgoing/tags.hpp>
#include <fas/jsonrpc/method/local/request/tags.hpp>

#include <fas/serialization/json/meta/null.hpp>
/*#include <fas/jsonrpc/json/result_object.hpp>
#include <fas/jsonrpc/json/result_object_json.hpp>
*/


namespace fas{ namespace jsonrpc{ namespace local{

template<
  typename V = void* ,
  typename J = ::fas::json::null
>
struct ad_request_result
{
  typedef J json_type;
  template<typename T, typename M>
  bool operator()(T& t, M& method, const V& result, int id)
  {
    if ( method.get_aspect().template get<_request_id_>().has(id) )
    {
      method.get_aspect().template get<_request_id_>().pop(id);

      if ( t.get_aspect().template get<_send_result_>()( t, json_type(), result, id ) )
        return true;
      method.get_aspect().template get<_request_result_fail_>()( t, method, result, id );
    }
    else
      method.get_aspect().template get<_invalid_result_id_>()( t, method, result, id );
    
    return false;
    
  }
};


}}}

#endif

