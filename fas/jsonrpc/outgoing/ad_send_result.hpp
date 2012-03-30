#ifndef FAS_JSONRPC_OUTGOING_AD_SEND_RESULT_HPP
#define FAS_JSONRPC_OUTGOING_AD_SEND_RESULT_HPP

#include <fas/jsonrpc/outgoing/json/result_object_json.hpp>
#include <fas/jsonrpc/outgoing/types/result_object.hpp>

#include <fas/jsonrpc/outgoing/tags.hpp>
#include <fas/jsonrpc/error_code.hpp>

namespace fas{ namespace jsonrpc{ 

struct ad_send_result
{
  template<typename T, typename J, typename V>
  bool operator() (T& t, J, const V& result, int id)
  {
    typedef result_object<V> result_message;
    typedef result_object_json< result_message, V, J > result_message_json;
    
    return t.get_aspect().template get<_send_>()
    (
      t,
      result_message_json(),
      result_message( result, id)
    );
  }
};

}}

#endif
