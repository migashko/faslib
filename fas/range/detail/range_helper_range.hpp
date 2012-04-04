#ifndef FAS_RANGE_DETAIL_RANGE_HELPER_RANGE_HPP
#define FAS_RANGE_DETAIL_RANGE_HELPER_RANGE_HPP

#include <fas/range/typerange_flag.hpp>

namespace fas{

template< typename R>
struct range_helper<R, typerange_flag::range >
{
  enum { flag = typerange_flag::range };
  typedef R range;
  typedef typename range::difference_type   difference_type;

  static inline range make_range(R r)
  {
    return r;
  }

  static inline range make_orange(R r, bool clear)
  {
    if ( clear )
      for ( R i = r; i ; ++i) *i = typename R::value_type();
    return r;
  }

  static inline range make_erange(R r)
  {
    return range( r.end() , r.end() );
  }

  static inline difference_type distance( R r )
  {
    return r.distance();
  }
};


};

#endif
