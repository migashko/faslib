#ifndef FAS_JSONRPC_METHOD_AD_NOTIFY_STUB_HPP
#define FAS_JSONRPC_METHOD_AD_NOTIFY_STUB_HPP

#include <fas/jsonrpc/tags.hpp>
// #include <fas/jsonrpc/error/error_code.hpp>

// todo: убрать
namespace fas{ namespace jsonrpc{ 

struct ad_notify_stub
{
  template<typename T>
  void operator()(T& t, void*)
  {
    t.get_aspect().template get<_not_impl_>()(t);
  }
};


}}

#endif
