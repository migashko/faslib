#ifndef FAS_RPC_JSON_METHOD_AD_INVOKE_ERROR_HANDLER_HPP
#define FAS_RPC_JSON_METHOD_AD_INVOKE_ERROR_HANDLER_HPP

#include <fas/serialization/json/rpc/method/tags.hpp>

namespace fas{ namespace json{ namespace rpc{ namespace method{


struct ad_invoke_error_handler
{
  template<typename T, typename TM, typename R>
  void operator() ( T& t, TM& tm, R params, int id )
  {
  }

  template<typename T, typename TM, typename R>
  void operator() ( T& t, TM& tm, R params )
  {
  }

};


}}}}

#endif
