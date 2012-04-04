#ifndef FAS_RANGE_DETAIL_RANGE_HELPER_OTHER_HPP
#define FAS_RANGE_DETAIL_RANGE_HELPER_OTHER_HPP

#include <fas/range/typerange_flag.hpp>
#include <fas/range/random_access_range.hpp>

namespace fas{

template< typename T>
struct range_helper<T, typerange_flag::other >
{
  enum { flag = typerange_flag::other };
  typedef random_access_range<T*> range;
  typedef range orange;
  
  typedef typename range::difference_type difference_type;

  template<typename TT>
  static inline range make_range(TT& v)
  {
    return range(&v, &v + 1);
  }

  template<typename TT>
  static inline orange make_orange(TT& v, bool clear = false)
  {
    if ( clear )
      v = T();
    return orange(&v, &v + 1);
  }

  template<typename TT>
  static inline range make_erange(TT& v)
  {
    return range(&v + 1, &v + 1);
  }

  template<typename TT>
  static inline difference_type distance( const TT& )
  {
    return 1;
  }
};

};

#endif
