//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_RANGE_DETAIL_RANGE_HELPER_ITERATOR_HPP
#define FAS_RANGE_DETAIL_RANGE_HELPER_ITERATOR_HPP

#include <fas/range/iterator2range.hpp>
#include <fas/range/typerange_flag.hpp>
#include <fas/typemanip/remove_const.hpp>

#include <iterator>

namespace fas{

template< typename I>
struct range_helper<I, typerange_flag::iterator >
{
  enum { flag = typerange_flag::iterator };
  typedef typename remove_const<I>::type iterator;
  typedef typename iterator2range< iterator >::type range;

  typedef typename range::difference_type   difference_type;

  static inline range make_range(I beg)
  {
    return range(beg);
  }

  static inline range make_range(I beg, I end)
  {
    return range(beg, end);
  }

  static inline difference_type distance( iterator /*r*/ )
  {
    return 0;
  }

  template<typename Dist>
  static inline void advance( iterator& itr, Dist s)
  {
    std::advance(itr, s);
  }

};

}

#endif
