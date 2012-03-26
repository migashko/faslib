#ifndef FAS_JSONRPC_METHOD_AD_PARSE_REQUEST_STUB_HPP
#define FAS_JSONRPC_METHOD_AD_PARSE_REQUEST_STUB_HPP

#include <fas/jsonrpc/error/tags.hpp>


namespace fas{ namespace jsonrpc{ 

struct ad_parse_request_stub
{
  template<typename T, typename M, typename R>
  void operator()(T& t, M&, R, int id)
  {
    t.get_aspect().template get<_not_impl_>()(t, id);
  }
};


}}

#endif
