#ifndef FAS_SERIALIZATION_JSON_SER_AD_OBJECT_HPP
#define FAS_SERIALIZATION_JSON_SER_AD_OBJECT_HPP

#include <fas/serialization/json/except/try_throw.hpp>
#include <fas/serialization/json/except/out_of_range.hpp>

namespace fas{ namespace json{ namespace ser{

struct ad_object
{
  template<typename T, typename M, typename V>
  bool check(T&, M, const V& )
  {
    return true;
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, const V& v, R r)
  {
    typedef typename M::target target;
    typedef typename target::serializer_tag serializer_tag;

    if ( !r )
      return throw_(t, out_of_range(), r);

    *(r++)='{';
    
    r = t.get_aspect().template get<serializer_tag>()(t, target(), v, r);

    if ( !try_(t) )
      return r;
    
    if ( !r )
      return throw_(t, out_of_range(), r);
    
    *(r++)='}';
    
    return r;
  }
};

}}}

#endif
