#ifndef FAS_JSONRPC_INVOKE_AD_REQUEST_NOT_FOUND_HPP
#define FAS_JSONRPC_INVOKE_AD_REQUEST_NOT_FOUND_HPP

#include <fas/jsonrpc/invoke/tags.hpp>

namespace fas{ namespace jsonrpc{ 

struct ad_request_not_found
{
  template<typename T, typename RN, typename RP>
  void operator() (T& t, RN /*name*/, RP /*params*/, int id)
  {
    t.get_aspect().template get<_not_impl_>()( t, id );
  }
};

}}

#endif
