#ifndef FAS_JSONRPC_METHOD_REMOTE_REQUEST_AD_INVALID_REQUEST_ID_HPP
#define FAS_JSONRPC_METHOD_REMOTE_REQUEST_AD_INVALID_REQUEST_ID_HPP

#include <fas/jsonrpc/types.hpp>

namespace fas{ namespace jsonrpc{ namespace remote{

struct ad_invalid_request_id
{
  template<typename T, typename M, typename V>
  void operator() (T& t, M&, const V&, id_t id)
  {
  }
};

}}}

#endif
