#ifndef FAS_RANGE_DETAIL_RANGE_HELPER_ITERATOR_HPP
#define FAS_RANGE_DETAIL_RANGE_HELPER_ITERATOR_HPP

#include <fas/range/iterator2range.hpp>
#include <fas/range/typerange_flag.hpp>
#include <iterator>

namespace fas{

template< typename I>
struct range_helper<I, typerange_flag::iterator >
{
  enum { flag = typerange_flag::iterator };
  typedef typename remove_const<I>::type iterator;
  //typedef typename std::reverse_iterator<iterator> reverse_iterator; 
  typedef typename iterator2range< iterator >::type range;
  //typedef typename iterator2range< reverse_iterator >::type rrange;
  typedef typename range::difference_type   difference_type;

  // only for output iterator
  static inline range make_range(I beg)
  {
    return range(beg);
  }

  static inline range make_range(I beg, I end)
  {
    return range(beg, end);
  }

  // rrange( v.begin(), v.end() ) <=> range( v.rbegin(), v.rend() )
  /*static inline rrange make_rrange(I beg, I end)
  {
    return rrange(end, beg);
  }
  */

  static inline difference_type distance( I r )
  {
    return 0;
  }
};

};

#endif
