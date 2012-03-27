#ifndef FAS_JSONRPC_METHOD_AD_SEND_NOTIFY_FAIL_HPP
#define FAS_JSONRPC_METHOD_AD_SEND_NOTIFY_FAIL_HPP

namespace fas{ namespace jsonrpc{ 

struct ad_send_notify_fail
{
  template<typename T, typename M, typename V>
  void operator() (T& t, M&, V&)
  {
    // сделать ретрансляцию в t вместе с method
  }
};

}}

#endif
