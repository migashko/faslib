#ifndef FAS_SERIALIZATION_JSON_SER_AD_BRUTE_PAIR_HPP
#define FAS_SERIALIZATION_JSON_SER_AD_BRUTE_PAIR_HPP

#include <fas/serialization/json/except/try_throw.hpp>
#include <fas/serialization/json/except/out_of_range.hpp>

namespace fas{ namespace json{ namespace ser{

struct ad_brute_pair
{
  template<typename T, typename M, typename V>
  bool check(T& t, M, const V& v)
  {
    typedef typename M::first_target first_target;
    typedef typename M::second_target second_target;
    
    typedef typename first_target::serializer_tag first_tag;
    typedef typename second_target::serializer_tag second_tag;

    return t.get_aspect().template get<first_tag>().check(t, first_target(), v)
           || t.get_aspect().template get<first_tag>().check(t, second_tag(), v);
  };
  
  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, const V& v, R r)
  {
    typedef typename M::first_target first_target;
    typedef typename M::second_target second_target;
    
    typedef typename first_target::serializer_tag first_tag;
    typedef typename second_target::serializer_tag second_tag;
    
    if ( t.get_aspect().template get<first_tag>().check(t, first_target(), v) )
    {
      r = t.get_aspect().template get<first_tag>()(t, first_target(), v, r);
      
      if ( !try_(t) )
        return r;
      
      if ( t.get_aspect().template get<second_tag>().check(t, second_target(), v) )
      {
        if ( !try_(t) )
          return r;
        
        if ( !r )
          return throw_(t, out_of_range(), r);
        
        *(r++)=',';
      }
    }
    
    r = t.get_aspect().template get<second_tag>()(t, second_target(), v, r);
    return r;
  }
  
};


}}}

#endif
