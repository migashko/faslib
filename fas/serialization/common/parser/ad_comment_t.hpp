#ifndef FAS_SERIALIZATION_COMMON_PARSER_AD_COMMET_T_HPP
#define FAS_SERIALIZATION_COMMON_PARSER_AD_COMMET_T_HPP

#include <fas/serialization/common/except/try_throw.hpp>
#include <fas/serialization/common/except/unexpected_end_fragment.hpp>
#include <fas/serialization/common/except/expected_of.hpp>
#include <fas/serialization/common/except/out_of_range.hpp>

#include <fas/range/distance.hpp>
#include <fas/range/srange.hpp>
#include <fas/range/string_range.hpp>

namespace fas{ namespace serialization{ namespace parse{
	
template<typename TgBegComment, typename TgEndComment, typename TgExcept>
struct ad_comment_t
{
	typedef TgExcept _except_;
  typedef TgBegComment _begin_comment_;
  typedef TgEndComment _end_comment_;
  
  template<typename T, typename R>
  bool check(T& t, R r)
  {
    return t.get_aspect().template get<_begin_comment_>().check(t, r);
  }
  
  template<typename T, typename R>
  R operator()(T& t, R r)
  {
    r = t.get_aspect().template get<_begin_comment_>()(t, r);
    for ( ; r ; ++r)
    {
      if ( t.get_aspect().template get<_end_comment_>().check(t, r) )
      {
        r = t.get_aspect().template get<_end_comment_>()(t, r);
        return r;
      }
    }
    return throw_t<_except_>( t, unexpected_end_fragment( distance(r) ), r );
  }
  
  template<typename T, typename R, typename RO>
  std::pair<R, RO> operator()(T& t, R r, RO ro)
  {
    return std::make_pair( (*this)(t, r), ro );
  }
  
};

}}}

#endif
