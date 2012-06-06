#ifndef FAS_SERIALIZATION_COMMON_PARSER_AD_AD_ENCLOSED_T_HPP
#define FAS_SERIALIZATION_COMMON_PARSER_AD_AD_ENCLOSED_T_HPP

#include <fas/serialization/common/except/try_throw.hpp>
#include <fas/serialization/common/except/unexpected_end_fragment.hpp>
#include <fas/serialization/common/except/expected_of.hpp>
#include <fas/serialization/common/except/out_of_range.hpp>

#include <utility>

namespace fas{ namespace serialization{ namespace parse{

template<typename TgOpen, typename TgItem, typename TgClose, typename TgExcept>
struct ad_enclosed_t
{
  typedef TgOpen    _open_;
  typedef TgItem    _item_;
  typedef TgClose   _close_;
  typedef TgExcept  _except_;
  
  template<typename T, typename R>
  bool check( T& t, R r) 
  {
    return t.get_aspect().template get<_open_>().check(t, r); 
  }

  template<typename T, typename R>
  R operator()(T& t, R r)
  {
    if ( !r )
      return throw_t<_except_>( t, unexpected_end_fragment(), r );
    r = t.get_aspect().template get<_open_>()(t, r);
    if ( !try_t<_except_>(t) ) return r;
    r = t.get_aspect().template get<_item_>()(t, r);
    if ( !try_t<_except_>(t) ) return r;
    return t.get_aspect().template get<_close_>()(t, r);
  }

  /*
  template<typename T, typename R, typename RO>
  std::pair<R, RO> operator()(T& t, R r, RO ro)
  {
    std::pair<R, RO> rr(r, ro);

   if ( !rr.first )
      return throw_t<_except_>( t, unexpected_end_fragment(), rr.first, rr.second );
    
    rr = t.get_aspect().template get<_open_>()(t, rr.first, rr.second);
    
    if ( !try_t<_except_>(t) ) return rr;
    
    rr = t.get_aspect().template get<_item_>()(t, rr.first, rr.second);
    
    if ( !try_t<_except_>(t) ) return rr;
    
    return t.get_aspect().template get<_close_>()(t, rr.first, rr.second);
  }
  */
};

}}}

#endif
