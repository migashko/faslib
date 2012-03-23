#ifndef FASrange_DETAIL_RANGE_TRAITS_HPP
#define FASrange_DETAIL_RANGE_TRAITS_HPP

#include <fas/range/output_range.hpp>
#include <fas/range/forward_range.hpp>
#include <fas/range/input_range.hpp>
#include <fas/range/string_range.hpp>
#include <fas/range/random_access_range.hpp>
#include <fas/range/bidirectional_range.hpp>

#include <fas/typemanip/has_typename.hpp>
#include <fas/typemanip/has_member_function.hpp>
#include <fas/integral/int_.hpp>


namespace fas{ namespace detail{
  
FAS_HAS_TYPENAME(has_iterator_category, iterator_category);
FAS_HAS_TYPENAME(has_iterator, iterator);
FAS_HAS_TYPENAME(has_const_iterator, const_iterator);

/*
FAS_HAS_MEMBER_FUNCTION2(has_insert, insert, typename T::iterator, typename T::iterator, const typename T::value_type&)
FAS_HAS_MEMBER_FUNCTION1(has_push_back, push_back, void, const typename T::value_type&)
FAS_HAS_MEMBER_FUNCTION1(has_append, append, T&, const typename T::value_type*)
*/


/// ///////////////////////////////////////
/// iterators range
/// ///////////////////////////////////////

template<typename T, typename Tg>
struct iterator_range_helper;

template<typename T>
struct iterator_range_helper<T, std::input_iterator_tag>
{
  typedef input_range<T> range_type;
};

template<typename T>
struct iterator_range_helper<T, std::output_iterator_tag>
{
  typedef output_range<T> range_type;
};

template<typename T>
struct iterator_range_helper<T, std::forward_iterator_tag>
{
  typedef forward_range<T> range_type;
};

template<typename T>
struct iterator_range_helper<T, std::bidirectional_iterator_tag>
{
  typedef bidirectional_range<T> range_type;
};

template<typename T>
struct iterator_range_helper<T, std::random_access_iterator_tag>
{
  typedef random_access_range<T> range_type;
};


template<typename T>
struct iterator_range
  : iterator_range_helper<T, typename std::iterator_traits<T>::iterator_category > 
{

};


template<typename T, int>
struct range_traits_impl0;

template<typename T, int>
struct range_traits_impl1;

template<typename T>
struct range_traits_impl_cont;

template<typename T>
struct range_traits_impl2;

/// ///////////////////////////////////////
template<typename T>
struct range_traits_helper
  : range_traits_impl0< T, has_iterator_category< T >::value >
{
};


/// STL iterator or ...

template<typename T>
struct remove_const { typedef T type; };

template<typename T>
struct remove_const<const T> { typedef T type; };

template<typename T, int>
struct range_traits_impl0
  : iterator_range< typename remove_const<T>::type >
{
  /*
  enum { is_array = false };
  enum { is_associative_container = false };
  enum { is_sequence_container = false };
  */

  typedef typename remove_const<T>::type iterator_type;
  typedef iterator_range< iterator_type > super;
  typedef typename super::range_type range_type;

  static range_type (iterator_type beg) { return range_type( beg ); }

  static range_type (iterator_type beg, iterator_type end) { return range_type( beg, end ); }
};

template<typename T>
struct range_traits_impl0<T, false>
  : range_traits_impl1< T, has_iterator< T >::value || has_const_iterator< T >::value  >
{
  
};

/// STL container or ...

template<typename T>
struct range_traits_impl_initial
{
  typedef typename iterator_range< std::insert_iterator<T> >::range_type initial_range_type;
  
  static inline initial_range_type make_initial_range(T& cnt) 
  {
    return initial_range_type( std::inserter(cnt, cnt.end()) );
  }

};

template<typename T, int N>
struct range_traits_impl_initial< T[N] >
{
  // array
  typedef iterator_range< T* > iter_range;
  typedef typename iter_range::range_type initial_range_type;
  typedef typename initial_range_type::pointer initial_pointer;
  
  static inline initial_range_type make_initial_range(initial_pointer beg) 
  {
    return initial_range_type(beg, beg + N); 
    
  }
};


template<typename T, int>
struct range_traits_impl1
  : range_traits_impl_cont< T >
  , range_traits_impl_initial<T>
{
  /*
  enum { is_array = false };
  enum { is_sequence_container = has_push_back<T>::value };
  enum { is_associative_container = has_insert<T>::value && !has_push_back<T>::value };
  enum { is_std_string = has_append<T>::value  };
  */
  

};

template<typename T>
struct range_traits_impl1<T, false>
  : range_traits_impl2< T >
{
  
};

template<typename T>
struct range_traits_impl_cont
  : iterator_range< typename T::iterator >
{
  typedef iterator_range< typename T::iterator > super;
  typedef typename super::range_type range_type;
  
  template<typename Cnt>
  static inline range_type (Cnt& cnt) { return range_type(cnt.begin(), cnt.end()); }

};

template<typename T>
struct range_traits_impl_cont<const T>
  : iterator_range< typename T::const_iterator >
{
  typedef iterator_range< typename T::const_iterator > super;
  typedef typename super::range_type range_type;

  template<typename Cnt>
  static inline range_type (Cnt& cnt) { return range_type(cnt.begin(), cnt.end()); }
  
};


/// Array or pointer

template<typename T, int N>
struct range_traits_impl2<T[N]>
  : iterator_range< T* >
  , range_traits_impl_initial<T[N] >
{
  /*
  enum { is_array = true };
  enum { is_associative_container = false };
  enum { is_sequence_container = false };
  */
  typedef iterator_range< T* > super;
  typedef typename super::range_type range_type;
  typedef typename range_type::pointer pointer;
  
  static inline range_type (pointer beg) { return range_type(beg, beg + N); }
  
  static inline range_type (pointer beg, pointer end) { return range_type(beg, end); }

};

template<typename T>
struct range_traits_impl2
  : iterator_range< T >
{
  /*
  enum { is_array = false };
  enum { is_associative_container = false };
  enum { is_sequence_container = false };
  */
  
  typedef iterator_range< T > super;
  typedef typename super::range_type range_type;
  typedef typename range_type::pointer pointer;
  
  static inline range_type (pointer beg, pointer end) { return range_type(beg, end); }
};
  
} // namespace detail
  
template<typename T>
struct range_traits;

namespace detail
{
  
  /*
template<typename AR>
struct array_size
{
  enum { value = -1};
};

template<typename A, int N>
struct array_size<A[N]>
{
  enum { value = N};
};

template<typename AR, typename T, int>
struct _impl;

template<typename AR, typename T>
struct _helper
  : _impl<AR, T, array_size<AR>::value>
{
  
};

template<typename AR, typename T>
struct _impl<AR, T, -1>
{
  typedef typename range_traits<AR>::type range_type;
  range_type operator()(T& cont)
  {
    range_type( cont.begin(), cont.end() );
  }

  range_type operator()(const T& cont)
  {
    range_type( cont.begin(), cont.end() );
  }

};

template<typename AR, typename T, int N>
struct _impl
{
  typedef typename range_traits<AR>::type range_type;
  range_type operator()(T cont)
  {
    range_type( cont, cont + N );
  }
};
*/


}// namespace detail

  
}

#endif
