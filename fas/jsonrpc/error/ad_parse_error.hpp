#ifndef FAS_JSONRPC_ERROR_AD_PARSE_ERROR_HPP
#define FAS_JSONRPC_ERROR_AD_PARSE_ERROR_HPP

#include <fas/jsonrpc/tags.hpp>
#include <fas/jsonrpc/error/error_code.hpp>

namespace fas{ namespace jsonrpc{ 

struct ad_parse_error
{
  template<typename T>
  void operator() (T& t, int id)
  {
    t.get_aspect().template get<_send_error_>()( t, error_code::parse_error, id );
  }

  template<typename T>
  void operator() (T& t)
  {
    t.get_aspect().template get<_send_error_>()( t, error_code::parse_error );
  }
};

}}

#endif
