#ifndef FAS_RANGE_DETAIL_RANGE_HELPER_CONTAINER_HPP
#define FAS_RANGE_DETAIL_RANGE_HELPER_CONTAINER_HPP

#include <fas/range/iterator2range.hpp>
#include <fas/range/typerange_flag.hpp>
#include <fas/typemanip/is_const.hpp>
#include <iterator>

namespace fas{

template< typename C, int CNST>
struct range_container_helper
{
  typedef typename iterator2range< typename C::const_iterator >::type range;
  
  static inline range make_range(const C& ctn)
  {
    return range( ctn.begin(), ctn.end() );
  }
};


template< typename C>
struct range_container_helper<C, false>
{
  typedef typename iterator2range< typename C::iterator >::type range;
  typedef typename iterator2range< std::insert_iterator<C>, typename C::value_type >::type orange;
  
  template<typename CC>
  static inline orange make_orange(CC& cnt, bool clear = false)
  {
    if (clear)
      cnt.clear();
    return orange( std::inserter(cnt, cnt.end()) );
  }

  template<typename CC>
  static inline range make_range(CC& ctn)
  {
    return range( ctn.begin(), ctn.end() );
  }
};


template< typename C>
struct range_helper<C, typerange_flag::container >
  : range_container_helper< C, is_const<C>::value  >
{
  enum { flag = typerange_flag::container };
  typedef range_container_helper< C, is_const<C>::value > super;
  typedef typename super::range range;
  typedef typename range::difference_type   difference_type;

  template<typename CC>
  static inline range make_erange(CC& ctn)
  {
    return range( ctn.end(), ctn.end() );
  }

  static inline difference_type distance( const C& c )
  {
    return static_cast<difference_type> ( c.size() );
  }
};

};

#endif
