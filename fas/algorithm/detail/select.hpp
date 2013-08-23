//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_DETAIL_SELECT_HPP
#define FAS_ALGORITHM_DETAIL_SELECT_HPP

#include <fas/type_list/length.hpp>
#include <fas/type_list/erase_c.hpp>
#include <fas/type_list/type_at_c.hpp>

namespace fas{ namespace detail{

template<int I, typename L, template<typename> class F>
struct select_impl1_t;

template<int C, int I, typename L, template<typename> class F>
struct select_impl2_t;

template<typename L, template<typename> class F>
struct select_impl_t
  : select_impl1_t< length<L>::value, L, F>
{
};

template<int I, typename L, template<typename> class F>
struct select_impl1_t
{
  typedef typename type_at_c<I-1, L>::type current;
  typedef typename select_impl2_t< F<current>::type::value, I, L, F>::type type;
};

template<typename L, template<typename> class F>
struct select_impl1_t<0, L, F>
{
  typedef L type;
};

template<int C, int I, typename L, template<typename> class F>
struct select_impl2_t
{
  typedef typename select_impl1_t< I-1, L, F>::type type;
};

template<int I, typename L, template<typename> class F>
struct select_impl2_t<false, I, L, F>
{
  typedef typename erase_c<I-1, L>::type erased;
  typedef typename select_impl1_t< I-1, erased, F>::type type;
};

}}


#endif
