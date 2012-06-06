#ifndef FAS_RPC_JSON_METHOD_AD_SWITCH_DESERIALIZE_HPP
#define FAS_RPC_JSON_METHOD_AD_SWITCH_DESERIALIZE_HPP

#include <fas/rpc/json/tags.hpp>
#include <fas/adv/ad_aspect_select.hpp>

namespace fas{ namespace rpc{ namespace json{

struct ad_switch_deserialize
{
  template<typename T, typename TM, typename M, typename V, typename R>
  void operator() (T& t, TM& tm, M m, V& value, R params)
  {
    switch_by_tag< _deserializer_ >(tm, t).get_aspect().template get<_deserializer_>()( m, value, params);
  }
};


}}}

#endif
