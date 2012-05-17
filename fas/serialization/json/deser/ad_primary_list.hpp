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

template<typename SepTag>
struct ad_primary_list_t
{
	typedef SepTag _separator_;
	
  template<typename T, typename M, typename R>
  bool check(T& , M, R )
  {
    return true;
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, V& v, R r)
  {
    typedef typename M::target_list target_list;
    r = _( t, v, r, target_list() );
    return r;
  }

private:
  
  template<typename T, typename V, typename R>
  R _(T&, V&, R r, empty_list )
  {
    return r;
  }
  
  template<typename T, typename V, typename R, typename H, typename L >
  R _(T& t,  V& v, R r, type_list<H, L> )
  {
		R income = r;
		r = t.get_aspect().template get< _separator_ >()(t, H(), v, r);
		if ( r != income )
			r = t.get_aspect().template get< parse::_space_>()(t, r);
		
    r = __(t, v, r, type_list<H, L>()  );
    return  r ;
  }

  template<typename T, typename V, typename R, typename H, typename L >
  R __(T& t,  V& v, R r, type_list<H, L> )
  {
    typedef typename H::deserializer_tag deserializer_tag;
    
    R income = r;
    r = t.get_aspect().template get<deserializer_tag>()(t, H(), v, r);
    if ( r && r == income)
      return _trouble(t, v, r, type_list<H, L>() );
    
    r = t.get_aspect().template get< parse::_space_>()(t, r);
    
    if ( !r || /**r!=','*/ !t.get_aspect().template get< _separator_ >().check(t, H(), r) )
      return r;
    return _(t, v, r, L() );
  }
  
/// ///////////////////////////////////////

  template<typename T, typename V, typename R, typename H, typename L >
  R _trouble(T& t,  V& v, R r, type_list<H, L> )
  {
    R income = r;
    int pos = 1;
    r = _0(t, v, r, L(), pos);
    if ( r && r != income)
    {
      if ( /**r == ','*/ t.get_aspect().template get< _separator_ >().check(t, H(), r) )
        r = _1(t, v, r, type_list<H, L>(), pos );
      return r;
    }
    else
    {
      r = _parse(t, r);
      return _(t, v, r, type_list<H, L>() );
    }
  }

  /// Пытаемся обойтись малой кровью
  template<typename T, typename V, typename R, typename H, typename L >
  R _0(T& t,  V& v, R r, type_list<H, L>, int& pos )
  {
    typedef typename H::deserializer_tag deserializer_tag;
    R income = r;
    r = t.get_aspect().template get<deserializer_tag>()(t, H(), v, r);
    if ( r && r == income)
      return _0(t, v, r, L(), ++pos);
    r = t.get_aspect().template get< parse::_space_>()(t, r);
    return r;
  }

  template<typename T, typename V, typename R >
  R _0(T& t,  V& v, R r, empty_list, int& pos )
  {
    return r;
  }


/// ///////////////////////////////////////
  
  // Произошло нарушение порядка полей
  template<typename T, typename V, typename R, typename H, typename L >
  R _1(T& t,  V& v, R r, type_list<H, L>, int pos )
  {
    /** Для r и H может быть три ситуации
     * 2. текущего типа в потоке нет в списке
     * 3. текущий тип в другом месте потока
     * 
     * Делаем один проход, по списку, если не нашли, то пропускаем и десериализуем в обычном режиме
     */
    enum { len = length< type_list<H, L> >::value };
    bool flags[len] = {false};
    flags[pos] = true;
    // H - уже пробовали 
    R income = _1_(t, v, r, type_list<H, L>(), flags, int_<1>(), int_<len>() );
    
    // Не нашли, пропускаем H и продолжаем
    if ( income == r)
      return _(t, v, r, L() );
    
    r = income;
    return r;
  }

  template<typename T, typename V, typename R, typename TL, int I, int N >
  R _1_(T& t,  V& v, R r, TL, bool* flags, int_<I>, int_<N> )
  {
		R income = r;
		r = t.get_aspect().template get< _separator_ >()(t, typename TL::left_type(), v, r);
		if ( r != income )
			r = t.get_aspect().template get< parse::_space_>()(t, r);

    /*if ( *r == ',' )
      r = t.get_aspect().template get< parse::_space_>()(t, ++r);
      */
		

    return _2_(t, v, r, TL(), flags, int_<I>(), int_<N>() );
  }

  template<typename T, typename V, typename R, typename TL, int I, int N >
  R _2_(T& t,  V& v, R r, TL, bool* flags, int_<I>, int_<N> )
  {
    typedef typename type_at_c< I, TL >::type current_type;
    typedef typename current_type::deserializer_tag deserializer_tag;
    R income = r;
   
    // чтобы по второму кругу не фигачить 
    if ( !flags[I]) 
    {
      r = t.get_aspect().template get<deserializer_tag>()(t, current_type(), v, r); 
    }
    else
      ;
    
    if ( r && r == income)
      return _2_(t, v, r, TL(), flags, int_<I+1>(), int_<N>() );
    
    flags[I] = true;
 
    r = t.get_aspect().template get< parse::_space_>()(t, r);

    return _3_(t, v, r, TL(), flags );
  }

  template<typename T, typename V, typename R, typename TL, int N >
  R _2_(T& t,  V& v, R r, TL, bool* flags, int_<N>, int_<N> )
  {
    // вот блин, не нашли
    // пропускаем 
    r = _parse(t, r); 
    // начинаем с начала 
    return _1_(t, v, r, TL(), flags, int_<0>(), int_<N>() ) ;
  }

  	/*R income = r;
		r = t.get_aspect().template get< _separator_ >()(t, H(), v, r);
		if ( r != income )
			r = t.get_aspect().template get< parse::_space_>()(t, r);
		*/

  template<typename T, typename V, typename R, typename TL >
  R _3_(T& t,  V& v, R r, TL, bool* flags )
  {
    r = t.get_aspect().template get< parse::_space_>()(t, r);
		if ( !r ) return r;

		R income = r;
		r = t.get_aspect().template get< _separator_ >()(t, typename TL::left_type(), v, r);
		if ( income == r )
			return r;
		r = t.get_aspect().template get< parse::_space_>()(t, r);

    /*if ( !r || *r!=',')
      return r;
    
    if ( *r == ',' )
      r = t.get_aspect().template get< parse::_space_>()(t, ++r);
		*/
		
    
    // todo: Проверить flags на предмет возобновления обычного поиска
      
    // Начинаем с начала  
    return _1_(t, v, r, TL(), flags, int_<0>(), int_< length<TL>::value >() );
  }

  template<typename T, typename R>
  R _parse(T& t, R r)
  {
    r = t.get_aspect().template get< parse::_value_>()(t, r);
    r = t.get_aspect().template get< parse::_space_>()(t, r);
    if ( !r ) return r;
    if ( *r!=':') return r;
    r = t.get_aspect().template get< parse::_space_>()(t, ++r);
    r = t.get_aspect().template get< parse::_value_>()(t, r);
    r = t.get_aspect().template get< parse::_space_>()(t, r);
    return r;
  }
};

struct ad_primary_list: ad_primary_list_t<_separator_>{};

}}}

#endif
