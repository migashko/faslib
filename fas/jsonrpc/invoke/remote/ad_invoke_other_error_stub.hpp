#ifndef FAS_JSONRPC_INVOKE_AD_INVOKE_OTHER_ERROR_STUB_HPP
#define FAS_JSONRPC_INVOKE_AD_INVOKE_OTHER_ERROR_STUB_HPP

#include <fas/jsonrpc/invoke/tags.hpp>

namespace fas{ namespace jsonrpc{

struct ad_invoke_other_error_stub
{
  template<typename T, typename RP>
  void operator()(T& t, RP )
  {
    t.get_aspect().template get<_empty_send_>()(t);
  }
};


}}

#endif
