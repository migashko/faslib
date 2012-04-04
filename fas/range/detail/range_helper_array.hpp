#ifndef FAS_RANGE_DETAIL_RANGE_HELPER_ARRAY_HPP
#define FAS_RANGE_DETAIL_RANGE_HELPER_ARRAY_HPP

#include <fas/range/typerange_flag.hpp>
#include <fas/range/random_access_range.hpp>

#include <fas/typemanip/type2type.hpp>

#include <fas/typemanip/remove_const.hpp>
#include <fas/typemanip/is_const.hpp>

#include <algorithm>

namespace fas{

template< typename T, int N>
struct range_helper<T[N], typerange_flag::array >
{
  enum
  {
    flag = typerange_flag::array
    
  };
  
  typedef random_access_range<T*> range;
  typedef random_access_range< std::reverse_iterator<T*> > rrange;
  typedef range orange;
  
  typedef typename range::difference_type   difference_type;

  template<typename TT>
  static inline difference_type distance( TT* )
  {
    return N;
  }
  
  template<typename TT>
  static inline range make_range(TT* v)
  {
    return range(v, static_cast<TT*>(v) + N);
  }

  template<typename TT>
  static inline rrange make_rrange(TT* v)
  {
    return rrange(static_cast<TT*>(v) + N - 1 , v - 1 );
  }

  template<typename TT>
  static inline range make_range(TT* beg, TT* end )
  {
    return range(beg, end);
  }

  template<typename TT>
  static inline range make_rrange(TT* beg, TT* end )
  {
    return rrange(end, beg);
  }

  template<typename TT>
  static inline orange make_orange(TT* v, bool clear = false)
  {
    if ( clear)
      _clear( v, type2type<TT>() );
    return range(v, v + N);
  }

  template<typename TT>
  static inline range make_erange(TT* v)
  {
    return range(v + N , v + N);
  }


private:
  
  template<typename TT, typename V, int NN>
  static inline void _clear(TT* v, type2type<V[NN]> ) { }

  template<typename TT, typename V>
  static inline void _clear(TT* v, type2type<V> )
  {
    std::fill_n( v, N, V() );
  }
};

};

#endif
