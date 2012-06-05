#ifndef FAS_SERIALIZATION_JSON_SER_AD_RANGE_HPP
#define FAS_SERIALIZATION_JSON_SER_AD_RANGE_HPP

#include <fas/serialization/json/parser/tags.hpp>
#include <fas/range/irange.hpp>

namespace fas{ namespace json{ namespace ser{

struct ad_range
{
  template<typename T, typename M, typename V>
  bool check(T&, M, const V& )
  {
    return true;
  };
  
  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, const V& v, R r)
  {
    //return t.get_aspect().template get<parse::_value_>()(t, v, r).second;
    return t.get_aspect().template get<parse::_value_>()(t, ::fas::crange( v, r) );
  }
};

}}}

#endif
