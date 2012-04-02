#ifndef FAS_JSONRPC_METHOD_REMOTE_ERROR_AD_INVALID_ERROR_HPP
#define FAS_JSONRPC_METHOD_REMOTE_ERROR_AD_INVALID_ERROR_HPP

#include <fas/jsonrpc/types.hpp>

namespace fas{ namespace jsonrpc{ namespace remote{

struct ad_invalid_error
{
  template<typename T, typename M, typename R>
  void operator() (T& t, M&, R, id_t)
  {
  }
};

}}}

#endif
