#ifndef FAS_DESER_JSON_DESER_AD_PRIMARY_LIST_HPP
#define FAS_DESER_JSON_DESER_AD_PRIMARY_LIST_HPP

#include <fas/serialization/json/except.hpp>
#include <fas/serialization/json/parser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>

#include <fas/typemanip/some_type.hpp>
#include <fas/typemanip/tchars.hpp>
#include <fas/type_list/length.hpp>
#include <fas/type_list/type_at_c.hpp>
#include <iostream>

#include <fas/range/string_range.hpp>
namespace fas{ namespace json{ namespace deser{

template<typename SEP = tchars<','> >
struct ad_separator_t
{
	typedef SEP separator;
	typedef string_range< typename separator::value_type > range_type;
	
	template<typename T, typename M, typename R>
  bool check(T& , M, R r)
  {
		range_type rr = range_type( separator()() );
		for ( ;r && rr && *r == *rr; ++r, ++rr);
    return !rr;
  };

	template<typename T, typename M, typename V, typename R>
  R operator()(T&, M, V&, R r)
  {
		R income = r;
		range_type rr = range_type( separator()() );
		for ( ;r && rr && *r == *rr; ++r, ++rr);
		return !rr ? r : income;
	}
};

struct ad_separator: ad_separator_t<>{};

template<typename SepTg, typename SpaceParserTg, typename ItemListTg>
struct ad_primary_list_t
{
	typedef SepTg _separator_;
  typedef SpaceParserTg _parse_space_;
  typedef ItemListTg _parse_item_;
	
  template<typename T, typename M, typename R>
  bool check(T& , M, R )
  {
    return true;
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, V& v, R r)
  {
    typedef typename M::target_list target_list;
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
    if ( r != income )
      r = t.get_aspect().template get< parse::_space_>()(t, r);
    
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
    
    r = t.get_aspect().template get< parse::_space_>()(t, r);
    
    if ( !r || !t.get_aspect().template get< _separator_ >().check(t, target(), r) )
      return r;
    typedef typename erase_c<position, L>::type target_list;
    return _(t, v, r, target_list(), int_<length<target_list>::value>() );
  }
  
  template<typename T, typename V, typename R, typename L>
  R __(T& t, V& v, R r, L, int_<0> )
  {
    r = t.get_aspect().template get< parse::_item_>()(t, r);
    r = t.get_aspect().template get< parse::_space_>()(t, r);
    return _(t, v, r, L(), int_<length<L>::value>());
  }

};

struct ad_primary_list: ad_primary_list_t<_separator_, parse::_space_, parse::_item_>{};

}}}

#endif
