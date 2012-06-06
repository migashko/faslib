#ifndef FAS_SERIALIZATION_COMMON_DESER_AD_SEPARATOR_T_HPP
#define FAS_SERIALIZATION_COMMON_DESER_AD_SEPARATOR_T_HPP

//#include <fas/typemanip/tchars.hpp>
#include <fas/range/string_range.hpp>

namespace fas{ namespace serialization{ namespace deser{

template<typename SEP /*= tchars<','>*/ >
struct ad_separator_t
{
	typedef SEP separator;
	typedef string_range< typename separator::value_type > range_type;
	
	template<typename T, typename M, typename R>
  bool check(T& , M, R r)
  {
		range_type rr = range_type( separator()() );
    return r && rr && *r == *rr;
		//for ( ;r && rr && *r == *rr; ++r, ++rr);
    //return !rr;
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

template<typename CharT, CharT CH>
struct ad_char_t
{
  template<typename T, typename R>
  bool check(T& t, R r) 
  {
    return r && *r == CH;
  }
  
  template<typename T, typename R>
  R operator()(T& t, R r)
  {
    return r && *r == CH ? ++r : r;
  }
  
};


}}}

#endif
