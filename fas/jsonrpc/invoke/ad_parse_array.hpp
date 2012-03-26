#ifndef FAS_JSONRPC_INVOKE_PARSE_ARRAY_HPP
#define FAS_JSONRPC_INVOKE_PARSE_ARRAY_HPP

#include <fas/jsonrpc/tags.hpp>

namespace fas{ namespace jsonrpc{
  

struct ad_parse_array
{
  template<typename T, typename R>
  R operator()(T& t, R r )
  {
    throw;
    return r;
  }
};

}}

#endif
