#ifndef FAS_JSONRPC_ERROR_AD_INTERNAL_ERROR_HPP
#define FAS_JSONRPC_ERROR_AD_INTERNAL_ERROR_HPP

#include <fas/jsonrpc/error/tags.hpp>
#include <fas/jsonrpc/error/error_code.hpp>

namespace fas{ namespace jsonrpc{ 

struct ad_internal_error
{
  template<typename T>
  void operator() (T& t, int id)
  {
    t.get_aspect().template get<_send_error_>()( t, error_code::internal_error, id );
  }

  template<typename T>
  void operator() (T& t)
  {
    t.get_aspect().template get<_send_error_>()( t, error_code::internal_error );
  }
};

}}

#endif
