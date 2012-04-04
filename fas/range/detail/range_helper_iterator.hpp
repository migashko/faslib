#ifndef FAS_RANGE_DETAIL_RANGE_HELPER_ITERATOR_HPP
#define FAS_RANGE_DETAIL_RANGE_HELPER_ITERATOR_HPP

#include <fas/range/iterator2range.hpp>
#include <fas/range/typerange_flag.hpp>

namespace fas{

template< typename I>
struct range_helper<I, typerange_flag::iterator >
{
  enum { flag = typerange_flag::iterator };
  typedef typename iterator2range< typename remove_const<I>::type >::type range;
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

  static inline difference_type distance( I r )
  {
    return 0;
  }
};

};

#endif
