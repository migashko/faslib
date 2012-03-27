#ifndef FAS_JSONRPC_METHOD_AD_INVALID_ID_METHOD_HPP
#define FAS_JSONRPC_METHOD_AD_INVALID_ID_METHOD_HPP

#include <fas/jsonrpc/error/tags.hpp>

namespace fas{ namespace jsonrpc{ 

struct ad_invalid_id_method
{
  template<typename T, typename M, typename V>
  void operator() (T& t, M&, const V& v, int id)
  {
    t.get_aspect().template get<_invalid_id_>()( t, id );
  }
};

}}

#endif
