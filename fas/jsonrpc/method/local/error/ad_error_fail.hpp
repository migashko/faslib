#ifndef FAS_JSONRPC_METHOD_LOCAL_ERROR_AD_ERROR_FAIL_HPP
#define FAS_JSONRPC_METHOD_LOCAL_ERROR_AD_ERROR_FAIL_HPP

namespace fas{ namespace jsonrpc{ namespace local{

struct ad_error_fail
{
  template<typename T, typename M, typename V>
  void operator() (T& t, M&, V&, int )
  {
  }
};

}}}

#endif

