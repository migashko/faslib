#ifndef FAS_SERIALIZATION_JSON_SER_AD_ENUMSET_VALUE_HPP
#define FAS_SERIALIZATION_JSON_SER_AD_ENUMSET_VALUE_HPP

namespace fas{ namespace json{ namespace ser{

struct ad_enumset_value
{
  template<typename T, typename M, typename V>
  bool check(T&, M, V v)
  {
    return 0 != ( static_cast<V>(M::value) & v );
  };
  
  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M m, V v, R r)
  {
    typedef typename M::target target;
    typedef typename target::serializer_tag serializer_tag;

    if ( !check(t, m, v) )
      return r;
    
    return t.get_aspect().template get<serializer_tag>()(t, target(), v, r);
  }
};

}}}

#endif
