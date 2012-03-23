#ifndef FAS_SERIALIZATION_JSON_SERIALIZER_AD_BLOCK_HPP
#define FAS_SERIALIZATION_JSON_SERIALIZER_AD_BLOCK_HPP

#include <fas/serialization/json/except/try_throw.hpp>
#include <fas/serialization/json/except/out_of_range.hpp>
#include <fas/serialization/json/meta/is_sequence.hpp>

#include <fas/typemanip/empty_type.hpp>



namespace fas{ namespace json{ namespace ser{

template<char c = ' ', int n = 2 >
struct ad_block
{
  int depth;
  
  ad_block(): depth() {}

  template<typename T>
  void clear(T& t)
  {
    depth = 0;
  }
  
  template<typename T, typename M, typename V>
  bool check(T& t, M m, V v )
  {
    typedef typename M::target target;
    return _check(t, target(), v);
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M m, V v, R r)
  {
    typedef typename M::target target;
    
    if ( !is_sequence<M>::value)
    {
      ++depth;

      r = __(t, r);
      
      if ( !try_(t) )
        return r;
    }

    r = _(t, target(), v, r);
    
    if ( !try_(t) )
      return r;
    
    if (is_sequence<M>::value)
    {
      r = __(t, r);
      if ( !try_(t) )
        return r;
    }
    else
      --depth;
    
    return r;
  }
private:
  
  template<typename T, typename V>
  bool _check(T& , empty_type, V  )
  {
    return false;
  };

  template<typename T, typename M, typename V>
  bool _check(T& t, M m, V v )
  {
    typedef typename M::serializer_tag serializer_tag;
    return t.get_aspect().template get<serializer_tag>().check(t, m, v);
  };
  
  template<typename T, typename M, typename V, typename R>
  R _(T& t, M m, V v, R r)
  {
    typedef typename M::serializer_tag serializer_tag;
    return t.get_aspect().template get<serializer_tag>()(t, m, v, r);
  }

  template<typename T, typename V, typename R>
  R _(T& , empty_type, V , R r)
  {
    return r;
  }

/// ////////////////////

  template<typename T, typename R>
  R __(T& t, R r)
  {
    if (!r)
      return throw_(t, out_of_range(), r);

    *(r++) = '\n';

    for ( int i=0; i < n*depth; ++i)
    {
      if (!r)
        return throw_(t, out_of_range(), r);

      *(r++) = c;
    }

    return r;
  }


};

}}}


#endif
