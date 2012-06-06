#ifndef FAS_SERIALIZATION_JSON_RPC_METHOD_AD_INCOMING_DESERIALIZE_HPP
#define FAS_SERIALIZATION_JSON_RPC_METHOD_AD_INCOMING_DESERIALIZE_HPP

//#include <fas/aop/advice_cast.hpp>
#include <fas/integral/bool_.hpp>
#include <fas/serialization/json/rpc/method/tags.hpp>


namespace fas{ namespace json{ namespace rpc{ namespace method{

struct ad_incoming_deserialize
{
  template<typename T, typename TM, typename M, typename V, typename R>
  R operator() (T& t, TM& tm, M m, V& v,  R params)
  {
    enum { method_deser = TM::aspect::template has_advice< _deserializer_ >::value };
    return _( t, tm, m, v, params, bool_< method_deser >() );
  }
  
private:
  template<typename T, typename TM, typename M, typename V, typename R>
  R _(T& t, TM& tm, M m, V& v,  R params, bool_<true> )
  {
    return tm.get_aspect().template get<_deserializer_>()( m, v, params );
  }

  template<typename T, typename TM, typename M, typename V, typename R>
  R _(T& t, TM& tm, M m, V& v,  R params, bool_<false> )
  {
    return t.get_aspect().template get<_deserializer_>()( m, v, params );
  }
};

}}}}

#endif
