#ifndef FAS_JSONRPC_METHOD_REQUEST_AD_INVALID_REQUEST_ID_HPP
#define FAS_JSONRPC_METHOD_REQUEST_AD_INVALID_REQUEST_ID_HPP

#include <fas/jsonrpc/outgoing/tags.hpp>

namespace fas{ namespace jsonrpc{ namespace local{

struct ad_invalid_request_id
{
  template<typename T, typename M, typename V>
  void operator() (T& t, M&, const V&, int id)
  {
    t.get_aspect().template get<_send_common_error_>()( t, error_code::invalid_request, id );
  }
};

}}}

#endif
