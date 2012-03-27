#ifndef FAS_JSONRPC_METHOD_AD_REQUEST_EXCEPT_HPP
#define FAS_JSONRPC_METHOD_AD_REQUEST_EXCEPT_HPP

#include <fas/jsonrpc/error/tags.hpp>

namespace fas{ namespace jsonrpc{ 

struct ad_request_except
{
  template<typename T, typename M, typename V>
  void operator() (T& t, M&, V&, const std::exception& , int id)
  {
    t.get_aspect().template get<_internal_error_>()( t, id );
  }

  template<typename T, typename M, typename V>
  void operator() (T& t, M&, V&, int id)
  {
    t.get_aspect().template get<_internal_error_>()( t, id );
  }

};

}}

#endif
