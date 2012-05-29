#ifndef FAS_SERIALIZATION_JSON_SERIALIZER_AD_FIELD_HPP
#define FAS_SERIALIZATION_JSON_SERIALIZER_AD_FIELD_HPP

#include <fas/serialization/json/except/try_throw.hpp>
#include <fas/serialization/json/except/out_of_range.hpp>

namespace fas{ namespace json{ namespace ser{

struct ad_field
{
  template<typename T, typename M, typename V>
  bool check(T& t, M, const V& v)
  {
    typedef typename M::target1 target1;
    typedef typename M::target2 target2;
    typedef typename target1::serializer_tag serializer_tag1;
    typedef typename target2::serializer_tag serializer_tag2;

    return t.get_aspect().template get<serializer_tag1>().check(t, target1(), v )
           && t.get_aspect().template get<serializer_tag2>().check(t, target2(), v );
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, const V& v, R r)
  {
    typedef typename M::target1 target1;
    typedef typename M::target2 target2;
    typedef typename target1::serializer_tag serializer_tag1;
    typedef typename target2::serializer_tag serializer_tag2;

    r = t.get_aspect().template get<serializer_tag1>()(t, target1(), v, r );
    if ( !try_(t) )
      return r;

    if ( !r )
      return throw_(t, out_of_range(), r);

    *(r++)=':';
    
    r = t.get_aspect().template get<serializer_tag2>()(t, target2(), v, r );
    
    return r;
  }
};


}}}


#endif
