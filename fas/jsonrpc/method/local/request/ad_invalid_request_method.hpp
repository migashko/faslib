#ifndef FAS_JSONRPC_METHOD_AD_INVALID_REQUEST_METHOD_HPP
#define FAS_JSONRPC_METHOD_AD_INVALID_REQUEST_METHOD_HPP

#include <fas/jsonrpc/method/request/tags.hpp>

namespace fas{ namespace jsonrpc{ 

struct ad_invalid_request_method
{
  template<typename T, typename M, typename R>
  void operator() (T& t, M&, R, int id)
  {
    t.get_aspect().template get<_send_error_>()( t, error_code::invalid_request, id );
  }
};

}}

#endif
