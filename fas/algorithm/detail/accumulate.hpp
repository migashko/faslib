//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2014
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_DETAIL_ACCUMULATE_HPP
#define FAS_ALGORITHM_DETAIL_ACCUMULATE_HPP

#include <fas/type_list/is_type_list.hpp>
#include <fas/type_list/is_organized.hpp>
#include <fas/type_list/type_list.hpp>
#include <fas/type_list/empty_list.hpp>
#include <fas/type_list/errorlist.hpp>
#include <fas/type_list/metalist.hpp>

#include <fas/typemanip/empty_type.hpp>
#include <fas/static_check/static_error.hpp>

namespace fas{ namespace detail{
  
template< typename L1, template<typename,typename> class F, typename Init>
struct accumulate_impl1_t;

template<typename MT1, typename L1, template<typename,typename> class F, typename Init>
struct accumulate_impl2_t;

#ifdef FASLIB_TYPE_LIST_CHECK

template<typename L1, template<typename,typename> class F, typename Init>
struct accumulate_impl_t
  : static_error< errorlist::not_type_list, is_type_list<L1>::value >::type
  , static_error< errorlist::not_organized, is_organized<L1>::value >::type
  , accumulate_impl1_t< L1, F, Init>
{
};

#else

template<typename L1, template<typename,typename> class F, typename Init>
struct accumulate_impl_t
  : accumulate_impl1_t<L1, F, Init>
{
};

#endif

template< typename L1, template<typename,typename> class F, typename Init>
struct accumulate_impl1_t
  : accumulate_impl2_t<typename L1::metatype, L1, F, Init>
{
};

#ifndef DISABLE_TYPE_LIST_SPEC


template< template<typename,typename> class F, typename Init>
struct accumulate_impl1_t<empty_list, F, Init>
{
  typedef Init type;
};


template< typename L, typename R, template<typename,typename> class F, typename Init>
struct accumulate_impl1_t< type_list<L, R>, F, Init >
{
  typedef typename F<
    L,
    typename accumulate_impl1_t<  R, F, Init>::type
  >::type type;
};

#endif // DISABLE_TYPE_LIST_SPEC


template<typename L1, template<typename,typename> class F, typename Init>
struct accumulate_impl2_t<metalist::type_list, L1, F, Init>
{
  typedef typename L1::left_type head1;
  typedef typename L1::right_type tail1;
  
  typedef typename F<
    head1,
    typename accumulate_impl1_t<  tail1, F, Init>::type
  >::type type;
};


template<typename L1, template<typename,typename> class F, typename Init>
struct accumulate_impl2_t<metalist::empty_list, L1, F, Init>
{
  typedef Init type;
};

  
}}

#endif
