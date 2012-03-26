#ifndef FAS_JSONRPC_METHOD_AD_REQUEST_STUB_HPP
#define FAS_JSONRPC_METHOD_AD_REQUEST_STUB_HPP

#include <fas/jsonrpc/error/tags.hpp>

// todo: убрать

namespace fas{ namespace jsonrpc{ 

struct ad_request_stub
{
  template<typename T>
  void operator()(T& t, void*, int id)
  {
    t.get_aspect().template get<_not_impl_>()(t, id);
  }
};


}}

#endif
