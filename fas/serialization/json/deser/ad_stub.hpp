#ifndef FAS_SERIALIZATION_JSON_DESER_AD_STUB_HPP
#define FAS_SERIALIZATION_JSON_DESER_AD_STUB_HPP

namespace fas{ namespace json{ namespace deser{

struct ad_stub
{
  template<typename T, typename M, typename R>
  bool check(T&, M, R )
  {
    return false;
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T&, M, V&, R r)
  {
    return r;
  }
};

}}}

#endif
