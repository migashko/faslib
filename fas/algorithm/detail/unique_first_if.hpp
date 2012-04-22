//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_DETAIL_UNIQUE_FISRT_IF_HPP
#define FAS_ALGORITHM_DETAIL_UNIQUE_FISRT_IF_HPP

#include <fas/mp/apply.hpp>
#include <fas/mp/lambda.hpp>
#include <fas/static_check/verifying.hpp>
#include <fas/type_list/check_list.hpp>
#include <fas/type_list/metalist.hpp>
#include <fas/type_list/type_at_c.hpp>
#include <fas/type_list/merge.hpp>
#include <fas/type_list/split_c.hpp>
#include <fas/type_list/erase_c.hpp>
#include <fas/algorithm/count_if.hpp>
#include <fas/mp/bind1st.hpp>

namespace fas{ namespace detail{

template<int P, typename L, typename F>
struct unique_first_if_impl;

template<int P, typename L, int, typename F>
struct unique_first_if_impl2;

#ifdef FASLIB_TYPE_LIST_CHECK

template<typename L, typename F>
struct unique_first_if_verifying;

template<typename L, typename F>
struct unique_first_if_helper
  : verifying< unique_first_if_verifying<L, F>, check_list<L> >::type
{
};

template<typename L, typename F>
struct unique_first_if_verifying
  : unique_first_if_impl< length<L>::value, L, F>
{
};

#else

template<typename L, typename F>
struct unique_first_if_helper
  : unique_first_if_impl< length<L>::value, L, F>
{
};

#endif


template<int P, typename L, typename F>
struct unique_first_if_impl
{
  typedef typename type_at_c< P - 1, L>::type current;
  
  typedef typename unique_first_if_impl2<
    P,
    L,
    (
    count_if< 
      L,
      typename lambda_r<F,2>::template apply< current, _1 >
    >::value > 1
    ),
    F
  >::type type;
  
  // typedef typename unique_first_if_impl2_t< P, L, count_if<L, bind1st<F, current>::template apply >::value > 1), F >::type type;
  // typedef typename unique_first_if_impl2_t< P, L, (count_if_t<L, bind1st<F, current>::template apply >::value > 1), F >::type type;
  /*
  typedef typename type_at_c< P - 1, L>::type current;
  
  typedef typename unique_first_if_impl2<
    P,
    L,
    (
      count_if<
        L,
        typename lambda_r<F, 2>::template apply<current, _1>
      >::value > 1
    ),
    F
  >::type type;
  */
  
};

template<typename L, typename F>
struct unique_first_if_impl<0, L, F>
{
  typedef L type;
};

template<int P,typename L, int, typename F>
struct unique_first_if_impl2
{
  typedef typename erase_c<P-1, L>::type erased;
  typedef typename unique_first_if_impl<P-1, erased, F>::type type;
};

template<int P,typename L, typename F>
struct unique_first_if_impl2<P, L, false, F>
{
  typedef typename unique_first_if_impl< P - 1, L, F>::type type;
};


/// ////////////////////////////////////////////////////////

template<int P, typename L, template<typename, typename> class F>
struct unique_first_if_impl_t;

template<int P, typename L, int, template<typename, typename> class F>
struct unique_first_if_impl2_t;

#ifdef FASLIB_TYPE_LIST_CHECK

template<typename L, template<typename, typename> class F>
struct unique_first_if_verifying_t;

template<typename L, template<typename, typename> class F>
struct unique_first_if_helper_t
  : verifying< unique_first_if_verifying_t<L, F>, check_list<L> >::type
{
};

template<typename L, template<typename, typename> class F>
struct unique_first_if_verifying_t
  : unique_first_if_impl_t< length<L>::value, L, F>
{
};

#else

template<typename L, template<typename, typename> class F>
struct unique_first_if_helper_t
  : unique_first_if_impl_t< length<L>::value, L, F>
{
};

#endif


template<int P, typename L, template<typename, typename> class F>
struct unique_first_if_impl_t
{
  typedef typename type_at_c< P - 1, L>::type current;
  typedef typename unique_first_if_impl2_t< P, L, (count_if_t<L, bind1st<F, current>::template apply >::value > 1), F >::type type;
};

template<typename L, template<typename, typename> class F>
struct unique_first_if_impl_t<0, L, F>
{
  typedef L type;
};

template<int P,typename L, int, template<typename, typename> class F>
struct unique_first_if_impl2_t
{
  typedef typename erase_c<P-1, L>::type erased;
  typedef typename unique_first_if_impl_t<P-1, erased, F>::type type;
};

template<int P,typename L, template<typename, typename> class F>
struct unique_first_if_impl2_t<P, L, false, F>
{
  typedef typename unique_first_if_impl_t< P - 1, L, F>::type type;
};

}}

#endif
