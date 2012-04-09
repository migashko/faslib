#ifndef FAS_SERIALIZATION_JSON_SERIALIZER_AD_SEQUENCE_HPP
#define FAS_SERIALIZATION_JSON_SERIALIZER_AD_SEQUENCE_HPP

#include <fas/serialization/json/except/try_throw.hpp>
#include <fas/serialization/json/except/out_of_range.hpp>

#include <fas/range/range.hpp>
#include <fas/range/distance.hpp>
#include <fas/range/decrease.hpp>

#include <fas/typemanip/is_array.hpp>
#include <fas/integral/int_.hpp>
#include <fas/integral/bool_.hpp>

namespace fas{ namespace json{ namespace ser{

struct ad_sequence
{
  template<typename T, typename M, typename V>
  bool check(T&, M, const V& v)
  {
    return M::limit && ::fas::range( v );
  };
  
  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, const V& v, R r)
  {
    typedef typename M::target target;
    //return _( t, target(), ::fas::range( v ), r);
    return _1( t, target(), v , r, typename is_array<V>::type(), int_< M::limit >() );
  }

  template<typename T, typename M, typename V, typename R, typename ISA>
  R _1(T& t, M, const V& v, R r, ISA, int_<-1>)
  {
    return _( t, M(), ::fas::range( v ) , r);
  }

 template<typename T, typename M, typename V, typename R, typename ISA>
  R _1(T& t, M, const V& v, R r, ISA, int_<0>)
  {
    return r;
  }

  template<typename T, typename M, typename V, typename R, int N, typename ISA>
  R _1(T& t, M, const V& v, R r, ISA, int_<N>)
  {
    typename ::fas::typerange< const V>::range rr = ::fas::range( v );
    if ( ::fas::distance(rr) > N )
      /*rr = */   ::fas::decrease( rr, 0, ::fas::distance(rr) - N );
    return _( t, M(), rr , r);
  }

  //    ::fas::range_traits< const V>::range r = ::fas::range( v );

  template<typename T, typename M, typename V, typename R>
  R _1(T& t, M, const V* v, R r, false_, int_<0>) { return r; }

  template<typename T, typename M, typename V, typename R>
  R _1(T& t, M, const V* v, R r, false_, int_<-1>) { return r; }

  template<typename T, typename M, typename V, typename R, int N>
  R _1(T& t, M, const V* v, R r, false_, int_<N>                                )
  {
    if ( !v ) return r;
    return _( t, M(), ::fas::range( v, v + N ), r);
  }

private:
  
  template<typename T, typename M, typename AR, typename R>
  R _( T& t, M, AR ar, R r)
  {
    typedef M target;
    typedef typename target::serializer_tag serializer_tag;
    
    if ( ar )
    {
      r = t.get_aspect().template get<serializer_tag>()(t, target(), *ar++, r);

      for ( ; ar && try_(t); ++ar)
      {
        if (!r)
          return throw_(t, out_of_range(), r);
        
        *r = ',';
        r = t.get_aspect().template get<serializer_tag>()(t, target(), *ar, ++r);
      }
    }
    return r;
  };
};

}}}


#endif
