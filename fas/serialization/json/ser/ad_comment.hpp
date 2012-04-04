#ifndef FAS_SERIALIZATION_JSON_SERIALIZER_AD_COMMENT_HPP
#define FAS_SERIALIZATION_JSON_SERIALIZER_AD_COMMENT_HPP

#include <fas/serialization/json/except/try_throw.hpp>
#include <fas/serialization/json/except/out_of_range.hpp>

#include <fas/typemanip/empty_type.hpp>
#include <fas/typemanip/type2type.hpp>

namespace fas{ namespace json{ namespace ser{

struct ad_comment
{
  template<typename T, typename M, typename V>
  bool check(T& t, M m, V v )
  {
    typedef typename M::target target;
    typedef typename target::serializer_tag serializer_tag;
    return t.get_aspect().template get<serializer_tag>().check(t, target(), v);
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M m, V v, R r)
  {
    
    typedef typename M::target target;
    typedef typename target::serializer_tag serializer_tag;
    
    typedef typename M::before_comment before_comment;
    typedef typename M::after_comment after_comment;

    
    r = _1(t, r, m, type2type<before_comment>() );
    
    if ( !try_(t) )
      return r;
    
    r = t.get_aspect().template get<serializer_tag>()(t, target(), v, r);
    
    if ( !try_(t) )
      return r;
    
    r = _2(t, r, m, type2type<after_comment>() );
    
    return r;
    
  }
  
private:

  template<typename T, typename R, typename M>
  R _1(T& , R r, M, type2type<empty_type> ) { return r; }

  template<typename T, typename R, typename M, typename C>
  R _1(T& t, R r, M m, C) { return _(t, r, m.before_range() ); }

  template<typename T, typename R, typename M>
  R _2(T&, R r, M, type2type<empty_type> ) { return r; }

  template<typename T, typename R, typename M, typename C>
  R _2(T& t, R r, M m, C) { return _(t, r, m.after_range() ); }

  template<typename T, typename R, typename RC>
  R _(T& t, R r, RC rc)
  {
    if ( !r )
      return throw_(t, out_of_range(), r);

    *(r++)='/';

    if ( !r )
      return throw_(t, out_of_range(), r);

    *(r++)='*';
    
    for ( ; rc; ++r, ++rc)
    {
      if ( !r )
        return throw_(t, out_of_range(), r);
      *r=*rc;
    }
    
    if ( !r )
      return throw_(t, out_of_range(), r);
    
    *(r++)='*';
    
    if ( !r )
      return throw_(t, out_of_range(), r);

    *(r++)='/';
    
    return r;
  }
};

}}}


#endif
