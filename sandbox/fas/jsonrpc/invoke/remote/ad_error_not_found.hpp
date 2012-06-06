#ifndef FAS_JSONRPC_INVOKE_AD_ERROR_NOT_FOUND_HPP
#define FAS_JSONRPC_INVOKE_AD_ERROR_NOT_FOUND_HPP

#include <fas/jsonrpc/invoke/tags.hpp>

namespace fas{ namespace jsonrpc{ 

struct ad_error_not_found
{
  template<typename T, typename RP>
  void operator() (T& t, RP /*params*/, int id)
  {
    t.get_aspect().template get< _invoke_invalid_id_ >()( t, id );
  }
};


}}

#endif
