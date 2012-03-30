#ifndef FAS_JSONRPC_METHOD_REQUEST_AD_REQUEST_ERROR_FAIL_HPP
#define FAS_JSONRPC_METHOD_REQUEST_AD_REQUEST_ERROR_FAIL_HPP

namespace fas{ namespace jsonrpc{ namespace local{

struct ad_request_error_fail
{
  template<typename T, typename M, typename V>
  void operator() (T& t, M&, V&, int )
  {
  }
};

}}}

#endif

