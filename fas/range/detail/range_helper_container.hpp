//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

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
  typedef typename iterator2range< typename C::const_reverse_iterator >::type reverse_range;
  typedef typename C::const_reverse_iterator reverse_iterator;

  static inline range make_range(const C& ctn)
  {
    return range( ctn.begin(), ctn.end() );
  }

  static inline reverse_range make_rrange(const C& ctn)
  {
    return reverse_range( ctn.rbegin(), ctn.rend() );
  }

  static inline reverse_iterator rbegin(const C& ctn)
  {
    return reverse_iterator(ctn.end());
  }

  static inline reverse_iterator rend(const C& ctn)
  {
    return reverse_iterator(ctn.begin());
  }
};


template< typename C>
struct range_container_helper<C, false>
{
  typedef typename iterator2range< typename C::iterator >::type range;
  typedef typename iterator2range< typename C::reverse_iterator >::type reverse_range;
  typedef typename iterator2range< std::insert_iterator<C>, typename C::value_type >::type orange;
  typedef typename C::const_reverse_iterator reverse_iterator;

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

  template<typename CC>
  static inline reverse_range make_rrange(CC& ctn)
  {
    return reverse_range( ctn.rbegin(), ctn.rend() );
  }

  template<typename CC>
  static inline reverse_iterator rbegin(CC& ctn)
  {
    return reverse_iterator(ctn.end());
  }

  template<typename CC>
  static inline reverse_iterator rend(CC& ctn)
  {
    return reverse_iterator(ctn.begin());
  }

};


template< typename C>
struct range_helper<C, typerange_flag::container >
  : range_container_helper< C, is_const<C>::value  >
{
  typedef range_container_helper< C, is_const<C>::value  > super;
  enum { flag = typerange_flag::container };
  typedef typename super::range range;
  typedef typename range::difference_type   difference_type;

  template<typename CC>
  static inline range make_erange(CC& ctn)
  {
    range r = super::make_range(ctn);
    r.advance( static_cast<difference_type>( ctn.size() ) );
    return r;
  }

  static inline difference_type distance( const C& c )
  {
    return static_cast<difference_type> ( c.size() );
  }
};

}

#endif
