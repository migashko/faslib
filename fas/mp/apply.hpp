//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_PS_APPLY_HPP
#define FAS_PS_APPLY_HPP

#include <fas/mp/detail/apply.hpp>

#include <fas/mp/w.hpp>
#include <fas/mp/bind.hpp>
#include <fas/type_list/type_list_n.hpp>
#include <fas/typemanip/empty_type.hpp>

namespace fas{

template<
  typename F,
  typename P0 = empty_type,
  typename P1 = empty_type,
  typename P2 = empty_type,
  typename P3 = empty_type,
  typename P4 = empty_type 
>
struct apply
{
  typedef typename type_list_n< 
    w<P0>, w<P1>, w<P2>, w<P3>, w<P4> 
  >::type arg_list;
  
  typedef typename bind<F, arg_list>::type binded_type;
  typedef typename detail::apply_helper<binded_type>::type type;
};

template<typename F >
struct apply0
{
  typedef typename bind<F>::type binded_type;
  typedef typename detail::apply_helper<binded_type>::type type;
};

template<typename F, typename P0 >
struct apply1
{
  typedef typename bind<F, w<P0> >::type binded_type;
  typedef typename detail::apply_helper<binded_type>::type type;
};

template<typename F, typename P0, typename P1 >
struct apply2
{
  typedef typename type_list_n<
    w<P0>, w<P1> 
  >::type arg_list;

  typedef typename bind< F, arg_list >::type binded_type;
  
  typedef typename detail::apply_helper<binded_type>::type type;
};

template<typename F, typename P0, typename P1, typename P2 >
struct apply3
{
  typedef typename type_list_n<
    w<P0>, w<P1>, w<P2>
  >::type arg_list;
  typedef typename bind<F, arg_list >::type binded_type;
  typedef typename detail::apply_helper<binded_type>::type type;
};

template<typename F, typename P0, typename P1, typename P2, typename P3 >
struct apply4
{
  typedef typename type_list_n<
    w<P0>, w<P1>, w<P2>, w<P3>
  >::type arg_list;
  typedef typename bind<F, arg_list >::type binded_type;
  typedef typename detail::apply_helper<binded_type>::type type;
};

template<typename F, typename P0, typename P1, typename P2, typename P3, typename P4 >
struct apply5
{
  typedef typename type_list_n<
    w<P0>, w<P1>, w<P2>, w<P3>, w<P4>
  >::type arg_list;
  
  typedef typename bind<F, arg_list>::type binded_type;
  typedef typename detail::apply_helper<binded_type>::type type;
};

}

#endif
