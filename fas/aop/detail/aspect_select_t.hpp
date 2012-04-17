// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_DETAIL_ASPECT_SELECT_T_HPP
#define FAS_AOP_DETAIL_ASPECT_SELECT_T_HPP

#include <fas/aop/metalist.hpp>
#include <fas/type_list/metalist.hpp>
#include <fas/type_list/merge.hpp>
#include <fas/type_list/empty_list.hpp>
#include <fas/type_list/type_list.hpp>
#include <fas/typemanip/if_c.hpp>


namespace fas{ namespace detail{

// #warning TDOD: сделать ошибку если в списке присутствует недопустимый элемент 

template<typename M, typename L, template<typename> class F>
struct aspect_select_t_impl;

template<typename M, typename T, typename EL, template<typename> class F>
struct aspect_select_t_impl2;

template<typename L, template<typename> class F>
struct aspect_select_t_helper
{
  typedef typename aspect_select_t_impl<typename L::metatype, L, F>::type type;
};



#ifndef DISABLE_TYPE_LIST_SPEC

template<template<typename> class F>
struct aspect_select_t_helper<empty_list, F>
{
  typedef typename aspect_select_t_impl< metalist::empty_list, empty_list, F>::type type;
};

template<typename L, typename R, template<typename> class F>
struct aspect_select_t_helper< type_list<L, R>, F>
{
  typedef typename aspect_select_t_impl< metalist::type_list, type_list<L, R>, F>::type type;
};

#endif

template<typename L, template<typename> class F>
struct aspect_select_t_impl< metalist::empty_list, L, F>
{
  typedef empty_list type;
};

template<typename L, template<typename> class F>
struct aspect_select_t_impl< metalist::type_list, L, F>
{
  typedef typename L::left_type head;
  typedef typename L::right_type tail;
  typedef typename merge<
    typename aspect_select_t_impl2< typename head::metatype, head, empty_list, F>::type,
    typename aspect_select_t_helper< tail, F>::type
  >::type type;

};

template<typename A, template<typename> class F>
struct aspect_select_t_impl< metalist::aspect, A, F>
{
  typedef typename aspect_select_t_helper< typename A::type_list, F>::type type;
};

template<typename T, template<typename> class F>
struct aspect_select_t_impl< metalist::advice, T, F>
{
  typedef T type;
};


template<typename M, typename T, typename EL, template<typename> class F>
struct aspect_select_t_impl2
{
  typedef typename if_c< F<T>::type::value, T, EL >::type type;
};


template<typename A, typename EL, template<typename> class F>
struct aspect_select_t_impl2< metalist::aspect, A, EL, F>
{
  typedef typename aspect_select_t_helper< typename A::type_list, F>::type type;
};

}}

#endif
