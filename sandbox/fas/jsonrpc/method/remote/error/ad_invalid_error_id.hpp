#ifndef FAS_JSONRPC_METHOD_REMOTE_ERROR_AD_INVALID_ERROR_ID_HPP
#define FAS_JSONRPC_METHOD_REMOTE_ERROR_AD_INVALID_ERROR_ID_HPP

#include <fas/jsonrpc/types.hpp>

namespace fas{ namespace jsonrpc{ namespace remote{

struct ad_invalid_error_id
{
  template<typename T, typename M, typename V>
  void operator() (T& t, M&, const V&, id_t)
  {
  }
};

}}}

#endif
