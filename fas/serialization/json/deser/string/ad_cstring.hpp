#ifndef FAS_SERIALIZATION_JSON_DESER_STRING_AD_CSTRING_HPP
#define FAS_SERIALIZATION_JSON_DESER_STRING_AD_CSTRING_HPP

#include <fas/serialization/json/except/try_throw.hpp>
#include <fas/serialization/json/except/out_of_range.hpp>
#include <fas/serialization/json/except/unexpected_end_fragment.hpp>
#include <fas/serialization/json/except/invalid_json_string.hpp>
#include <fas/serialization/json/except/expected_of.hpp>

#include <fas/serialization/json/deser/tags.hpp>
#include <fas/serialization/json/parser/tags.hpp>


namespace fas{ namespace json{ namespace deser{

struct ad_cstring
{
private:
  template<typename R, typename RS>
  bool _check(R& r, RS rs)
  {
    for ( ;r && rs && *r==*rs; ++r, ++rs );
    return !rs && r && *r=='"';
  }
public:

  template<typename T, typename M, typename R>
  bool check(T& t, M, R r)
  {
    return t.get_aspect().template get<parse::_string_>().check(r);
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, V&, R r)
  {
    if ( !t.get_aspect().template get<parse::_string_>().check(r) )
      return r;

    R income =  r;
    if (!_check(++r, M().get_range() ) )
    {
      if (!r)
        throw unexpected_end_fragment();
      return income;
    }
    if (!r)
      throw unexpected_end_fragment();

    if ( *r++ != '"')
      return income;
    
    return r;
  }
};

}}}

#endif
