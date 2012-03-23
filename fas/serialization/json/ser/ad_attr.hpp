#ifndef FAS_SERIALIZATION_JSON_SER_AD_ATTR_HPP
#define FAS_SERIALIZATION_JSON_SER_AD_ATTR_HPP

namespace fas{ namespace json{ namespace ser{

struct ad_attr
{
  template<typename T, typename M, typename V>
  bool check(T& t, M m, const V& v)
  {
    typedef typename M::target target;
    typedef typename target::serializer_tag serializer_tag;

    return t.get_aspect().template get<serializer_tag>().check(t, target(), m.ref(v) );
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M m, const V& v, R r)
  {
    typedef typename M::target target;
    typedef typename target::serializer_tag serializer_tag;

    return t.get_aspect().template get<serializer_tag>()(t, target(), m.ref(v), r );
  }
};

struct ad_prop
{
  template<typename T, typename M, typename V>
  bool check(T& t, M m, const V& v)
  {
    typedef typename M::target target;
    typedef typename target::serializer_tag serializer_tag;

    return t.get_aspect().template get<serializer_tag>().check(t, target(), m.get(v) );
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M m, const V& v, R r)
  {
    typedef typename M::target target;
    typedef typename target::serializer_tag serializer_tag;

    return t.get_aspect().template get<serializer_tag>()(t, target(), m.get(v), r );
    
  }
};

}}}


#endif
