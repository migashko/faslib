#ifndef FAS_SERIALIZATION_COMMON_DESER_AD_JSON_ESCAPE_T_HPP
#define FAS_SERIALIZATION_COMMON_DESER_AD_JSON_ESCAPE_T_HPP

#include <fas/serialization/common/except/try_throw.hpp>
#include <fas/serialization/common/except/out_of_range.hpp>
#include <fas/serialization/common/except/unexpected_end_fragment.hpp>
#include <fas/serialization/common/except/invalid_string.hpp>

namespace fas{ namespace serialization{ namespace deser{

template<typename TgUhex, typename TgExcept>
struct ad_json_escape_t
{
  typedef TgUhex   _json_uhex_;
  typedef TgExcept _except_;
  template<typename R>
  bool check(R r)
  {
    return *r=='\\';
  }

  template<typename T, typename Rin, typename Rout>
  Rin operator()( T& t, Rin r_in, Rout& r_out)
  {
    if ( !r_in )
      return r_in;
    
    if (*r_in!='\\')
      return r_in;

    if (!(++r_in))
      return throw_t<_except_>(t, unexpected_end_fragment(), r_in );

    switch (*r_in)
    {
      case '"' :
      case '\\':
      case '/' : *(r_out++) = *r_in; ++r_in; break;
      case 't':  *(r_out++) = '\t';  ++r_in; break;
      case 'b':  *(r_out++) = '\b';  ++r_in; break;
      case 'r':  *(r_out++) = '\r';  ++r_in; break;
      case 'n':  *(r_out++) = '\n';  ++r_in; break;
      case 'f':  *(r_out++) = '\f';  ++r_in; break;
      case 'u':  r_in = t.get_aspect().template get<_json_uhex_>()(t,  ++r_in, r_out); break;
      default:
        return throw_t<_except_>(t, invalid_string( distance(r_in) ), r_in );
    } // case

    return r_in;
  }
};


}}}

#endif
