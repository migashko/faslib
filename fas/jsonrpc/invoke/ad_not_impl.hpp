#ifndef FAS_JSONRPC_INVOKE_AD_NOT_IMPL_HPP
#define FAS_JSONRPC_INVOKE_AD_NOT_IMPL_HPP

#include <fas/jsonrpc/error_code.hpp>
#include <fas/jsonrpc/outgoing/tags.hpp>

namespace fas{ namespace jsonrpc{ 

struct ad_not_impl
{
  template<typename T>
  void operator() (T& t, int id)
  {
    t.get_aspect().template get<_send_common_error_>()( t, error_code::method_not_found, id );
  }

  template<typename T>
  void operator() (T& t)
  {
    t.get_aspect().template get<_send_common_error_>()( t, error_code::method_not_found );
  }
};


}}

#endif
