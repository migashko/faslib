#ifndef FAS_SERIALIZATION_JSON_SER_AD_RAW_HPP
#define FAS_SERIALIZATION_JSON_SER_AD_RAW_HPP

#include <fas/serialization/json/except/try_throw.hpp>
#include <fas/serialization/json/except/out_of_range.hpp>

#include <fas/serialization/json/parser/tags.hpp>
#include <fas/range/range.hpp>

namespace fas{ namespace json{ namespace ser{

struct ad_raw
{
  template<typename T, typename M, typename V>
  bool check(T&, M, const V& )
  {
    return true;
  };

  // for STL containers and arrays ( char example[200] )
  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, const V& v, R r)
  {
    return t.get_aspect().template get<parse::_value_>()(t, ::fas::range(v), r).second;
  }
};

struct ad_traw
{
  template<typename T, typename M, typename V>
  bool check(T&, M, const V& v)
  {
    return true;
  };

  // for STL containers and arrays ( char example[200] )
  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, const V&, R r)
  {
    typename M::range_type rr = M().get_range();
    for(;rr; ++rr, ++r)
    {
      if ( !r )
        return throw_(t, out_of_range(), r);

      *r = *rr;
    }
    return r;
  }
};



}}}

#endif
