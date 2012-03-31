#ifndef FAS_JSONRPC_OUTGOING_AD_SEND_NOTIFY_HPP
#define FAS_JSONRPC_OUTGOING_AD_SEND_NOTIFY_HPP

#include <fas/jsonrpc/outgoing/json/notify_json.hpp>
#include <fas/jsonrpc/outgoing/tags.hpp>

namespace fas{ namespace jsonrpc{ 

struct ad_send_notify
{
  template<typename T, typename TName, typename J, typename V>
  bool operator() (T& t, TName, J, const V& params)
  {
    return t.get_aspect().template get<_send_>()(t, notify_json<TName,J>(), params );
  }
};

}}

#endif
