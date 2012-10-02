//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_RANGE_DETAIL_RANGE_HELPER_ARRAY_HPP
#define FAS_RANGE_DETAIL_RANGE_HELPER_ARRAY_HPP

#include <fas/range/typerange_flag.hpp>
#include <fas/range/random_access_range.hpp>
#include <fas/range/forward_range.hpp>
#include <fas/typemanip/type2type.hpp>
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

  static inline difference_type distance( T* )
  {
    return N;
  }

  static inline range make_range(T* v)
  {
    return range(v, static_cast<T*>(v) + N);
  }

  static inline reverse_range make_rrange(T* v)
  {
    return reverse_range( reverse_iterator(static_cast<T*>(v) + N), reverse_iterator(v) );
  }

  static inline range make_range(T* beg, T* end )
  {
    return range(beg, end);
  }

  static inline orange make_orange(T* v, bool clear = false)
  {
    typedef T type_t[N];
    if ( clear)
      _clear( v, type2type<type_t>() );
    return orange(v, v + N);
  }

  static inline range make_erange(T* v)
  {
    range r(v , v + N);
    r.advance(N);
    return r;
  }

  static inline iterator begin(T* v)
  {
    return v;
  }

  static inline iterator end(T* v)
  {
    return v + N;
  }

  static inline reverse_iterator rbegin(T* v)
  {
    return reverse_iterator(static_cast<T*>(v) + N);
  }

  static inline reverse_iterator rend(T* v)
  {
    return reverse_iterator(v);
  }

private:

  template<typename TT, typename V, int NN>
  static inline void _clear(TT* v, type2type<V[NN]> )
  {
    for (register int i = 0; i < NN; ++i)
      _clear( v[i], type2type<V>() );
  }

  template<typename TT, typename V>
  static inline void _clear(TT& v, type2type<V> )
  {
    v = V();
  }
};

}

#endif
