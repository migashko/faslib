#ifndef FAS_SERIALIZATION_COMMON_PARSER_AD_SPACE_T_HPP
#define FAS_SERIALIZATION_COMMON_PARSER_AD_SPACE_T_HPP

#include <fas/serialization/common/except/try_throw.hpp>
#include <fas/serialization/common/except/unexpected_end_fragment.hpp>
#include <fas/serialization/common/except/expected_of.hpp>
#include <fas/serialization/common/except/out_of_range.hpp>

#include <fas/range/distance.hpp>
#include <fas/range/srange.hpp>
#include <fas/range/string_range.hpp>

namespace fas{ namespace serialization{ namespace parse{
	
template<typename TgSpaceChars, typename TgComment, typename TgExcept>
struct ad_space_t
{
	typedef TgExcept     _except_;
  typedef TgSpaceChars _space_;
  typedef TgComment    _comment_;
  
  template<typename T, typename R>
  bool check(T& t, R r)
  {
    return t.get_aspect().template get<_space_>().check(t, r)
        || t.get_aspect().template get<_comment_>().check(t, r);
  }
  
  template<typename T, typename R>
  R operator()(T& t, R r)
  {
    for (;;)
    {
      if ( t.get_aspect().template get<_space_>().check(t, r) )
        r = t.get_aspect().template get<_space_>()(t, r);
      else if (t.get_aspect().template get<_comment_>().check(t, r) )
        r = t.get_aspect().template get<_comment_>()(t, r);
      else
        return r;
    }
  }
  
  template<typename T, typename R, typename RO>
  std::pair<R, RO> operator()(T& t, R r, RO ro)
  {
    return std::make_pair( (*this)(t, r), ro );
  }
};

}}}

#endif
