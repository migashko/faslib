// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_MP_DETAIL_BIND_HPP
#define FAS_MP_DETAIL_BIND_HPP

#include <fas/mp/p.hpp>
#include <fas/mp/ps.hpp>

#error исправить бинд для плейсхолдера _

namespace fas{ namespace detail{

template<typename F, typename PL, int>
struct bind_impl1;

template<typename F, typename PL>
struct bind_impl2;

template<typename F, typename PL>
struct bind_helper
{
  typedef typename bind_impl1<F, PL, is_p<F>::value >::type type;
};

template<typename F, typename PL>
struct bind_impl1<F, PL, true>
{
  typedef typename unp<F>::type type;
};

template<typename F, typename PL>
struct bind_impl1<F, PL, false>
{
  typedef typename bind_impl2<F, PL>::type type;
};

template<typename F, typename PL>
struct bind_impl2_1;
template<typename F, typename PL>
struct bind_impl2_2;
template<typename F, typename PL>
struct bind_impl2_3;
template<typename F, typename PL>
struct bind_impl2_4;


template<typename F, typename PL>
struct bind_impl2
  : bind_impl2_4< F, PL >
{
};

template<typename F, typename PL>
struct bind_impl2_1
{
  typedef typename ps< F, PL >::type type;
};

template<template<typename> class F, typename P0, typename PL>
struct bind_impl2_1< F<P0>, PL>
{
  typedef P0 arg0;
  typedef F<
    typename bind_impl1< arg0, PL, is_p<arg0>::value >::type
  > type;
};

template<typename F, typename PL>
struct bind_impl2_2: bind_impl2_1 < F, PL > {};


template<template<typename, typename> class F, typename P0, typename P1, typename PL>
struct bind_impl2_2< F<P0, P1>, PL>
{
  typedef P0 arg0;
  typedef P1 arg1;
  typedef F<
    typename bind_impl1< arg0, PL, is_p<arg0>::value >::type,
    typename bind_impl1< arg1, PL, is_p<arg1>::value >::type
  > type;
};

template<typename F, typename PL>
struct bind_impl2_3: bind_impl2_2 < F, PL > {};

template<template<typename, typename, typename> class F, typename P0, typename P1, typename P2, typename PL>
struct bind_impl2_3< F<P0, P1, P2>, PL>
{
  typedef P0 arg0;
  typedef P1 arg1;
  typedef P2 arg2;

  typedef F<
    typename bind_impl1< arg0, PL, is_p<arg0>::value >::type,
    typename bind_impl1< arg1, PL, is_p<arg1>::value >::type,
    typename bind_impl1< arg2, PL, is_p<arg2>::value >::type
  > type;
};

template<typename F, typename PL>
struct bind_impl2_4: bind_impl2_3 < F, PL > {};

template<template<typename, typename, typename, typename> class F, typename P0, typename P1, typename P2, typename P3, typename PL>
struct bind_impl2_4< F<P0, P1, P2, P3>, PL>
{
  typedef P0 arg0;
  typedef P1 arg1;
  typedef P2 arg2;
  typedef P3 arg3;

  typedef F<
    typename bind_impl1< arg0, PL, is_p<arg0>::value >::type,
    typename bind_impl1< arg1, PL, is_p<arg1>::value >::type,
    typename bind_impl1< arg2, PL, is_p<arg2>::value >::type,
    typename bind_impl1< arg3, PL, is_p<arg3>::value >::type
  > type;
};

template<template<typename, typename, typename, typename, typename> class F, typename P0, typename P1, typename P2, typename P3, typename P4, typename PL>
struct bind_impl2< F<P0, P1, P2, P3, P4>, PL>
{
  typedef P0 arg0;
  typedef P1 arg1;
  typedef P2 arg2;
  typedef P3 arg3;
  typedef P4 arg4;

  typedef F<
    typename bind_impl1< arg0, PL, is_p<arg0>::value >::type,
    typename bind_impl1< arg1, PL, is_p<arg1>::value >::type,
    typename bind_impl1< arg2, PL, is_p<arg2>::value >::type,
    typename bind_impl1< arg3, PL, is_p<arg3>::value >::type,
    typename bind_impl1< arg4, PL, is_p<arg4>::value >::type
  > type;
};

/// ///////////////////////////

}}

#endif
