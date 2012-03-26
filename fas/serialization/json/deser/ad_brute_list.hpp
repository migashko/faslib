#ifndef FAS_DESER_JSON_DESER_AD_BRUTE_LIST_HPP
#define FAS_DESER_JSON_DESER_AD_BRUTE_LIST_HPP

#include <fas/serialization/json/except.hpp>
//#include <fas/serialization/json/meta/member_list.hpp>
#include <fas/serialization/json/parser/tags.hpp>

#include <fas/typemanip/some_type.hpp>
#include <fas/type_list/length.hpp>
#include <fas/type_list/type_at_c.hpp>
#include <iostream>

namespace fas{ namespace json{ namespace deser{

struct ad_brute_list
{
  template<typename T, typename M, typename R>
  bool check(T& , M, R )
  {
    return true;
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, V& v, R r)
  {
    typedef typename M::target_list target_list;
    
    for (;;)
    {
      _(t, v, r, target_list());
      r = _parse(t, r);
      r = t.get_aspect().template get< parse::_space_>()(t, r);
      if ( !r || *r!=',' ) return r;
      r = t.get_aspect().template get< parse::_space_>()(t, ++r);
      
    }
    return r;
  }
  
private:
  
  template<typename T, typename R>
  R _parse(T& t, R r)
  {
    r = t.get_aspect().template get< parse::_value_>()(t, r);
    r = t.get_aspect().template get< parse::_space_>()(t, r);
    if ( !r ) return r;
    if ( *r!=':') return r;
    r = t.get_aspect().template get< parse::_space_>()(t, ++r);
    r = t.get_aspect().template get< parse::_value_>()(t, r);
    return r;
  }
  
  template<typename T, typename V, typename R>
  void _(T&, V&, R r, empty_list ) { }

  template<typename T, typename V, typename R, typename H, typename L >
  void _(T& t, V& v, R r, type_list<H, L> )
  {
    typedef typename H::deserializer_tag deserializer_tag;
    t.get_aspect().template get<deserializer_tag>()(t, H(), v, r);
    _(t, v, r, L() );
  }
};



}}}

#endif
