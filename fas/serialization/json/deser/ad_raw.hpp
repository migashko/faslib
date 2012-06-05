#ifndef FAS_SERIALIZATION_JSON_DESER_AD_RAW_HPP
#define FAS_SERIALIZATION_JSON_DESER_AD_RAW_HPP

#include <fas/serialization/json/except.hpp>
#include <fas/serialization/json/deser/deserialize_string.hpp>
#include <fas/serialization/json/deser/tags.hpp>
#include <fas/serialization/json/parser/tags.hpp>

#include <fas/range/range.hpp>
#include <fas/range/orange.hpp>
#include <fas/range/irange.hpp>

namespace fas{ namespace json{ namespace deser{

struct ad_raw
{
  template<typename T, typename M, typename R>
  bool check(T& t, M, R r)
  {
    return true;
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, V& v, R r)
  {
    
    //return t.get_aspect().template get<parse::_value_>()( t, r, orange(v) ).first;
    return t.get_aspect().template get<parse::_value_>()( t, iorange( r, orange(v) ) );
  }
};

struct ad_traw
{
private:
  template<typename R, typename RS>
  bool _check(R& r, RS rs)
  {
    for ( ;r && rs && *r==*rs; ++r, ++rs );
    return !rs;
  }
public:

  template<typename T, typename M, typename R>
  bool check(T& t, M, R r)
  {
    return t.get_aspect().template get<parse::_value_>().check(t, r);
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, V&, R r)
  {
    if ( !t.get_aspect().template get<parse::_value_>().check(t, r) )
      return r;

    R income =  r;
    if (!_check(r, M().get_range() ) )
      return income;
    
    return r;
  }
};

}}}

#endif
