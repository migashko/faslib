#ifndef FAS_SERIALIZATION_COMMON_DESER_AD_PRIMARY_LIST_T_HPP
#define FAS_SERIALIZATION_COMMON_DESER_AD_PRIMARY_LIST_T_HPP

#include <fas/serialization/common/except/try_throw.hpp>

#include <fas/type_list/erase_c.hpp>
#include <fas/type_list/type_at_c.hpp>
#include <fas/type_list/length.hpp>
#include <fas/integral/int_.hpp>

#include <fas/type_list/empty_list.hpp>

namespace fas{ namespace serialization{ namespace deser{

template<typename SepTg, typename SpaceParserTg, typename ItemListTg, typename TgExcept>
struct ad_primary_list_t
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
    
    if ( !try_t<_except_>(t) ) return r;
    
    if ( r ) 
      r = _( t, v, r, target_list(), int_<length<target_list>::value>() );
    
    return r;
  }

private:

  template<typename T, typename V, typename R>
  R _(T& t, V& v, R r, empty_list, int_<0> )
  {
    return r;
  }

  template<typename T, typename V, typename R, typename L, int N >
  R _(T& t, V& v, R r, L, int_<N> )
  {
    enum { position = length<L>::value - N };
    typedef typename type_at_c<position, L>::type target;
    
    R income = r;
    r = t.get_aspect().template get< _separator_ >()(t, target(), v, r);
    if ( !try_t<_except_>(t) ) return r;
    
    if ( r != income )
    {
      r = t.get_aspect().template get< _parse_space_ >()(t, r);
      if ( !try_t<_except_>(t) ) return r;
    }
    
    typedef typename target::deserializer_tag deserializer_tag;
    
    r = __(t, v, r, L(), int_<N>() );
    return  r ;
  }


  template<typename T, typename V, typename R, typename L, int N >
  R __(T& t, V& v, R r, L, int_<N> )
  {
    enum { position = length<L>::value - N };
    typedef typename type_at_c<position, L>::type target;
    typedef typename target::deserializer_tag deserializer_tag;
    
    R income = r;
    r = t.get_aspect().template get<deserializer_tag>()(t, target(), v, r);
    if ( r && r == income)
      return __(t, v, r, L(), int_<N-1>() );
    
    r = t.get_aspect().template get< _parse_space_ >()(t, r);
    if ( !try_t<_except_>(t) ) return r;
    
    if ( !r || !t.get_aspect().template get< _separator_ >().check(t, target(), r) )
      return r;
    
    typedef typename erase_c<position, L>::type target_list;
    
    return _(t, v, r, target_list(), int_<length<target_list>::value>() );
  }
  
  template<typename T, typename V, typename R, typename L>
  R __(T& t, V& v, R r, L, int_<0> )
  {
    r = t.get_aspect().template get< _parse_item_ >()(t, r);
    if ( !try_t<_except_>(t) ) return r;
    
    r = t.get_aspect().template get< _parse_space_>()(t, r);
    if ( !try_t<_except_>(t) ) return r;
    
    return _(t, v, r, L(), int_<length<L>::value>());
  }

};

}}}

#endif
