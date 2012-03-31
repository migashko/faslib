#ifndef FAS_JSONRPC_METHOD_LOCAL_REQUEST_AD_INVALID_REQUEST_HPP
#define FAS_JSONRPC_METHOD_LOCAL_REQUEST_AD_INVALID_REQUEST_HPP

#include <fas/jsonrpc/outgoing/tags.hpp>

namespace fas{ namespace jsonrpc{ namespace local{ 

struct ad_invalid_request
{
  template<typename T, typename M, typename R>
  void operator() (T& t, M&, R, int id)
  {
    t.get_aspect().template get<_send_error_>()( t, error_code::invalid_request, id );
  }
};

}}}

#endif
