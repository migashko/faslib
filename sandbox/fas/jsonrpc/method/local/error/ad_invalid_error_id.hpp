#ifndef FAS_JSONRPC_METHOD_REQUEST_AD_INVALID_ERROR_ID_HPP
#define FAS_JSONRPC_METHOD_REQUEST_AD_INVALID_ERROR_ID_HPP

#include <fas/jsonrpc/outgoing/tags.hpp>

namespace fas{ namespace jsonrpc{ namespace local{

struct ad_invalid_error_id
{
  template<typename T, typename M, typename V>
  void operator() (T& t, M&, const V&, int id)
  {
    t.get_aspect().template get<_empty_send_>()( t);
  }
};

}}}

#endif
