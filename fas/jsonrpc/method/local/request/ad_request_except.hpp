#ifndef FAS_JSONRPC_METHOD_AD_REQUEST_EXCEPT_HPP
#define FAS_JSONRPC_METHOD_AD_REQUEST_EXCEPT_HPP

#include <fas/jsonrpc/outgoing/tags.hpp>
#include <fas/jsonrpc/error_code.hpp>

namespace fas{ namespace jsonrpc{ namespace local{

struct ad_request_except
{
  template<typename T, typename M, typename V>
  void operator() (T& t, M&, V&, const std::exception& , int id)
  {
    t.get_aspect().template get<_send_error_>()( t, error_code::internal_error, id );
  }

  template<typename T, typename M, typename V>
  void operator() (T& t, M&, V&, int id)
  {
    t.get_aspect().template get<_send_error_>()( t, error_code::internal_error, id );
    
  }
};

}}}

#endif
