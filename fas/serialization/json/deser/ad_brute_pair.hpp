#ifndef FAS_DESER_JSON_DESER_AD_BRUTE_PAIR_HPP
#define FAS_DESER_JSON_DESER_AD_BRUTE_PAIR_HPP

#include <fas/serialization/json/except.hpp>
//#include <fas/serialization/json/meta/member_list.hpp>
#include <fas/serialization/json/parser/tags.hpp>

#include <fas/typemanip/some_type.hpp>
#include <fas/type_list/length.hpp>
#include <fas/type_list/type_at_c.hpp>
#include <iostream>

namespace fas{ namespace json{ namespace deser{


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
