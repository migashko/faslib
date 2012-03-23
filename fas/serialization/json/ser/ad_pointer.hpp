#ifndef FAS_SERIALIZATION_JSON_SERIALIZER_AD_POINTER_HPP
#define FAS_SERIALIZATION_JSON_SERIALIZER_AD_POINTER_HPP

#include <fas/serialization/json/ser/tags.hpp>

namespace fas{ namespace json{ namespace ser{

struct ad_pointer
{
  template<typename T, typename M, typename V>
  bool check(T& t, M, V* v )
  {
    if ( v==0 ) return false;
    
    typedef typename M::target target;
    typedef typename target::serializer_tag serializer_tag;
    
    return t.get_aspect().template get<serializer_tag>().check(t, target(), *v);
  }

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, V v, R r)
  {
    typedef typename M::target target;
    
    if ( v==0 )
      return t.get_aspect().template get<_null_>()(t, target(), 0, r);
    
    
    typedef typename target::serializer_tag serializer_tag;
    return t.get_aspect().template get<serializer_tag>()(t, target(), *v, r);
  }
  
};

}}}


#endif
