#ifndef FAS_RANGE_TYPERANGE_HPP
#define FAS_RANGE_TYPERANGE_HPP

#include <fas/range/range_category.hpp>

#include <fas/range/output_range.hpp>
#include <fas/range/input_range.hpp>
#include <fas/range/forward_range.hpp>
#include <fas/range/bidirectional_range.hpp>
#include <fas/range/random_access_range.hpp>

#include <fas/typemanip/has_typename.hpp>
#include <fas/typemanip/empty_type.hpp>
#include <fas/typemanip/type2type.hpp>
#include <fas/typemanip/remove_const.hpp>
#include <fas/typemanip/is_array.hpp>
#include <fas/typemanip/is_pointer.hpp>

namespace fas{

FAS_HAS_TYPENAME(has_iterator_category, iterator_category);
FAS_HAS_TYPENAME(has_range_category, range_category);
FAS_HAS_TYPENAME(has_iterator, iterator);

struct typerange_flag
{
  struct shift
  {
    enum {
      other     = 0,
      pointer   = 1,
      array     = 2,
      range     = 3,
      iterator  = 4,
      container = 5
    };
  };
  
  enum {
    other     = 0,
    pointer   = 1 << shift::pointer,
    array     = 1 << shift::array,
    range     = 1 << shift::range,
    iterator  = 1 << shift::iterator,
    container = 1 << shift::container
  };

  template<typename T>
  struct make
  {
    enum
    {
      array_flag = is_array<T>::value, 
      pointer_flag = !array_flag && is_pointer<T>::value, 
      iterator_flag = !pointer_flag && has_iterator_category<T>::value,
      container_flag = !iterator_flag && has_iterator<T>::value,
      range_flag = !iterator_flag && has_range_category<T>::value,
    };

    enum
    {
      value =
          ( array_flag     << shift::array )
        | ( pointer_flag   << shift::pointer )
        | ( iterator_flag  << shift::iterator )
        | ( container_flag << shift::container )
        | ( range_flag     << shift::range )
    };
  };
};

template<typename T, typename Tg = empty_type>
struct iterator2range;

template<typename T>
struct iterator2range<T, std::input_iterator_tag>
{
  typedef input_range<T> type;
};

template<typename T>
struct iterator2range<T, std::output_iterator_tag>
{
  typedef output_range<T> type;
};

template<typename T>
struct iterator2range<T, std::forward_iterator_tag>
{
  typedef forward_range<T> type;
};

template<typename T>
struct iterator2range<T, std::bidirectional_iterator_tag>
{
  typedef bidirectional_range<T> type;
};

template<typename T>
struct iterator2range<T, std::random_access_iterator_tag>
{
  typedef random_access_range<T> type;
};


template<typename T>
struct iterator2range<T, empty_type>
  : iterator2range<T, typename std::iterator_traits<T>::iterator_category > 
{

};


template<typename T>
struct typerange;

template< typename T, int flag >
struct range_helper;

template< typename T>
struct range_helper<T, typerange_flag::other >
{
  typedef random_access_range<T*> range;
  typedef range init_range;
  typedef typename range::iterator iterator;
  typedef typename range::range_category    range_category;
  typedef typename range::iterator_category iterator_category;
  typedef typename range::value_type        value_type;
  typedef typename range::difference_type   difference_type;
  typedef typename range::pointer           pointer;
  typedef typename range::reference         reference;

  static inline range make_range(T& v)
  {
    return range(&v, &v + 1);
  }

  static inline init_range make_init_range(T& v, bool clear = false)
  {
    if ( clear )
      v = T();
    return init_range(&v, &v + 1);
  }

};

template< typename T>
struct range_helper<T*, typerange_flag::pointer >
{
  typedef random_access_range<T*> range;
  typedef typename range::iterator iterator;
  typedef typename range::range_category    range_category;
  typedef typename range::iterator_category iterator_category;
  typedef typename range::value_type        value_type;
  typedef typename range::difference_type   difference_type;
  typedef typename range::pointer           pointer;
  typedef typename range::reference         reference;

  template<typename TT>
  static inline range make_range(TT* beg, TT* end )
  {
    return range(beg, end);
  }
  
};

template< typename T, int N>
struct range_helper<T[N], typerange_flag::array >
{
  typedef random_access_range<T*> range;
  typedef range init_range;
  typedef typename range::iterator iterator;
  typedef typename range::range_category    range_category;
  typedef typename range::iterator_category iterator_category;
  typedef typename range::value_type        value_type;
  typedef typename range::difference_type   difference_type;
  typedef typename range::pointer           pointer;
  typedef typename range::reference         reference;

