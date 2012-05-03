#ifndef FAS_SERIALIZATION_JSON_DESER_AD_ATTR_HPP
#define FAS_SERIALIZATION_JSON_DESER_AD_ATTR_HPP

#include <fas/serialization/json/except.hpp>


namespace fas{ namespace json{ namespace deser{

struct ad_attr
{
  template<typename T, typename J, typename R>
  bool check(T& t, J, R r)
  {
    typedef typename J::target target;
    typedef typename target::deserializer_tag deserializer_tag;
    return t.get_aspect().template get<deserializer_tag>().check(t, target(), r );
  };


  template<typename T, typename J, typename V, typename R>
  R operator()(T& t, J, V& v, R r)
  {
    typedef typename J::target target;
    typedef typename target::deserializer_tag deserializer_tag;

    return t.get_aspect().template get<deserializer_tag>()(t, target(), J()(v), r );
  }
};

struct ad_prop
{
  template<typename T, typename M, typename R>
  bool check(T& t, M m, R r)
  {
    typedef typename M::target target;
    typedef typename target::deserializer_tag deserializer_tag;
    return t.get_aspect().template get<deserializer_tag>().check(t, target(), r );
  };


  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M m, V& v, R r)
  {
    typedef typename M::target target;
    typedef typename target::deserializer_tag deserializer_tag;
    typedef typename M::value_type value_type;

    value_type vt = value_type();
    r = t.get_aspect().template get<deserializer_tag>()(t, target(), vt, r );
    m.set(v, vt);
    return r;
  }
};


}}}


#endif
