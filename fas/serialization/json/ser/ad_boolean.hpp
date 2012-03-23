#ifndef FAS_SERIALIZATION_JSON_SER_AD_BOOLEAN_HPP
#define FAS_SERIALIZATION_JSON_SER_AD_BOOLEAN_HPP

#include <fas/serialization/json/except/try_throw.hpp>
#include <fas/serialization/json/except/out_of_range.hpp>

namespace fas{ namespace json{ namespace ser{

struct ad_boolean
{
  template<typename T, typename M, typename V>
  bool check(T&, M, V )
  {
    return true;
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, V v, R r)
  {
    if ( v )
    {
      r = _(t, 't', r);
      r = _(t, 'r', r);
      r = _(t, 'u', r);
      r = _(t, 'e', r);
    }
    else
    {
      r = _(t, 'f', r);
      r = _(t, 'a', r);
      r = _(t, 'l', r);
      r = _(t, 's', r);
      r = _(t, 'e', r);
    }

    return r;
  }

private:
  template<typename T, typename R>
  R _(T& t, char ch, R r)
  {
    if (!r)
      return throw_(t, out_of_range(), r);
    *r=ch;
    ++r;
    return r;
  }
};

}}}


#endif
