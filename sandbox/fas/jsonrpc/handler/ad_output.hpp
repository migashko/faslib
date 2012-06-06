#ifndef FAS_JSONRPC_HANDLER_AD_OUTPUT_HPP
#define FAS_JSONRPC_HANDLER_AD_OUTPUT_HPP

#include <fas/jsonrpc/outgoing/tags.hpp>

namespace fas{ namespace jsonrpc{
  
struct ad_output
{
  template<typename T, typename R>
  void operator()(T& t, R r)
  {
    if ( r )
      t << t.get_aspect().template get<_buffer_>();
  }
};


}}

#endif
