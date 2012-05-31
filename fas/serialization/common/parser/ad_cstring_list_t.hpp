#ifndef FAS_SERIALIZATION_COMMON_PARSER_AD_CSTRING_LIST_T_HPP
#define FAS_SERIALIZATION_COMMON_PARSER_AD_CSTRING_LIST_T_HPP

#include <fas/serialization/common/except/try_throw.hpp>
#include <fas/serialization/common/except/unexpected_end_fragment.hpp>
#include <fas/serialization/common/except/expected_of.hpp>
#include <fas/serialization/common/except/out_of_range.hpp>

#include <fas/range/orange.hpp>
#include <fas/range/distance.hpp>
#include <fas/range/srange.hpp>

#include <iostream>
namespace fas{ namespace serialization{ namespace parse{
	
template<typename SepList, typename TgExcept>
struct ad_cstring_list_t
{
	typedef TgExcept _except_;
  typedef typename normalize<SepList>::type string_list;
  
  template<typename T, typename R>
  bool check( T&, R r) 
  {
    return _check_list(r, string_list() );
  }
  
  template<typename T, typename R>
  R operator()(T& t, R r)
  {
    return _parse_list(t, r, string_list() );
  }
  
  template<typename T, typename R, typename RO>
  std::pair<R, RO> operator()(T& t, R r, RO ro)
  {
     return _copy_list(t, r, string_list(), ro );
  }
  
private:
  
  template<typename R, typename LL, typename LR>
  bool _check_list(R r, type_list<LL, LR>)
  {
    if ( _check(r, srange(LL()()) ) )
      return true;
    return _check_list( r, LR() );
  }

  template<typename R>
  bool _check_list(R r, empty_list)
  {
    return false;
  }

  template<typename R, typename RR>
  bool _check(R r, RR rr)
  {
    return r && rr && *r==*rr;
    /*for ( ;r && rr && *r==*rr; ++r, ++rr);
    return !rr;
    */
  }

  template<typename T, typename R, typename LL, typename LR>
  R _parse_list(T& t, R r, type_list<LL, LR>)
  {
    if (_check(r, srange(LL()())))
      return _parse(t, r, srange(LL()()) );
    return _parse_list( t, r, LR() );
		/*R income  = r;
		r = _parse(t, r, srange(LL()()) );
		if ( r == income )
			return _parse_list( t, r, LR() );
		return r;
    */
  }

  template<typename T, typename R>
  R _parse_list(T& t, R r, empty_list)
  {
    return throw_t<_except_>( t, expected_of( typename string_list::left_type()(), distance(r) ), r );;
  }

  template<typename T, typename R, typename RR>
  R _parse(T& t, R r, RR rr)
  {
    for ( ;r && rr && *r==*rr; ++r, ++rr);
    if (rr)                                     // ! сделать полный вывод 
      return throw_t<_except_>( t, expected_of( std::string(begin(rr), end(rr) ), distance(r) ), r );;
    return r;
  }
  
  template<typename T, typename R, typename LL, typename LR, typename RO>
  std::pair<R, RO> _copy_list(T& t, R r, type_list<LL, LR>, RO ro)
  {
    if ( _check(r, srange(LL()()) ) )
      return _copy(t, r, srange(LL()()), ro);
    return _copy_list( t, r, LR(), ro );
  }

  template<typename T, typename R, typename RO>
  std::pair<R, RO> _copy_list(T& t, R r, empty_list, RO ro)
  {
    return throw_t<_except_>( t, expected_of( typename string_list::left_type()(), distance(r) ), r, ro );
  }

  template<typename T, typename R, typename RR, typename RO>
  std::pair<R, RO> _copy(T& t, R r, RR rr, RO ro)
  {
    for ( ;r && rr && ro && *r==*rr; ++r, ++rr)
      *(ro++) = *r;
    
    if (rr && !r)
      return throw_t<_except_>( t, unexpected_end_fragment(), r, ro );

    if (rr && !ro)
      return throw_t<_except_>( t, out_of_range( distance(r) ), r, ro );

    if (rr)
      return throw_t<_except_>( t, expected_of( typename string_list::left_type()(), distance(r) ), r, ro);
    
    return std::make_pair(r, ro);
  }
};

}}}

#endif
