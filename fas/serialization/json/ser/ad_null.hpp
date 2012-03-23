#ifndef FAS_SERIALIZATION_JSON_SER_AD_NULL_HPP
#define FAS_SERIALIZATION_JSON_SER_AD_NULL_HPP

#include <fas/serialization/json/except/try_throw.hpp>
#include <fas/serialization/json/except/out_of_range.hpp>


namespace fas{ namespace json{ namespace ser{

struct ad_null
{
  template<typename T, typename M, typename V>
  bool check(T&, M, const V& )
  {
    return true;
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, const V&, R r)
  {
    r = _(t, 'n', r);
    r = _(t, 'u', r);
    r = _(t, 'l', r);
    r = _(t, 'l', r);
    return r;
  }
  
private:
  
  template<typename T, typename V, typename R>
  R _(T& t, V v, R r)
  {
    if ( !try_(t) )
      return r;
    
    if ( !r )
      return throw_(t, out_of_range(), r);
    
    *r = v;
    
    return ++r;
  }
};

}}}

#endif
