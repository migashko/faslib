#ifndef FAS_JSONRPC_METHOD_AD_NOTIFY_HANDLER_HPP
#define FAS_JSONRPC_METHOD_AD_NOTIFY_HANDLER_HPP

#include <fas/jsonrpc/method/tags.hpp>


namespace fas{ namespace jsonrpc{ 

struct ad_notify_handler
{
  template<typename T, typename M, typename V>
  void operator()(T& t, M& method, const V& v)
  {
    try
    {
      method.get_aspect().template get<_notify_>()(t, method, v);
    }
    catch(const std::exception& e)
    {
      method.get_aspect().template get<_notify_error_>()(t, method, v, e);
    }
    catch(...)
    {
      method.get_aspect().template get<_notify_error_>()(t, method, v);
    }
  }
};


}}

#endif
