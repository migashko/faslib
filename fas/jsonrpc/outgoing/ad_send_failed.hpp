#ifndef FAS_JSONRPC_OUTGOING_AD_SEND_FAILED_HPP
#define FAS_JSONRPC_OUTGOING_AD_SEND_FAILED_HPP

#include <fas/serialization/json/except/json_error.hpp>

namespace fas{ namespace jsonrpc{ 

struct ad_send_failed
{
  template<typename T, typename J, typename V, typename R>
  void operator() ( T&, J, const V&, R , const ::fas::json::json_error& )
  {
  }
};

}}

#endif
