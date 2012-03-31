#ifndef FAS_JSONRPC_METHOD_REMOTE_RESULT_AD_RESULT_HANDLER_HPP
#define FAS_JSONRPC_METHOD_REMOTE_RESULT_AD_RESULT_HANDLER_HPP

#include <fas/jsonrpc/types.hpp>
#include <fas/jsonrpc/method/remote/result/tags.hpp>

namespace fas{ namespace jsonrpc{ namespace remote{

struct ad_result_handler
{
  template<typename T, typename M, typename V>
  void operator()(T& t, M& method, const V& params, id_t id)
  {
    try
    {
      method.get_aspect().template get<_result_>()(t, method, params, id);
    }
    catch(const std::exception& e)
    {
      method.get_aspect().template get<_result_except_>()(t, method, params, e, id);
    }
    catch(...)
    {
      method.get_aspect().template get<_result_except_>()(t, method, params, id);
    }
  }
};


}}}

#endif
