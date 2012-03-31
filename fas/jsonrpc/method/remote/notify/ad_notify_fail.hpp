#ifndef FAS_JSONRPC_METHOD_REMOTE_NOTIFY_AD_NOTIFY_FAIL_HPP
#define FAS_JSONRPC_METHOD_REMOTE_NOTIFY_AD_NOTIFY_FAIL_HPP

namespace fas{ namespace jsonrpc{ namespace remote{

struct ad_notify_fail
{
  template<typename T, typename M, typename V>
  void operator() (T& t, M&, V& )
  {
  }
};

}}}

#endif

