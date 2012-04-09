#ifndef FAS_RANGE_DETAIL_RANGE_HELPER_ARRAY_HPP
#define FAS_RANGE_DETAIL_RANGE_HELPER_ARRAY_HPP
#include <iostream>
#include <fas/range/typerange_flag.hpp>
#include <fas/range/random_access_range.hpp>
#include <fas/range/forward_range.hpp>

#include <fas/typemanip/type2type.hpp>

#include <fas/typemanip/remove_const.hpp>
#include <fas/typemanip/is_const.hpp>

#include <algorithm>
#include <iterator>

namespace fas{

template< typename T, int N>
struct range_helper<T[N], typerange_flag::array >
{
  enum
  {
    flag = typerange_flag::array
  };
  
  typedef random_access_range<T*> range;
  typedef std::reverse_iterator<T*> reverse_iterator;
  typedef T* iterator;
  typedef random_access_range< std::reverse_iterator<T*> > reverse_range;
  typedef forward_range<T*> orange;
  
  typedef typename range::difference_type   difference_type;

  //template<typename TT>
  static inline difference_type distance( T* )
  {
    return N;
  }
  
  //template<typename TT>
  static inline range make_range(T* v)
  {
    return range(v, static_cast<T*>(v) + N);
  }

  //template<typename TT>
  static inline reverse_range make_rrange(T* v)
  {
    return reverse_range( reverse_iterator(static_cast<T*>(v) + N), reverse_iterator(v) );
  }

  //template<typename TT>
  static inline range make_range(T* beg, T* end )
  {
    return range(beg, end);
  }

  /*template<typename TT>
  static inline reverse_range make_rrange(TT* beg, TT* end )
  {
    return rrange(end, beg);
  }*/

  /*template<typename TT>
  static inline orange make_orange(TT* v, bool clear = false)
  */
  static inline orange make_orange(T* v, bool clear = false)
  {
    typedef T type_t[N];
    if ( clear)
      _clear( v, type2type<type_t>() );
    return orange(v, v + N);
  }

  //template<typename TT>
  static inline range make_erange(T* v)
  {
    return range(v + N , v + N);
  }

  static inline iterator begin(T* v)
  {
    return v;
  }

  static inline iterator end(T* v)
  {
    return v + N;
  }

private:
  
  template<typename TT, typename V, int NN>
  static inline void _clear(TT* v, type2type<V[NN]> ) 
  { 
    //std::cout << "type2type<V[NN]>" << NN << std::endl;
    for (register int i = 0; i < NN; ++i)
      _clear( v[i], type2type<V>() );
  }

  template<typename TT, typename V>
  static inline void _clear(TT& v, type2type<V> )
  {
    //std::cout << "type2type<V>" << std::endl;
    v = V();
    //std::fill_n( v, N, V() );
  }
};

};

#endif
