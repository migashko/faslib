#ifndef FAS_SERIALIZATION_COMMON_DESER_AD_JSONBASE_STRING_T_HPP
#define FAS_SERIALIZATION_COMMON_DESER_AD_JSONBASE_STRING_T_HPP

#include <fas/serialization/common/except/try_throw.hpp>
#include <fas/serialization/common/except/out_of_range.hpp>

#include <fas/typemanip/is_array.hpp>
#include <fas/range/range.hpp>
#include <fas/range/orange.hpp>
#include <fas/range/distance.hpp>
#include <fas/integral/bool_.hpp>

namespace fas{ namespace serialization{ namespace deser{

template<typename TgSep, typename TgUtf8, typename TgEscape, typename TgExcept>
struct ad_jsonbase_string_t
{
  typedef TgUtf8 _utf8_;
  typedef TgSep _separator_;
  typedef TgEscape _escape_;
  typedef TgExcept _except_;
  
  template<typename T, typename M, typename R>
  bool check(T& t, M, R r)
  {
    return true;
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, V& v, R r)
  {
    return _(t, M(), v, r, bool_<is_array<V>::value> () );
  }

private:
    
  template<typename T, typename M, typename V, typename R, typename ISA>
  R _(T& t, M, V& v, R r, ISA)
  {
    typename typerange<V>::orange ro = orange(v, true);
    return __(t, M(), ro, r);
  }

  template<typename T, typename M, typename V, typename R>
  R _(T& t, M, V* v, R r, false_)
  {
    if ( !v )
      return throw_t<_except_>(t, out_of_range( distance(r) ), r );
    
    typename typerange<V*>::range ro = range(v, v + M::limit );
    r = __(t, M(), ro, r);
    
    if ( !try_t<_except_>(t) ) 
      return r;
    
    if ( !ro )
      return throw_t<_except_>(t, out_of_range( distance(r) ), r );
    
    *(ro++) = '\0';
    
    return r;
  }

  template<typename T, typename M, typename Rout, typename Rin >
  Rin __( T& t, M, Rout& r_out, Rin r_in  )
  {
    for ( ;r_in && try_t<_except_>(t) ; )
    {
      if (!r_out)
        return throw_t<_except_>(t, out_of_range( distance(r_in) ), r_in );

      if ( t.get_aspect().template get<_separator_>().check(t, M(), r_in) )
        return r_in;
      
      if ( t.get_aspect().template get<_escape_>().check(r_in) )
        r_in = t.get_aspect().template get<_escape_>()(t, r_in, r_out);
      else
        r_in = t.get_aspect().template get<_utf8_>()(t, r_in, r_out);
    };
    return r_in;
  };
};


}}}

#endif
