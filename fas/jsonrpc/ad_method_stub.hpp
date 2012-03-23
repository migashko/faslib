#ifndef FAS_JSONRPC_AD_MEHOD_STUB_HPP
#define FAS_JSONRPC_AD_MEHOD_STUB_HPP

#include <fas/jsonrpc/tags.hpp>
// #include <fas/jsonrpc/error/error_code.hpp>

namespace fas{ namespace jsonrpc{ 

struct ad_method_stub
{
  template<typename T>
  void operator()(T& t, void*, int id)
  {
    t.get_aspect().template get<_not_impl_>()(t, id);
  }

  template<typename T>
  void operator()(T& t, void*)
  {
    t.get_aspect().template get<_not_impl_>()(t);
  }
};


}}

#endif
