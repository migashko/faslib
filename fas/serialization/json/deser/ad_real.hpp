#ifndef FAS_SERIALIZATION_JSON_DESER_AD_REAL_HPP
#define FAS_SERIALIZATION_JSON_DESER_AD_REAL_HPP

#include <fas/serialization/json/except.hpp>
#include <fas/serialization/json/deser/deserialize_integer.hpp>
#include <fas/serialization/json/deser/tags.hpp>
#include <fas/serialization/json/parser/tags.hpp>

#include <sstream>
namespace fas{ namespace json{ namespace deser{

struct ad_real
{
  template<typename T, typename M, typename R>
  bool check(T& t, M, R r)
  {
    return t.get_aspect().template get<parse::_number_>().check(r)
           || t.get_aspect().template get<parse::_null_>().check(r);
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, V& v, R r)
  {
    int it_is_not_a_very_efficient_algorithm;
   // using namespace ::fas::json;
    if ( t.get_aspect().template get<parse::_null_>().check(r) )
    {
      r = t.get_aspect().template get<parse::_null_>()(t, r);
      v = V();
    }
    else if (t.get_aspect().template get<parse::_number_>().check(r))
    {
      std::stringstream ss;
      while ( r && ( (*r>='0' && *r<='9' ) || *r=='.' || *r=='-' || *r=='+' || *r=='e' || *r=='E') )
        ss << *(r++);
      ss >> v;  
    }
    return r;
  }
};

}}}

#endif
