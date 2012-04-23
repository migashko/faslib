//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_DETAIL_TRANSFORM2_HPP
#define FAS_ALGORITHM_DETAIL_TRANSFORM2_HPP

#include <fas/type_list/is_type_list.hpp>
#include <fas/type_list/is_organized.hpp>
#include <fas/type_list/type_list.hpp>
#include <fas/type_list/empty_list.hpp>
#include <fas/type_list/errorlist.hpp>
#include <fas/type_list/metalist.hpp>

#include <fas/typemanip/empty_type.hpp>
#include <fas/static_check/static_error.hpp>


namespace fas{ namespace detail{

template< typename L1, typename L2, template<typename,typename> class F>
struct transform2_impl_t;

template<typename MT1, typename MT2, typename L1, typename L2, template<typename,typename> class F>
struct transform2_impl2_t;

#ifdef FASLIB_TYPE_LIST_CHECK

template<typename L1, typename L2, template<typename,typename> class F>
struct transform2_helper_t
  : static_error< errorlist::not_type_list, is_type_list<L1>::value && is_type_list<L2>::value >::type
  , static_error< errorlist::not_organized, is_organized<L1>::value && is_organized<L2>::value >::type
  , transform2_impl_t< L1, L2,  F>
{
};


#else

template<typename L1, typename L2, template<typename,typename> class F>
struct transform2_helper_t
  : transform2_impl_t<L1, L2,  F>
{
};

#endif

template< typename L1, typename L2, template<typename,typename> class F>
struct transform2_impl_t
  : transform2_impl2_t<typename L1::metatype, typename L2::metatype, L1, L2,  F>
{
};


#ifndef DISABLE_TYPE_LIST_SPEC


template< template<typename,typename> class F>
struct transform2_impl_t<empty_list, empty_list, F>
{
  typedef empty_list type;
};


template< typename L, typename R, template<typename,typename> class F>
struct transform2_impl_t< type_list<L, R>, empty_list, F >
{
  typedef type_list<
    typename F< L, empty_type>::type,
    typename transform2_impl_t<  R, empty_list, F>::type
  > type;
};


template< typename L, typename R, template<typename,typename> class F>
struct transform2_impl_t< empty_list, type_list<L, R>,  F >
{
  typedef type_list<
    typename F<empty_type, L>::type,
    typename transform2_impl_t< empty_list, R, F>::type
  > type;
};


template< typename L1, typename R1, typename L2, typename R2, template<typename,typename> class F>
struct transform2_impl_t< type_list<L1, R1>, type_list<L2, R2>,  F >
{
  typedef type_list<
    typename F< L1, L2>::type,
    typename transform2_impl_t< R1, R2, F>::type
  > type;
};

#endif // DISABLE_TYPE_LIST_SPEC


template<typename L1, typename L2, template<typename,typename> class F>
struct transform2_impl2_t<metalist::type_list, metalist::type_list, L1, L2, F>
{
  typedef typename L1::left_type head1;
  typedef typename L1::right_type tail1;
  
  typedef typename L2::left_type head2;
  typedef typename L2::right_type tail2;
  
  typedef type_list<
        typename F< head1, head2>::type,
        typename transform2_impl_t<tail1, tail2, F>::type
      > type;
};

template<typename L1, typename L2, template<typename,typename> class F>
struct transform2_impl2_t<metalist::type_list, metalist::empty_list, L1, L2, F>
{
  typedef typename L1::left_type head1;
  typedef typename L1::right_type tail1;
  
  typedef type_list<
        typename F<head1, empty_type>::type,
        typename transform2_impl_t<tail1, L2, F>::type
      > type;
};

template<typename L1, typename L2, template<typename,typename> class F>
struct transform2_impl2_t< metalist::empty_list, metalist::type_list, L1, L2, F>
{
  typedef typename L2::left_type head2;
  typedef typename L2::right_type tail2;
  
  typedef type_list<
        typename F< empty_type, head2>::type,
        typename transform2_impl_t< L1, tail2, F>::type
      > type;
};


template<typename L1, typename L2,  template<typename,typename> class F>
struct transform2_impl2_t<metalist::empty_list, metalist::empty_list, L1, L2, F>
{
  typedef L1 type;
};

}}


#endif
