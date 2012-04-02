#ifndef FAS_JSONRPC_INVOKE_AD_CHECK_NAME_HPP
#define FAS_JSONRPC_INVOKE_AD_CHECK_NAME_HPP

#include <fas/aop/tag.hpp>
#include <fas/jsonrpc/invoke/tags.hpp>

namespace fas{ namespace jsonrpc{ 

struct ad_check_name
{
  template<typename T, typename Tg, typename R>
  bool operator() (T& t, tag<Tg>, R r) const
  {
    return t.get_aspect().template get<Tg>().check_name( r );
  }
};

}}

#endif
