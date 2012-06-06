#ifndef FAS_JSONRPC_METHOD_REMOTE_RESULT_AD_INVALID_RESULT_HPP
#define FAS_JSONRPC_METHOD_REMOTE_RESULT_AD_INVALID_RESULT_HPP

#include <fas/jsonrpc/types.hpp>

namespace fas{ namespace jsonrpc{ namespace remote{

struct ad_invalid_result
{
  template<typename T, typename M, typename R>
  void operator() (T& t, M&, R, id_t)
  {
  }
};

}}}

#endif
