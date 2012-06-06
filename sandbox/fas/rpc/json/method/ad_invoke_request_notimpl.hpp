#ifndef FAS_RPC_JSON_METHOD_AD_INVOKE_REQUEST_NOTIMPL_HPP
#define FAS_RPC_JSON_METHOD_AD_INVOKE_REQUEST_NOTIMPL_HPP

#include <fas/rpc/json/tags.hpp>
#include <fas/rpc/json/error_code.hpp>

namespace fas{ namespace rpc{ namespace json{ 


struct ad_invoke_request_notimpl
{
  template<typename T, typename TM, typename R>
  void operator() (T& t, TM& tm, R params, int id)
  {
    tm.get_aspect().template get<_not_impl_>()( t, tm, params, id );
  }
};


}}}

#endif
