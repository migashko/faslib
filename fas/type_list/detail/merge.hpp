//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_DETAIL_MERGE_HPP
#define FAS_TYPE_LIST_DETAIL_MERGE_HPP

#include <fas/type_list/type_list.hpp>
#include <fas/type_list/empty_list.hpp>
#include <fas/type_list/metalist.hpp>
#include <fas/type_list/is_type_list.hpp>

namespace fas{ namespace detail{

template<int F1, int F2, typename L1, typename L2>
struct merge_impl1;

template<typename L1, typename L2>
struct merge_impl2;

template<typename M, typename L1, typename L2>
struct merge_impl3;

template<typename L1, typename L2>
struct merge_impl4;

template<typename M, typename L1, typename L2>
struct merge_impl5;

template<typename L1, typename L2>
struct merge_impl
  : merge_impl1<is_type_list<L1>::value, is_type_list<L2>::value, L1, L2>
{
};


#ifndef DISABLE_TYPE_LIST_SPEC

template<typename L1, typename R1, typename L2>
struct merge_impl<type_list<L1, R1>, L2 >
{
  typedef type_list<
    L1,
    typename merge_impl<
      R1, 
      L2
    >::type
  > type;
};

template<typename L2>
struct merge_impl<empty_list, L2 >
  : merge_impl1< true, is_type_list<L2>::value, empty_list, L2>
{
};

#endif // DISABLE_TYPE_LIST_SPEC

template<typename T, typename L>
struct merge_impl1<false, true, T, L>
{
  typedef type_list<T, L> type;
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename T, typename L, typename R>
struct merge_impl1<false, true, T, type_list<L, R> >
{
  typedef type_list< T, type_list<L, R> > type;
};

template<typename T>
struct merge_impl1<false, true, T, empty_list >
{
  typedef type_list< T, empty_list > type;
};

#endif // DISABLE_TYPE_LIST_SPEC

template<typename L, typename T>
struct merge_impl1<true, false, L, T>
{
  typedef typename merge_impl< 
        L,
        type_list<T, empty_list>
      >::type type;
};

#ifndef DISABLE_TYPE_LIST_SPEC


template<typename L, typename R, typename T>
struct merge_impl1<true, false, type_list<L, R>, T>
{
  typedef type_list<
    L,
    typename merge_impl< R, T>::type
  > type;
};

template< typename T>
struct merge_impl1<true, false, empty_list, T>
{
  typedef type_list<T> type;
};

#endif // DISABLE_TYPE_LIST_SPEC

template< typename L1, typename L2>
struct merge_impl1<true, true, L1, L2>
  : merge_impl2<L1, L2>
{
};

template<typename L1, typename L2>
struct merge_impl2
  : merge_impl3<typename L1::metatype, L1, L2>
{
};

#ifndef DISABLE_TYPE_LIST_SPEC


template<typename L2>
struct merge_impl2<empty_list, L2>
{
  typedef L2 type;
};

template<typename L1, typename R1, typename L2>
struct merge_impl2<type_list<L1, R1>, L2 >
  : merge_impl4< type_list<L1, R1>, L2 >
{
};

#endif // DISABLE_TYPE_LIST_SPEC

template<typename L1, typename L2>
struct merge_impl3<metalist::empty_list, L1, L2>
{
  typedef L2 type;
};

template<typename L1, typename L2>
struct merge_impl3<metalist::type_list, L1, L2>
  : merge_impl4<L1, L2 >
{
};

template<typename L1, typename L2>
struct merge_impl4
  : merge_impl5<typename L2::metatype, L1, L2 >
{
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename L1>
struct merge_impl4<L1, empty_list>
{
  typedef L1 type;
};

// Разношорстные варианты идут по метаспециализации
template<typename L1, typename R1, typename L2, typename R2>
struct merge_impl4<type_list<L1, R1>, type_list<L2, R2> >
{
  typedef type_list< 
    L1,
    typename merge_impl<
      R1, 
      type_list<L2, R2>
    >::type
  > type;
};

#endif // DISABLE_TYPE_LIST_SPEC

template<typename L1, typename L2>
struct merge_impl5<metalist::empty_list, L1, L2>
{
  typedef L1 type;
};

template<typename L1, typename L2>
struct merge_impl5<metalist::type_list, L1, L2>
{
  typedef type_list<
      typename L1::left_type,
      typename merge_impl<
          typename L1::right_type,
          L2
      >::type
  > type;
};

}}


#endif
