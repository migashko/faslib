//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_IMPLEMENTATION_DETAIL_MERGE_HPP
#define FAS_IMPLEMENTATION_DETAIL_MERGE_HPP

#include <fas/static_check/verifying.hpp>
#include <fas/type_list/metalist.hpp>
//#include <fas/type_list/tl.hpp>
#include <fas/type_list/type_list.hpp>
#include <fas/type_list/check_two_lists.hpp>

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
struct merge_helper
  : merge_impl1<is_type_list<L1>::value, is_type_list<L2>::value, L1, L2>
{
};

///
#ifndef DISABLE_TYPE_LIST_SPEC

template<typename L1, typename R1, typename L2>
struct merge_helper<type_list<L1, R1>, L2 >
{
  typedef type_list<
    L1,
    typename merge_helper<
      R1, 
      L2
    >::type
  > type;
};

template<typename L2>
struct merge_helper<empty_list, L2 >
  : merge_impl1< true, is_type_list<L2>::value, empty_list, L2>
{
};

/*
template<typename L1, typename R1, typename L2>
struct merge_helper<tl<L1, R1>, L2 >
{
  typedef tl<
    L1,
    typename merge_helper<
      R1, 
      L2
    >::type
  > type;
};
*/

/*
template<typename L2>
struct merge_helper<el, L2 >
  : merge_impl1< true, is_type_list<L2>::value, el, L2>
{
};
*/

#endif // DISABLE_TYPE_LIST_SPEC

/// false false
/*
template<typename L1, typename L2>
struct merge_impl1<false, false, L1, L2>
{
  typedef tl<L1, tl<L2> > type;
};
*/

/// false true
template<typename T, typename L>
struct merge_impl1<false, true, T, L>
{
  typedef typename L::template rebind< T, L >::type type;
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename T, typename L, typename R>
struct merge_impl1<false, true, T, type_list<L, R> >
{
  typedef type_list< T, type_list<L, R> > type;
};

/*
template<typename T, typename L, typename R>
struct merge_impl1<false, true, T, tl<L, R> >
{
  typedef tl< T, tl<L, R> > type;
};
*/

template<typename T>
struct merge_impl1<false, true, T, empty_list >
{
  typedef type_list< T, empty_list > type;
};

/*
template<typename T>
struct merge_impl1<false, true, T, el >
{
  typedef tl< T, el > type;
};
*/

#endif // DISABLE_TYPE_LIST_SPEC

/// true false 
template<typename L, typename T>
struct merge_impl1<true, false, L, T>
{
  typedef typename merge_helper< 
        L,
        typename L::template rebind<T, typename L::final_type>::type
      >::type type;
};

#ifndef DISABLE_TYPE_LIST_SPEC


template<typename L, typename R, typename T>
struct merge_impl1<true, false, type_list<L, R>, T>
{
  typedef type_list<
    L,
    typename merge_helper< R, T>::type
  > type;
};

/*
template<typename L, typename R, typename T>
struct merge_impl1<true, false, tl<L, R>, T>
{
  typedef tl<
    L,
    typename merge_helper< R, T>::type
  > type;
};
*/
template< typename T>
struct merge_impl1<true, false, empty_list, T>
{
  typedef type_list<T> type;
};

/*
template< typename T>
struct merge_impl1<true, false, el, T>
{
  typedef tl<T> type;
};
*/

#endif // DISABLE_TYPE_LIST_SPEC

/// ///////////////////////////////////////////
/// true true
/// ///////////////////////////////////////////
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

/*
template<typename L2>
struct merge_impl2<el, L2>
{
  typedef L2 type;
};
*/

template<typename L1, typename R1, typename L2>
struct merge_impl2<type_list<L1, R1>, L2 >
  : merge_impl4< type_list<L1, R1>, L2 >
{
};

/*
template<typename L1, typename R1, typename L2>
struct merge_impl2<tl<L1, R1>, L2 >
  : merge_impl4< tl<L1, R1>, L2 >
{
};
*/

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

// L1 непустой список типов
template<typename L1>
struct merge_impl4<L1, empty_list>
{
  typedef L1 type;
};

/*
template<typename L1>
struct merge_impl4<L1, el>
{
  typedef L1 type;
};
*/

// Разношорстные варианты идут по метаспециализации
template<typename L1, typename R1, typename L2, typename R2>
struct merge_impl4<type_list<L1, R1>, type_list<L2, R2> >
{
  typedef type_list< 
    L1,
    typename merge_helper<R1, 
    type_list<L2, R2>
    >::type
  > type;
  ///typedef L1 type;
};

/*
template<typename L1, typename R1, typename L2, typename R2>
struct merge_impl4<tl<L1, R1>, tl<L2, R2> >
{
  typedef tl< 
    L1,
    typename merge_helper<R1, L2>::type
  > type;
  ///typedef L1 type;
};
*/

#endif // DISABLE_TYPE_LIST_SPEC

template<typename L1, typename L2>
struct merge_impl5<metalist::empty_list, L1, L2>
{
  typedef L1 type;
};

template<typename L1, typename L2>
struct merge_impl5<metalist::type_list, L1, L2>
{
  typedef typename L1::template rebind<
      typename L1::left_type,
      typename merge_helper<
          typename L1::right_type,
          L2
      >::type
  >::type type;
};

  /*
template<int, int>
struct _m_pair;

template< typename P, typename L, typename R >
struct merge_impl;

template< typename L, typename R >
struct merge_impl1;

template< typename M, typename L, typename R >
struct merge_impl2;

// проверка больше не нужна, т.к. может работать и не со списками
template<typename L1, typename L2>
struct merge_helper
  : merge_impl< 
      _m_pair<
        is_type_list<L1>::value,
        is_type_list<L2>::value
      >, L1, L2>
{
};


template< typename L1, typename L2>
struct merge_impl<_m_pair<true, true>, L1, L2>
  : merge_impl<typename L2::metatype, L1, L2>
{
};

template< typename L1, typename L2>
struct merge_impl<_m_pair<false, false>, L1, L2>
{
    typedef tl<L1, tl<L2> > type;
};

template< typename L1, typename L2>
struct merge_impl<_m_pair<false, true>, L1, L2>
{
  typedef typename L2::template rebind<
      L1,
      L2
  >::type type;
};

template< typename L1, typename L2>
struct merge_impl<_m_pair<true, false>, L1, L2>
  : merge_impl< _m_pair<true, true>, L1, tl<L2> >
{
};

template< typename L, typename R>
struct merge_impl<metalist::empty_list, L, R>
{
  typedef L type;
};

template< typename L, typename R>
struct merge_impl<metalist::type_list, L, R>
{
  typedef typename merge_impl2<typename L::metatype, L, R>::type type;
};


template< typename L, typename R>
struct merge_impl2<metalist::empty_list, L, R>
{
  typedef R type;
};

template< typename L, typename R>
struct merge_impl2< metalist::type_list,  L, R>
{
  typedef typename L::left_type head;
  typedef typename L::right_type tail;

  typedef typename L::template rebind<
      head,
      typename merge_impl2< typename tail::metatype, tail, R >::type
  >::type type;
};

  */



}}


#endif
