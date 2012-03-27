#ifndef FAS_JSONRPC_METHOD_AD_INVALID_REQUEST_METHOD_HPP
#define FAS_JSONRPC_METHOD_AD_INVALID_REQUEST_METHOD_HPP

#include <fas/jsonrpc/error/tags.hpp>

namespace fas{ namespace jsonrpc{ 

struct ad_invalid_request_method
{
  template<typename T, typename M, typename R>
  void operator() (T& t, M&, R, int id)
  {
    t.get_aspect().template get<_invalid_request_>()( t, id );
  }
};

}}

#endif
