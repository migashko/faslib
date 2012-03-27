#ifndef FAS_JSONRPC_METHOD_AD_SEND_NOTIFY_ERROR_HPP
#define FAS_JSONRPC_METHOD_AD_SEND_NOTIFY_ERROR_HPP

#include <fas/jsonrpc/error/tags.hpp>

namespace fas{ namespace jsonrpc{ 

struct ad_send_request_error
{
  template<typename T, typename M, typename V>
  void operator() (T& t, M&, V&)
  {
  }
};

}}

#endif
