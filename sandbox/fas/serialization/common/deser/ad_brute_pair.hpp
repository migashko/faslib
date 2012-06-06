#ifndef FAS_SERIALIZATION_COMMON_DESER_AD_BRUTE_PAIR_HPP
#define FAS_SERIALIZATION_COMMON_DESER_AD_BRUTE_PAIR_HPP

namespace fas{ namespace serialization{ namespace deser{

struct ad_brute_pair
{
  template<typename T, typename M, typename R>
  bool check(T& t, M, R r )
  {
    return true;
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M , V& v, R r)
  {
    typedef typename M::first_target first_target;
    typedef typename M::second_target second_target;
    
    typedef typename first_target::deserializer_tag first_tag;
    typedef typename second_target::deserializer_tag second_tag;
    
    t.get_aspect().template get<first_tag>()(t, first_target(), v, r);
    r = t.get_aspect().template get<second_tag>()(t, second_target(), v, r);
    return r;
  }
};


}}}

#endif
