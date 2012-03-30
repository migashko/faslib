#ifndef FAS_JSONRPC_METHOD_REQUEST_AD_REQUEST_RESULT_FAIL_HPP
#define FAS_JSONRPC_METHOD_REQUEST_AD_REQUEST_RESULT_FAIL_HPP

namespace fas{ namespace jsonrpc{ namespace local{

struct ad_request_result_fail
{
  template<typename T, typename M, typename V>
  void operator() (T& t, M&, V&, int )
  {
  }
};

}}}

#endif

