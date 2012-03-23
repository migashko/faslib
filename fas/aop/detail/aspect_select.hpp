// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_DETAIL_ASPECT_SELECT_HPP
#define FAS_AOP_DETAIL_ASPECT_SELECT_HPP

#include <fas/aop/metalist.hpp>
#include <fas/type_list/metalist.hpp>
#include <fas/type_list/merge.hpp>
//#include <fas/type_list/el.hpp>
//#include <fas/type_list/make_type_list.hpp>
//#include <fas/algorithm/unique_first_if.hpp>
#include <fas/mp/apply.hpp>
#include <fas/typemanip/if_c.hpp>


namespace fas{ namespace detail{
  

  
template<typename M, typename L, typename F>
struct aspect_select_impl;

template<typename M, typename T, typename EL, typename F>
struct aspect_select_impl2;

template<typename L, typename F>
struct aspect_select_helper
{
  typedef typename aspect_select_impl<typename L::metatype, L, F>::type type;
};

template<typename L, typename F>
struct aspect_select_impl< metalist::empty_list, L, F>
{
  typedef typename L::final_type type;
};

template<typename L, typename F>
struct aspect_select_impl< metalist::type_list, L, F>
{
  typedef typename L::left_type head;
  typedef typename L::right_type tail;
  typedef typename merge<
    typename aspect_select_impl2< typename head::metatype, head, typename L::final_type, F>::type,
    typename aspect_select_helper< tail, F>::type
  >::type type;

};

template<typename A, typename F>
struct aspect_select_impl< metalist::aspect, A, F>
{
  typedef typename aspect_select_helper< typename A::type_list, F>::type type;
};

template<typename T, typename F>
struct aspect_select_impl< metalist::advice, T, F>
{
  typedef T type;
};

/*template<typename M, typename T, typename L>
struct aspect_select_impl
{
  typedef typename L::final_type type;
};*/

template<typename M, typename T, typename EL, typename F>
struct aspect_select_impl2
{
  typedef typename if_c<
    apply1<F, T>::type::value,
    T,
    EL
  >::type type;
};

template<typename M, typename T, typename EL>
struct aspect_select_impl2<M, T, EL, empty_type>
{
  typedef T type;
};


template<typename A, typename EL, typename F>
struct aspect_select_impl2< metalist::aspect, A, EL, F>
{
  typedef typename aspect_select_helper< typename A::type_list, F>::type type;
};

template<typename A, typename EL>
struct aspect_select_impl2< metalist::aspect, A, EL, empty_type>
{
  typedef typename aspect_select_helper< typename A::type_list, empty_type>::type type;
};

}}

#endif
