//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2010
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_DETAIL_SORT_HPP
#define FAS_ALGORITHM_DETAIL_SORT_HPP

#include <fas/mp/apply.hpp>
#include <fas/static_check/verifying.hpp>
#include <fas/algorithm/is_sorted.hpp>
#include <fas/type_list/metalist.hpp>

namespace fas{ namespace detail{

template<typename L, typename F, int>
struct sort_impl;

template<typename L, typename F>
struct bubble_sort;

template<typename L, typename F>
struct bubble_sort_impl1p;


template<typename M, typename L, typename F>
struct bubble_sort_impl1;

template<typename LL, typename L, typename F>
struct bubble_sort_impl2p;

template<typename M, typename L, typename F>
struct bubble_sort_impl2;

template<typename L, typename F, int>
struct bubble_sort_impl3;

template<typename L, typename F>
struct sort_helper
{
  typedef typename sort_impl< L, F, is_sorted<L, F>::value >::type type;
};

template<typename L, typename F>
struct sort_impl<L, F, true>
{
  typedef L type;
};

template<typename L, typename F>
struct sort_impl<L, F, false>
{
  //БАРБОТИРОВАНИЕ (от франц. barbotage - перемешивание), пропускание через слой жидкости пузырьков газа или пара, к-рый диспергируют в барботерах - трубах с мелкими
  // отверстиями, тарелках с отверстиями, колпачками и т. п. Барботирование применяют в периодич. процессах (при этом жидкость в целом покоится в аппарате) и непрерывных (газ диспергируют в поток жидкости в условиях перекрестного тока или противотока).
  typedef typename bubble_sort<L, F>::type bubbled;
  typedef typename sort_helper<bubbled, F>::type type;
};

template<typename L, typename F>
struct bubble_sort
{
  typedef typename bubble_sort_impl1p<L, F>::type type;
};

template<typename L, typename F>
struct bubble_sort_impl1p
  : bubble_sort_impl1<typename L::metatype, L, F>
{
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename L, typename R, typename F>
struct bubble_sort_impl1p< type_list<L, R>, F >
{
  typedef typename bubble_sort_impl2p<R, type_list<L, R>, F>::type type;
};

/*
template<typename L, typename R, typename F>
struct bubble_sort_impl1p< tl<L, R>, F >
{
  typedef typename bubble_sort_impl2p<R, tl<L, R>, F>::type type;
};
*/

template<typename F>
struct bubble_sort_impl1p< empty_list, F >
{
  typedef empty_list type;
};

/*
template<typename F>
struct bubble_sort_impl1p< el, F >
{
  typedef el type;
};
*/

#endif // DISABLE_TYPE_LIST_SPEC


template<typename L, typename F>
struct bubble_sort_impl1<metalist::type_list, L, F>
{
  typedef typename L::right_type tail;
  typedef typename bubble_sort_impl2p<tail, L, F>::type type;
};

template<typename L, typename F>
struct bubble_sort_impl1<metalist::empty_list, L, F>
{
  typedef L type;
};

template<typename LL, typename L, typename F>
struct bubble_sort_impl2p
  : bubble_sort_impl2<typename LL::metatype, L, F>
{
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename LL, typename LR, typename RR, typename F>
struct bubble_sort_impl2p<type_list<LR, RR>,  type_list<LL, type_list<LR, RR> >, F>
{
  typedef type_list<LL, type_list<LR, RR> > list;
  typedef typename bubble_sort_impl3<list, F, apply<F, LL, LR>::type::value>::type type;
};

/*
template<typename LL, typename LR, typename RR, typename F>
struct bubble_sort_impl2p<tl<LR, RR>,  tl<LL, tl<LR, RR> >, F>
{
  typedef tl<LL, tl<LR, RR> > list;
  typedef typename bubble_sort_impl3<list, F, apply<F, LL, LR>::type::value>::type type;
};
*/

template<typename L, typename F>
struct bubble_sort_impl2p<empty_list, L, F>
{
  typedef L type;
};

/*
template<typename L, typename F>
struct bubble_sort_impl2p<el, L, F>
{
  typedef L type;
};
*/

#endif // DISABLE_TYPE_LIST_SPEC

template<typename L, typename F>
struct bubble_sort_impl2<metalist::type_list, L, F>
{
  typedef typename L::left_type first;
  typedef typename L::right_type tail;
  typedef typename tail::left_type second;
  typedef typename bubble_sort_impl3<L, F, apply<F, first, second>::type::value>::type type;
};

template<typename L, typename F>
struct bubble_sort_impl2<metalist::empty_list, L, F>
{
  typedef L type;
};

template<typename L, typename F>
struct bubble_sort_impl3<L, F, true>
{
  typedef typename L::left_type head;
  typedef typename L::right_type tail;
  // ок, перестановка не требуется
  // не паримся и перестраиваем список 
  typedef type_list<
    head,
    // барботируем хвост
    typename bubble_sort<tail, F>::type
  > type;
  
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename L, typename R,  typename F>
struct bubble_sort_impl3< type_list<L, R>, F, true>
{
  typedef type_list<L, typename bubble_sort<R, F>::type > type;
};

/*
template<typename L, typename R, typename F>
struct bubble_sort_impl3< tl<L, R>, F, true>
{
  typedef tl<L, typename bubble_sort<R, F>::type > type;
};
*/

#endif // DISABLE_TYPE_LIST_SPEC

template<typename L, typename F>
struct bubble_sort_impl3<L, F, false>
{
  // переставляем
  typedef typename L::left_type head1;
  typedef typename L::right_type tail1;
  typedef typename tail1::left_type head2;
  typedef typename tail1::right_type tail2;
  
  typedef type_list<
    head1,
    tail2
  > nonbabled;
  
  typedef type_list<
    head2,
    // барботируем хвост
    typename bubble_sort<nonbabled, F>::type
  > type;
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename LL, typename LR, typename RR, typename F>
struct bubble_sort_impl3< type_list<LL, type_list<LR, RR> > , F, false>
{
  typedef type_list<
    LR, 
    typename bubble_sort<type_list<LL, RR>, F>::type
  > type;
};

/*
template<typename LL, typename LR, typename RR, typename F>
struct bubble_sort_impl3< tl<LL, tl<LR, RR> > , F, false>
{
  typedef tl<
    LR, 
    typename bubble_sort<tl<LL, RR>, F>::type
  > type;
};
*/


#endif // DISABLE_TYPE_LIST_SPEC


/// ////////////////////////////////////////////////////
/// ////////////////////////////////////////////////////
/// ////////////////////////////////////////////////////
/// ////////////////////////////////////////////////////

template<typename L, template<typename,typename> class F, int>
struct sort_impl_t;

template<typename L, template<typename,typename> class F>
struct bubble_sort_t;

template<typename L, template<typename,typename> class F>
struct bubble_sort_impl1p_t;

template<typename M, typename L, template<typename,typename> class F>
struct bubble_sort_impl1_t;

template<typename LL, typename L, template<typename,typename> class F>
struct bubble_sort_impl2p_t;

template<typename M, typename L, template<typename,typename> class F>
struct bubble_sort_impl2_t;

template<typename L, template<typename,typename> class F, int>
struct bubble_sort_impl3_t;

template<typename L, template<typename,typename> class F>
struct sort_helper_t
{
  typedef typename sort_impl_t< L, F, is_sorted_t<L, F>::value >::type type;
};

template<typename L, template<typename,typename> class F>
struct sort_impl_t<L, F, true>
{
  typedef L type;
};

template<typename L, template<typename,typename> class F>
struct sort_impl_t<L, F, false>
{
  typedef typename bubble_sort_t<L, F>::type bubbled;
  typedef typename sort_helper_t<bubbled, F>::type type;
};

template<typename L, template<typename,typename> class F>
struct bubble_sort_t
{
  typedef typename bubble_sort_impl1p_t<L, F>::type type;
};

template<typename L, template<typename,typename> class F>
struct bubble_sort_impl1p_t
  : bubble_sort_impl1_t<typename L::metatype, L, F>
{
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename L, typename R, template<typename,typename> class F>
struct bubble_sort_impl1p_t< type_list<L, R>, F >
{
  typedef typename bubble_sort_impl2p_t<R, type_list<L, R>, F>::type type;
};

template<template<typename,typename> class F>
struct bubble_sort_impl1p_t< empty_list, F >
{
  typedef empty_list type;
};

#endif // DISABLE_TYPE_LIST_SPEC


template<typename L, template<typename,typename> class F>
struct bubble_sort_impl1_t<metalist::type_list, L, F>
{
  typedef typename L::right_type tail;
  typedef typename bubble_sort_impl2p_t<tail, L, F>::type type;
};

template<typename L, template<typename,typename> class F>
struct bubble_sort_impl1_t<metalist::empty_list, L, F>
{
  typedef L type;
};

template<typename LL, typename L, template<typename,typename> class F>
struct bubble_sort_impl2p_t
  : bubble_sort_impl2_t<typename LL::metatype, L, F>
{
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename LL, typename LR, typename RR, template<typename,typename> class F>
struct bubble_sort_impl2p_t<type_list<LR, RR>,  type_list<LL, type_list<LR, RR> >, F>
{
  typedef type_list<LL, type_list<LR, RR> > list;
  typedef typename bubble_sort_impl3_t<list, F, F<LL, LR>::type::value>::type type;
};

template<typename L, template<typename,typename> class F>
struct bubble_sort_impl2p_t<empty_list, L, F>
{
  typedef L type;
};

#endif // DISABLE_TYPE_LIST_SPEC

template<typename L, template<typename,typename> class F>
struct bubble_sort_impl2_t<metalist::type_list, L, F>
{
  typedef typename L::left_type first;
  typedef typename L::right_type tail;
  typedef typename tail::left_type second;
  typedef typename bubble_sort_impl3_t<L, F, F<first, second>::type::value>::type type;
};

template<typename L, template<typename,typename> class F>
struct bubble_sort_impl2_t<metalist::empty_list, L, F>
{
  typedef L type;
};

template<typename L, template<typename,typename> class F>
struct bubble_sort_impl3_t<L, F, true>
{
  typedef typename L::left_type head;
  typedef typename L::right_type tail;
  typedef type_list<
    head,
    typename bubble_sort_t<tail, F>::type
  > type;
  
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename L, typename R,  template<typename,typename> class F>
struct bubble_sort_impl3_t< type_list<L, R>, F, true>
{
  typedef type_list<L, typename bubble_sort_t<R, F>::type > type;
};

#endif // DISABLE_TYPE_LIST_SPEC

template<typename L, template<typename,typename> class F>
struct bubble_sort_impl3_t<L, F, false>
{
  typedef typename L::left_type head1;
  typedef typename L::right_type tail1;
  typedef typename tail1::left_type head2;
  typedef typename tail1::right_type tail2;
  
  typedef type_list<
    head1,
    tail2
  > nonbabled;
  
  typedef type_list<
    head2,
    typename bubble_sort_t<nonbabled, F>::type
  > type;
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename LL, typename LR, typename RR, template<typename,typename> class F>
struct bubble_sort_impl3_t< type_list<LL, type_list<LR, RR> > , F, false>
{
  typedef type_list<
    LR, 
    typename bubble_sort_t<type_list<LL, RR>, F>::type
  > type;
};


#endif // DISABLE_TYPE_LIST_SPEC

}}


#endif
