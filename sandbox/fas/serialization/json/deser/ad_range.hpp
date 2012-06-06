#ifndef FAS_SERIALIZATION_JSON_DESER_AD_RANGE_HPP
#define FAS_SERIALIZATION_JSON_DESER_AD_RANGE_HPP

//#include <fas/serialization/json/except.hpp>
//#include <fas/serialization/json/deser/deserialize_string.hpp>
//#include <fas/serialization/json/deser/tags.hpp>
#include <fas/serialization/json/parser/tags.hpp>

// #include <fas/range/.hpp>

namespace fas{ namespace json{ namespace deser{

struct ad_range
{
  template<typename T, typename M, typename R>
  bool check(T& t, M, R r)
  {
    return true;
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, V& v, R r)
  {
    return t.get_aspect().template get<parse::_value_>()( t, r, v ).first;
  }
};


}}}

#endif