  template<typename TT>
  static inline range make_range(TT* v)
  {
    return range(v, static_cast<TT*>(v) + N);
  }

  template<typename TT>
  static inline range make_end_range(TT* v)
  {
    return range(v + N , v + N);
  }

  template<typename TT>
  static inline range make_range(TT* beg, TT* end )
  {
    return range(beg, end);
  }

  template<typename TT>
  static inline init_range make_init_range(TT* v, bool clear = false)
  {
    if ( clear)
      _clear( v, type2type<TT>() );
    return range(v, v + N);
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

template< typename R>
struct range_helper<R, typerange_flag::range >
{
  typedef R range;
  typedef typename range::iterator iterator;
  typedef typename range::range_category    range_category;
  typedef typename range::iterator_category iterator_category;
  typedef typename range::value_type        value_type;
  typedef typename range::difference_type   difference_type;
  typedef typename range::pointer           pointer;
  typedef typename range::reference         reference;

  template<typename RR>
  static inline range make_range(RR r)
  {
    return r;
  }

  template<typename RR>
  static inline range make_end_range(RR r)
  {
    return range( r.end() , r.end());
  }

};

template< typename I>
struct range_helper<I, typerange_flag::iterator >
{
  typedef typename iterator2range< typename remove_const<I>::type >::type range;
  
  typedef typename range::iterator iterator;
  typedef typename range::range_category    range_category;
  typedef typename range::iterator_category iterator_category;
  typedef typename range::value_type        value_type;
  typedef typename range::difference_type   difference_type;
  typedef typename range::pointer           pointer;
  typedef typename range::reference         reference;
  
  
  /*template<typename II>*/
  static inline range make_range(I/*I*/ beg)
  {
    // template for only output_range
    return range(beg);
  }

  /*template<typename II>*/
  static inline range make_range(I/*I*/ beg, I/*I*/ end)
  {
    // template for other range
    return range(beg, end);
  }
};

template< typename C, int CNST>
struct range_container_helper
{
  typedef typename iterator2range< typename C::const_iterator >::type range;

  
  static inline range make_range(const C& ctn)
  {
    return range( ctn.begin(), ctn.end() );
  }

};

template< typename C>
struct range_container_helper<C, false>
{
  typedef typename iterator2range< typename C::iterator >::type range;
  typedef typename iterator2range< std::insert_iterator<C> >::type init_range;
  
  template<typename CC>
  static inline init_range make_init_range(CC& cnt, bool clear = false)
  {
    if (clear)
      cnt.clear();
    return init_range( std::inserter(cnt, cnt.end()) );
  }

  static inline range make_range(C& ctn)
  {
    return range( ctn.begin(), ctn.end() );
  }

};



template< typename C>
struct range_helper<C, typerange_flag::container >
  : range_container_helper< C, is_const<C>::value  >
{
  typedef range_container_helper< C, is_const<C>::value > super;
  typedef typename super::range range;
  /*
  typedef typename iterator2range<
    if_c< is_const<C>::value
      typename C::iterator,
      typename C::const_iterator
    >::type
  >::type range;
  
  typedef typename iterator2range< std::insert_iterator<C> >::type init_range;
  */
  
  // typedef typename range::iterator iterator;
  typedef typename range::iterator iterator;
  typedef typename range::range_category    range_category;
  typedef typename range::iterator_category iterator_category;
  typedef typename range::value_type        value_type;
  typedef typename range::difference_type   difference_type;
  typedef typename range::pointer           pointer;
  typedef typename range::reference         reference;

  /*
  template<typename CC>
  static inline range make_range(CC& ctn)
  {
    return range( ctn.begin(), ctn.end() );
  }
  */

  /*static inline range make_range(const C& ctn)
  {
    return range( ctn.begin(), ctn.end() );
  }*/

  template<typename CC>
  static inline range make_end_range(CC& ctn)
  {
    return range( ctn.end(), ctn.end() );
  }

};

template<typename T>
struct typerange
  : range_helper<T, typerange_flag::make<T>::value >
{
};

/*
template<typename T, int N>
struct range_traits<T[N]>
  : range_helper<T[N], typerange_flag::array >
{
};

template<typename T>
struct range_traits<T*>
  : range_helper<T*, typerange_flag::pointer >
{
};
*/


};

#endif
