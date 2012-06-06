#ifndef FAS_JSONRPC_METHOD_REMOTE_REQUEST_AD_REQUEST_FAIL_HPP
#define FAS_JSONRPC_METHOD_REMOTE_REQUEST_AD_REQUEST_FAIL_HPP

namespace fas{ namespace jsonrpc{ namespace remote{

struct ad_request_fail
{
  template<typename T, typename M, typename V>
  void operator() (T& t, M&, V&, int )
  {
  }
};

}}}

#endif

