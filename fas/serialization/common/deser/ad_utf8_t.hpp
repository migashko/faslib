#ifndef FAS_SERIALIZATION_COMMON_DESER_AD_UTF8_T_HPP
#define FAS_SERIALIZATION_COMMON_DESER_AD_UTF8_T_HPP

#include <fas/serialization/common/except/try_throw.hpp>
#include <fas/serialization/common/except/unexpected_end_fragment.hpp>
#include <fas/serialization/common/except/invalid_string.hpp>
#include <fas/serialization/common/except/out_of_range.hpp>

#include <fas/range/distance.hpp>

namespace fas{ namespace serialization{ namespace deser{

template<typename TgExcept>
struct ad_utf8_t
{
  typedef TgExcept _except_;

  template<typename T, typename Rin, typename Rout>
  Rin operator()(T& t, Rin r_in, Rout& r_out)
  {
    if (!r_in)
      return throw_t<_except_>(t, unexpected_end_fragment(), r_in );

    if ( (*r_in & 128)==0 )
      *(r_out++) = *(r_in++);
    else if ( (*r_in & 224)==192 )
      return utf8_copy_n<2>(t, r_in, r_out);
    else if ( (*r_in & 240)==224 )
      return utf8_copy_n<3>(t, r_in, r_out);
    else if ( (*r_in & 248)==240 )
      return utf8_copy_n<4>(t, r_in, r_out);
    else
      return throw_t<_except_>(t, invalid_string( distance(r_in) ), r_in );
    return r_in;
  }

private:
  
  template<int N, typename T, typename Rin, typename Rout>
  Rin utf8_copy_n(T& t, Rin r_in, Rout& r_out)
  {
    for (register int i = 0; i < N; ++i)
    {
      if (!r_in)
        return throw_t<_except_>(t, unexpected_end_fragment(), r_in );

      if (!r_out)
        return throw_t<_except_>(t, out_of_range( distance(r_in) ), r_in );

      *(r_out++) = *(r_in++);
    }
    return r_in;
  }
};
  
}}}

#endif
