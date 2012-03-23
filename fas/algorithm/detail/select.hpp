//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_DETAIL_SELECT_HPP
#define FAS_ALGORITHM_DETAIL_SELECT_HPP

#include <fas/mp/apply.hpp>
#include <fas/type_list/metalist.hpp>
#include <fas/type_list/length.hpp>
#include <fas/type_list/erase_c.hpp>

namespace fas{ namespace detail{

template<int I, typename L, typename F>
struct select_impl;

template<int C, int I, typename L, typename F>
struct select_impl2;

template<typename L, typename F>
struct select_helper
  : select_impl< length<L>::value, L, F>
{
};

template<int I, typename L, typename F>
struct select_impl
{
  typedef typename type_at_c<I-1, L>::type current;
  typedef typename select_impl2< apply<F, current>::type::value, I, L, F>::type type;
};

template<typename L, typename F>
struct select_impl<0, L, F>
{
  typedef L type;
};

template<int C, int I, typename L, typename F>
struct select_impl2
{
  typedef typename select_impl< I-1, L, F>::type type;
};

template<int I, typename L, typename F>
struct select_impl2<false, I, L, F>
{
  typedef typename erase_c<I-1, L>::type erased;
  typedef typename select_impl< I-1, erased, F>::type type;
};


/// ////////////////////////////////////////////////////////

template<int I, typename L, template<typename> class F>
struct select_impl_t;

template<int C, int I, typename L, template<typename> class F>
struct select_impl2_t;

template<typename L, template<typename> class F>
struct select_helper_t
  : select_impl_t< length<L>::value, L, F>
{
};

template<int I, typename L, template<typename> class F>
struct select_impl_t
{
  typedef typename type_at_c<I-1, L>::type current;
  typedef typename select_impl2_t< F<current>::type::value, I, L, F>::type type;
};

template<typename L, template<typename> class F>
struct select_impl_t<0, L, F>
{
  typedef L type;
};

template<int C, int I, typename L, template<typename> class F>
struct select_impl2_t
{
  typedef typename select_impl_t< I-1, L, F>::type type;
};

template<int I, typename L, template<typename> class F>
struct select_impl2_t<false, I, L, F>
{
  typedef typename erase_c<I-1, L>::type erased;
  typedef typename select_impl_t< I-1, erased, F>::type type;
};

}}


#endif
