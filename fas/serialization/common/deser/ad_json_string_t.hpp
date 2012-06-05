#ifndef FAS_SERIALIZATION_COMMON_DESER_AD_JSON_STRING_T_HPP
#define FAS_SERIALIZATION_COMMON_DESER_AD_JSON_STRING_T_HPP

#include <fas/serialization/common/except/try_throw.hpp>
#include <fas/serialization/common/except/unexpected_end_fragment.hpp>
#include <fas/serialization/common/except/invalid_string.hpp>
#include <fas/serialization/common/except/expected_of.hpp>

#include <fas/range/orange.hpp>
#include <fas/range/distance.hpp>

namespace fas{ namespace serialization{ namespace deser{

template<typename TgContentString, typename TgQuotes,  typename TgParseString, typename TgParseNull, typename TgExcept>
struct ad_json_string_t
{
	typedef TgContentString _content_string_;
  typedef TgQuotes _quote_;
  typedef TgParseString _parse_string_;
  typedef TgParseNull _parse_null_;
	typedef TgExcept _except_;
  
  template<typename T, typename M, typename R>
  bool check(T& t, M, R r)
  {
    return t.get_aspect().template get<_parse_string_>().check(t, r)
           || t.get_aspect().template get<_parse_null_>().check(t, r);

  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, V& v, R r)
  {
    if ( t.get_aspect().template get<_parse_null_>().check(t, r) )
    {
      _clear(v);
      return t.get_aspect().template get<_parse_null_>()(t, r);
    }
    
    if ( !t.get_aspect().template get<_parse_string_>().check(t, r) )
      return r;
    
    // typedef typename T::aspect::template advice_cast<_quote_>::type::separator separator;

    if (!r)
      return throw_t<_except_>(t, unexpected_end_fragment(), r );

    if ( !t.get_aspect().template get<_quote_>().check(t, /*M(),*/ r) )
      return throw_t< _except_ >( t, expected_of( /*separator()()*/'"', distance(r) ), r );
    /*R beg_string = r;
    r = t.get_aspect().template get<_quote_>()(t, r);
    R income = r;
    r = t.get_aspect().template get<_content_string_>()(t, M(), v, r);
    if ( r == income )
      return t.get_aspect().template get<_parse_string_>()(t, beg_string);
    */
      
    r = t.get_aspect().template get<_quote_>()(t, r);
    r = t.get_aspect().template get<_content_string_>()(t, M(), v, r);
    if (!r)
      return throw_t<_except_>(t, unexpected_end_fragment(), r );
    if ( !t.get_aspect().template get<_quote_>().check(t, /*M(),*/ r) )
      return throw_t< _except_ >( t, expected_of( /*separator()()*/'"', distance(r) ), r );
    r = t.get_aspect().template get<_quote_>()(t, /*M(), v,*/ r);
    
    return r;
  }
  
private:
  
  template<typename V>
  void _clear(V* v)  { if (v) v[0]='\0'; }

  template<typename V>
  void _clear(V& v)  { orange(v, true); }
};

}}}

#endif
