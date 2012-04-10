#ifndef FAS_RANGE_DETAIL_RANGE_HELPER_POINTER_HPP
#define FAS_RANGE_DETAIL_RANGE_HELPER_POINTER_HPP

#include <fas/range/random_access_range.hpp>
#include <fas/range/typerange_flag.hpp>

namespace fas{

template< typename T>
struct range_helper<T*, typerange_flag::pointer >
{
  enum { flag = typerange_flag::pointer };
  typedef random_access_range<T*> range;
  typedef typename range::difference_type   difference_type;
  typedef typename range::reverse_range     reverse_range;

  template<typename TT>
  static inline range make_range(TT* beg, TT* end )
  {
    return range(beg, end);
  }

  /*
  template<typename TT>
  static inline range make_erange(TT* end )
  {
    return range(end, end);
  }
  */

  static inline difference_type distance( const T& )
  {
    return 0;
  }
};

};

#endif
