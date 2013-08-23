//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_DETAIL_UNIQUE_FISRT_IF_HPP
#define FAS_ALGORITHM_DETAIL_UNIQUE_FISRT_IF_HPP

#include <fas/type_list/erase_c.hpp>
#include <fas/type_list/is_type_list.hpp>
#include <fas/type_list/is_organized.hpp>
#include <fas/type_list/type_at_c.hpp>
#include <fas/type_list/length.hpp>
#include <fas/type_list/errorlist.hpp>

#include <fas/algorithm/count_if.hpp>

#include <fas/mp/bind1st.hpp>
#include <fas/static_check/static_error.hpp>


namespace fas{ namespace detail{

template<int P, typename L, template<typename, typename> class F>
struct unique_first_if_impl1_t;

template<int P, typename L, int, template<typename, typename> class F>
struct unique_first_if_impl2_t;

#ifdef FASLIB_TYPE_LIST_CHECK

template<typename L, template<typename, typename> class F>
struct unique_first_if_impl_t
  : static_error< errorlist::not_type_list, is_type_list<L>::value >::type
  , static_error< errorlist::not_organized, is_organized<L>::value >::type
  , unique_first_if_impl1_t< length<L>::value, L, F>
{
};

#else

template<typename L, template<typename, typename> class F>
struct unique_first_if_impl_t
  : unique_first_if_impl1_t< length<L>::value, L, F>
{
};

#endif

template<int P, typename L, template<typename, typename> class F>
struct unique_first_if_impl1_t
{
  typedef typename type_at_c< P - 1, L>::type current;
  typedef typename unique_first_if_impl2_t< P, L, (count_if_t<L, bind1st<F, current>::template apply >::value > 1), F >::type type;
};

template<typename L, template<typename, typename> class F>
struct unique_first_if_impl1_t<0, L, F>
{
  typedef L type;
};

template<int P,typename L, int, template<typename, typename> class F>
struct unique_first_if_impl2_t
{
  typedef typename erase_c<P-1, L>::type erased;
  typedef typename unique_first_if_impl1_t<P-1, erased, F>::type type;
};

template<int P,typename L, template<typename, typename> class F>
struct unique_first_if_impl2_t<P, L, false, F>
{
  typedef typename unique_first_if_impl1_t< P - 1, L, F>::type type;
};

}}

#endif
