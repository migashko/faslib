#ifndef FAS_JSONRPC_METHOD_REMOTE_ERROR_AD_ERROR_HANDLER_HPP
#define FAS_JSONRPC_METHOD_REMOTE_ERROR_AD_ERROR_HANDLER_HPP

#include <fas/jsonrpc/types.hpp>
#include <fas/jsonrpc/method/remote/error/tags.hpp>

namespace fas{ namespace jsonrpc{ namespace remote{

struct ad_error_handler
{
  template<typename T, typename M, typename V>
  void operator()(T& t, M& method, const V& error, id_t id)
  {
    try
    {
      method.get_aspect().template get<_error_>()(t, method, error, id);
    }
    catch(const std::exception& e)
    {
      method.get_aspect().template get<_error_except_>()(t, method, error, e, id);
    }
    catch(...)
    {
      method.get_aspect().template get<_error_except_>()(t, method, error, id);
    }
  }
};


}}}

#endif
