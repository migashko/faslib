#ifndef FAS_range_OUTPUT_RANGE_HPP
#define FAS_range_OUTPUT_RANGE_HPP

#include <fas/range/range_category.hpp>
#include <iterator>

namespace fas{

template<typename T>
struct output_value_type_1;

template<typename T>
struct output_value_type_2;

template<typename T>
struct output_value_type: output_value_type_2<T>{};

template< typename _Tp, typename _CharT, typename _Trait >
struct output_value_type< std::ostream_iterator<_Tp, _CharT, _Trait> >
{
  typedef _CharT value_type;
  //typedef _Tp value_type;
  //typedef std::ostream_iterator<_Tp, _CharT, _Trait>
};

template<typename T>
struct output_value_type_2: output_value_type_1<T>{};

template<typename _CharT, typename _Trait >
struct output_value_type_2< std::ostreambuf_iterator<_CharT, _Trait> >
{
  //typedef std::ostreambuf_iterator<_CharT, _Trait> value_type;
  typedef _CharT value_type;
};

template< template<typename> class C, typename P1 >
struct output_value_type_1< C<P1> >
{
  typedef typename P1::value_type value_type;
};

/*
template< template<typename> class C, typename P1 >
struct output_value_type< const C<P1> >
{
  typedef typename P1::value_type value_type;
};*/

/*
template< template<typename, typename> class C, typename P1, typename P2 >
struct output_value_type< C<P1, P2> >
{
  typedef typename C<P1, P2>::value_type value_type;
};

template< template<typename, typename, typename> class C, typename P1, typename P2, typename P3 >
struct output_value_type< C<P1, P2, P3> >
{
  typedef typename C<P1, P2, P3>::value_type value_type;
};

template< template<typename, typename, typename, typename> class C, typename P1, typename P2, typename P3, typename P4 >
struct output_value_type< C<P1, P2, P3, P4> >
{
  typedef typename C<P1, P2, P3, P4>::value_type value_type;
};

template< template<typename, typename, typename, typename, typename> class C, typename P1, typename P2, typename P3, typename P4, typename P5 >
struct output_value_type< C<P1, P2, P3, P4, P5> >
{
  typedef typename C<P1, P2, P3, P4, P5>::value_type value_type;
};
*/

template<typename T>
struct output_range_no_const
{
  typedef T type;
};

template<typename T>
struct output_range_no_const<const T>
{
  typedef T type;
};

template<typename T>
class output_range
{
public:
  typedef output_range_tag range_category;
  
  
  typedef T iterator;

  
  typedef typename output_value_type< typename output_range_no_const<T>::type >::value_type value_type;
  typedef typename std::iterator_traits<T>::iterator_category iterator_category;
//  typedef typename std::iterator_traits<T>::value_type        value_type;
  typedef typename std::iterator_traits<T>::difference_type   difference_type;
  typedef typename std::iterator_traits<T>::pointer           pointer;
  typedef typename std::iterator_traits<T>::reference         reference;
  

  
  output_range()
    : b()
  {}

  explicit output_range(T b)
    : b(b)
  {}

  operator bool () const { return true; }

  iterator& operator*() { return b; }

  template<typename V>
  output_range<T>& operator=(const V& value)
  {
    *b = value;
    return *this;
  }

  output_range<T>& operator++() 
  {
    return *this; 
  }

  output_range<T>& operator++(int) 
  {
    return *this; 
  }

protected:
  T b;
};

}

#endif

