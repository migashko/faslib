#ifndef FAS_SERIALIZATION_COMMON_PARSER_AD_SEQUENCE_T_HPP
#define FAS_SERIALIZATION_COMMON_PARSER_AD_SEQUENCE_T_HPP

#include <utility>

namespace fas{ namespace serialization{ namespace parse{

template<typename TgItem, typename TgSep, typename TgSpace, typename TgExcept>
struct ad_sequence_t
{
  typedef TgItem   _item_;
  typedef TgSep    _separator_;
  typedef TgSpace  _space_;
  typedef TgExcept _except_;
  
  template<typename T, typename R>
  bool check( T&, R r) {  return true; }

  template<typename T, typename R>
  R operator()(T& t, R r)
  {
    for (;;)
    {
      if ( !r || !try_t<_except_>(t) ) return r;
      
      r = t.get_aspect().template get<_space_>()(t, r);
      
      if ( !r || !try_t<_except_>(t) ) return r;
      
      if ( t.get_aspect().template get<_item_>().check(t, r) )
        r = t.get_aspect().template get<_item_>()(t, r);
      else
        return r;

      if ( !r || !try_t<_except_>(t) ) return r;
      
      r = t.get_aspect().template get<_space_>()(t, r);
      
      if ( t.get_aspect().template get<_separator_>().check(t, r) )
        r = t.get_aspect().template get<_separator_>()(t, r);
      else
        return r;
    }
  }

  template<typename T, typename R, typename RO>
  std::pair<R, RO> operator()(T& t, R r, RO ro)
  {
    std::pair<R, RO> rr(r, ro);
    
    for (;;)
    {
      if ( !rr.first || !try_t<_except_>(t) ) return rr;
      
      rr = t.get_aspect().template get<_space_>()(t, rr.first, rr.second);

      if ( !rr.first || !try_t<_except_>(t) ) return rr;

      if ( t.get_aspect().template get<_item_>().check(t, rr.first) )
        rr = t.get_aspect().template get<_item_>()(t, rr.first, rr.second);
      else
        return rr;

      if ( !rr.first || !try_t<_except_>(t) ) return rr;
      
      rr = t.get_aspect().template get<_space_>()(t, rr.first, rr.second);

      if ( t.get_aspect().template get<_separator_>().check(t, rr.first) )
        rr = t.get_aspect().template get<_separator_>()(t, rr.first, rr.second);
      else
        return rr;
    }
  }
};

}}}

#endif
