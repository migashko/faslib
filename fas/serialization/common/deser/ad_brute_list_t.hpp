#ifndef FAS_SERIALIZATION_COMMON_DESER_AD_BRUTE_LIST_T_HPP
#define FAS_SERIALIZATION_COMMON_DESER_AD_BRUTE_LIST_T_HPP

#include <fas/serialization/common/except/try_throw.hpp>

#include <fas/type_list/empty_list.hpp>
#include <fas/type_list/type_list.hpp>

#include <iostream>
namespace fas{ namespace serialization{ namespace deser{

template<typename SepTg, typename SpaceParserTg, typename ItemListTg, typename TgExcept>
struct ad_brute_list_t
{
  typedef SepTg _separator_;
  typedef SpaceParserTg _parse_space_;
  typedef ItemListTg _parse_item_;
  typedef TgExcept _except_;

  template<typename T, typename M, typename R>
  bool check(T& , M, R )
  {
    return true;
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, V& v, R r)
  {
    typedef typename M::target_list target_list;

    r = t.get_aspect().template get< _parse_space_ >()(t, r);
    if ( !r || !try_t<_except_>(t) ) return r;

    R income = r;
    r = t.get_aspect().template get< _separator_ >()(t, target_list                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             (), v, r);
    if ( !r || !try_t<_except_>(t) ) return r;
    
    if ( r != income )
    {
      r = t.get_aspect().template get< _parse_space_ >()(t, r);
      if ( !r || !try_t<_except_>(t) ) return r;
    }

    _(t, v, r, target_list());
    
    for (; try_t<_except_>(t) && r;)
    {
      r = t.get_aspect().template get< _parse_item_ >()(t, r);
      if ( !try_t<_except_>(t) ) return r;
      
      r = t.get_aspect().template get< _parse_space_ >()(t, r);
      if ( !try_t<_except_>(t) ) return r;
      if ( !r ) return r;
      
      R income = r;
      r = t.get_aspect().template get< _separator_ >()(t, M(), v, r);
      if ( income == r || !r || !try_t<_except_>(t) )
        return r;
      
      r = t.get_aspect().template get< _parse_space_ >()(t, r);
    }
    return r;
  }
  
private:
  
  template<typename T, typename V, typename R>
  void _(T&, V&, R r, empty_list ) {}

  template<typename T, typename V, typename R, typename H, typename L >
  void _(T& t, V& v, R r, type_list<H, L> )
  {
    
    typedef typename H::deserializer_tag deserializer_tag;
    R current = r;
    for (;;)
    {
      
      R income = current;
      current = t.get_aspect().template get<deserializer_tag>()(t, H(), v, current);
      if (current == income)
        current = t.get_aspect().template get< _parse_item_ >()(t, current);
      current = t.get_aspect().template get< _parse_space_ >()(t, current);
      if ( !current || !t.get_aspect().template get< _separator_ >().check(t, H(), current) )
        break;
      current = t.get_aspect().template get< _separator_ >()(t, H(), v, current);
      current = t.get_aspect().template get< _parse_space_ >()(t, current);
      
    }
    _(t, v, r, L() );
  }

  template<typename T, typename V, typename R, typename L >
  void _(T& t, V& v, R r, L )
  {
    
    typedef typename L::left_type head;
    typedef typename L::right_type tail;
    _(t, v, r, type_list<head, tail>() );
  }
};
  

}}}

#endif
