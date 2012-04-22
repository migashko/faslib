//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_DETAIL_INDEX_OF_HPP
#define FAS_TYPE_LIST_DETAIL_INDEX_OF_HPP

#include <fas/type_list/length.hpp>
#include <fas/type_list/check_list.hpp>
#include <fas/type_list/type_list.hpp>
#include <fas/type_list/empty_list.hpp>
#include <fas/typemanip/some_type.hpp>


namespace fas{ namespace detail{

template<int A, int B>
struct index_of_value_helper
{
  enum { value = A };
};

template<int A>
struct index_of_value_helper<A, A>
{
  enum { value = -1 };
};

template<typename T, typename L >
struct index_of_impl;

template<typename T, typename L >
struct index_of_impl0;


template<typename M, typename T, typename L >
struct index_of_impl1;

template<typename T, typename L, bool B >
struct index_of_impl2;

#ifdef FASLIB_TYPE_LIST_CHECK

template<typename T, typename L>
struct index_of_verifying;

template<typename T, typename L>
struct index_of_helper
  : verifying< index_of_verifying<T, L>, check_list<L> >::type
{
};

template<typename T, typename L>
struct index_of_verifying
  : index_of_impl<T, L>
{
};

#else

template<typename T, typename L>
struct index_of_helper
  : index_of_impl<T, L>
{
};

#endif

template<typename T, typename L >
struct index_of_impl
{
  enum
  {
    value = index_of_value_helper<
      index_of_impl0< T, L>::value,
      length<L>::value
    >::value
  };
  typedef typename index_of_impl0< T, L>::tail tail;
};

template<typename T, typename L >
struct index_of_impl0
  : index_of_impl1<typename L::metatype, T, L>
{
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename T, typename L, typename R >
struct index_of_impl0<T, type_list<L, R> >
{
  typedef R tail;
  
  enum 
  { 
    value = index_of_impl2< 
      T, 
      type_list<L, R>, 
      some_type<T, L>::value 
    >::value 
  };
};


template<typename T>
struct index_of_impl0<T, empty_list >
{
  typedef empty_list tail;
  enum { value = 0 };
};

#endif // DISABLE_TYPE_LIST_SPEC

template<typename T, typename L>
struct index_of_impl1<metalist::type_list, T, L>
{
  typedef index_of_impl2< 
    T, L, 
    some_type<T, typename L::left_type>::value 
  > index_of_type;
  
  enum { value = index_of_type::value };
  typedef typename index_of_type::tail tail;
};

template<typename T, typename L>
struct index_of_impl1<metalist::empty_list, T, L>
{
  typedef empty_list tail;
  enum { value = 0 };
};

template<typename T, typename L>
struct index_of_impl2<T, L, true>
{
  typedef typename L::right_type tail;
  enum { value = 0 };
};

template<typename T, typename L>
struct index_of_impl2<T, L, false>
{
  typedef typename L::right_type tail;
  enum { value = 1 + index_of_impl0<T, tail>::value };
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename T, typename L, typename R>
struct index_of_impl2<T, type_list<L, R>, false>
{
  typedef R tail;
  enum { value = 1 + index_of_impl0<T, R>::value };
};

#endif // DISABLE_TYPE_LIST_SPEC

}}


#endif
