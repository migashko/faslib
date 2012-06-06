#ifndef FAS_SERIALIZATION_JSON_RPC_METHOD_AD_OUTGOING_SERIALIZE_HPP
#define FAS_SERIALIZATION_JSON_RPC_METHOD_AD_OUTGOING_SERIALIZE_HPP

#include <fas/aop/advice.hpp>
#include <fas/aop/find_advice.hpp>
#include <fas/serialization/json/rpc/method/tags.hpp>

namespace fas{ namespace json{ namespace rpc{ namespace method{

struct ad_outgoing_serialize
{
  template<typename T, typename TM, typename M, typename V, typename R>
  R operator() (T& t, TM& tm, M m, const V& v,  R params)
  {
    enum { method_ser = TM::aspect::template has_advice< _serializer_ >::value };
    return _( t, tm, m, v, params, bool_< method_ser >() );
  }
  
private:
  
  template<typename T, typename TM, typename M, typename V, typename R>
  R _(T& t, TM& tm, M m, const V& v,  R params, bool_<true> )
  {
    return tm.get_aspect().template get<_serializer_>()( m, v, params );
  }

  template<typename T, typename TM, typename M, typename V, typename R>
  R _(T& t, TM& tm, M m, const V& v,  R params, bool_<false> )
  {
    return t.get_aspect().template get<_serializer_>()( m, v, params );
  }
  
};

}}}}

#endif

