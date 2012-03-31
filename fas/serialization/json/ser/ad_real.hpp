#ifndef FAS_SERIALIZATION_JSON_SERIALIZER_AD_REAL_HPP
#define FAS_SERIALIZATION_JSON_SERIALIZER_AD_REAL_HPP

#include <fas/serialization/json/except/try_throw.hpp>
#include <fas/serialization/json/except/out_of_range.hpp>

#include <sstream>

namespace fas{ namespace json{ namespace ser{

struct ad_real
{
  template<typename T, typename M, typename V>
  bool check(T&, M, V )
  {
    return true;
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, V v, R r)
  {
    int it_is_not_a_very_efficient_algorithm;
    std::stringstream ss;

    ss << v;
    for ( register typename R::value_type chr ; ; ++r)
    {
      if (!r)
        return throw_(t, out_of_range(), r);
      ss >> chr;
      if ( !ss )
        break;
      *r = chr;
    }

    return r;
  }
};

}}}


#endif
