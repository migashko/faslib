#ifndef FAS_SERIALIZATION_JSON_DESER_AD_INTEGER_HPP
#define FAS_SERIALIZATION_JSON_DESER_AD_INTEGER_HPP

/*#include <fas/serialization/json/except.hpp>
#include <fas/serialization/json/deser/deserialize_integer.hpp>
*/
#include <fas/serialization/json/deser/tags.hpp>
#include <fas/serialization/json/parser/tags.hpp>

namespace fas{ namespace json{ namespace deser{

struct ad_integer
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
    using namespace ::fas::json;
    if ( t.get_aspect().template get<parse::_null_>().check(r) )
    {
      r = t.get_aspect().template get<parse::_null_>()(t, r);
      v = V();
    }
    else if ( t.get_aspect().template get<parse::_number_>().check(r) )
    {
      r = _(v, r);
    }
    return r;
  }

private:

  template<typename V, typename R >
  R _( V& v, R r )
  {
    if( !r )
      return r;

    v = 0;

    register bool neg = *r=='-';

    if ( neg ) ++r;

    if ( !r || *r < '0' || *r > '9')
      return r;

    // цифры с первым нулем запрещены (напр 001), только 0
    
    if (*r=='0')
      return ++r;

    for ( ;r; ++r )
    {
      if (*r < '0' || *r > '9')
        break;
      v = v*10 + (*r- '0');
    }

    if (neg) v*=-1;
    
    return r;
  }

};

}}}

#endif
