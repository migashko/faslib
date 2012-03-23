#ifndef FAS_SERIALIZATION_JSON_SERIALIZER_AD_STUB_HPP
#define FAS_SERIALIZATION_JSON_SERIALIZER_AD_STUB_HPP


namespace fas{ namespace json{ namespace ser{

struct ad_stub
{
  template<typename T, typename M, typename V>
  bool check(T&, M, const V& )
  {
    return false;
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T&, M, const V&, R r)
  {
    return r;
  }
};

}}}

#endif
