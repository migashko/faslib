#ifndef FAS_JSONRPC_OUTGOING_AD_SEND_REQUEST_HPP
#define FAS_JSONRPC_OUTGOING_AD_SEND_REQUEST_HPP

#include <fas/jsonrpc/outgoing/json/request_object_json.hpp>
#include <fas/jsonrpc/outgoing/types/request_object.hpp>

#include <fas/jsonrpc/outgoing/tags.hpp>


namespace fas{ namespace jsonrpc{ 

struct ad_send_request
{
  template<typename T, typename TName, typename J, typename V>
  bool operator() (T& t, TName, J, const V& params, int id)
  {
    typedef request_object<V> request_message;
    typedef request_object_json< TName, request_message, V, J > request_message_json;
    
    return t.get_aspect().template get<_send_>()
    (
      t,
      request_message_json(),
      request_message( params, id)
    );
  }
};

}}

#endif
