#ifndef FAS_JSONRPC_INVOKE_AD_INVOKE_INVALID_ID_HPP
#define FAS_JSONRPC_INVOKE_AD_INVOKE_INVALID_ID_HPP

#include <fas/jsonrpc/outgoing/tags.hpp>

namespace fas{ namespace jsonrpc{ 

struct ad_invoke_invalid_id
{
  template<typename T>
  void operator() (T& t, int id)
  {
    std::cout << "ad_invoke_invalid_id" << std::endl;
    t.get_aspect().template get<_empty_send_>()(t);
  }
};

}}

#endif
