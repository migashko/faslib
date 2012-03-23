#ifndef FAS_range_MAKE_RANGE_HPP
#define FAS_range_MAKE_RANGE_HPP



#include <iterator>

#include <fas/range/string_range.hpp>
#include <fas/range/detail/make_range.hpp>
#include <fas/integral/int_.hpp>
#include <fas/static_check/static_check.hpp>
#include <fas/static_check/verifying.hpp>

#include <fas/typemanip/some_type.hpp>
#include <fas/integral/bool_.hpp>

#include <ostream>
#include <istream>

#include <iostream>

namespace fas{

template<typename T>
struct range_traits
  : ::fas::detail::range_traits_helper<T>
{
  typedef typename ::fas::detail::range_traits_helper<T>::range_type type;
 /* typedef detail::range_traits_helper<T> helper;
  typedef typename helper::range_type range_type;
  typedef typename helper::range_type type;
  */

};

template<typename Tchar, typename traits>
inline input_range< std::istreambuf_iterator<Tchar, traits> >
  make_ibufrange(std::basic_istream<Tchar, traits>& cnt)
{
  return input_range< std::istreambuf_iterator<Tchar, traits> >( std::istreambuf_iterator<Tchar, traits>(cnt), std::istreambuf_iterator<Tchar, traits>() );
};

template<typename Tchar>
inline input_range< std::istream_iterator<Tchar> >
  make_irange( std::basic_istream<Tchar>& cnt )
{
  return input_range< std::istream_iterator<Tchar> >( std::istream_iterator<Tchar>(cnt), std::istream_iterator<Tchar>() );
};


template<typename T>
inline typename range_traits<T>::type make_range(T beg, T end)
{
  return range_traits<T>::make_range(beg,  end);
};


template<typename T>
inline typename range_traits<T>::type make_range(T& beg)
{
  return range_traits<T>::make_range(beg);
};

template<typename T>
inline typename range_traits<const T>::type make_range(const T& beg)
{
  return range_traits<const T>::make_range(beg);
};




template<typename T>
inline string_range<T> make_string_range(T beg)
{
  typedef string_range<T> range_type;
  return range_type(beg);
};


/// ////////////////////////////////////////////
/*
namespace detail
{

template<typename T, typename ID>
struct initialize_range_helper;

template<typename T, int N>
struct initialize_range_helper<T[N], int_<1> >
{
  typedef iterator_range< T* > iter_range;
  typedef typename iter_range::range_type range_type;
  typedef typename range_type::pointer pointer;
  static inline range_type make_range(pointer beg) { return range_type(beg, beg + N); }
};

template<typename T>
struct initialize_range_helper<T, int_<2> >
{
  // sequence
  typedef iterator_range< std::back_insert_iterator<T> > range_type;
  
  static inline range_type make_range(T& cnt)
  {
    range_type( std::back_inserter(cnt) );
  }
};

template<typename T>
struct initialize_range_helper<T, int_<4> >
{
  // associative
  typedef iterator_range< std::insert_iterator<T> > range_type;
  
  static inline range_type make_range(T& cnt)
  {
    range_type( std::inserter(cnt, cnt.end()) );
  }
};

template<typename T>
struct initialize_range
{
  typedef typename range_traits<T>::helper helper;
  enum { type_id = helper::is_array 
                   + ( helper::is_sequence_container >> 1) 
                   + ( helper::is_associative_container >> 2)
       };
       
  typedef initialize_range_helper<T, int_<type_id> > type;
};

}
*/

template<typename T>
inline typename range_traits<T>::initial_range_type
  make_initial_range(T& cnt)
{
  return range_traits<T>::make_initial_range(cnt);
};


template<typename charT >
inline output_range< std::ostreambuf_iterator<charT> >
  make_obufrange(std::basic_ostream<charT>& cnt)
{
  return output_range< std::ostreambuf_iterator<charT> >( std::ostreambuf_iterator<charT>(cnt) );
};

template<typename charT >
inline output_range< std::ostream_iterator<charT> >
  make_orange(std::basic_ostream<charT>& cnt)
{
  return output_range< std::ostream_iterator<charT> >( std::ostream_iterator<charT>(cnt) );
};

/*
template<typename T >
struct range_error
  : some_type<true_, T>
{
  //struct error{};
  struct can_not_make_initial_range_for_const_reference{};
  typedef can_not_make_initial_range_for_const_reference error;
};

template<typename T>
typename range_traits<const T>::type make_initial_range(const T& beg)
{
  //verifying<T, range_error<T> > v;
  throw "fuck";
  //typename range_error<T>::error can_not_make_initial_range_for_const_reference;
  //return make_range( T(beg) );
};
*/



}

#endif
