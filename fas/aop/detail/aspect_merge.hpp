//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_ASPECT_ASPECT_MERGE_HELPER_HPP
#define FAS_AOP_ASPECT_ASPECT_MERGE_HELPER_HPP

#include <fas/aop/aspect.hpp>
#include <fas/type_list/metalist.hpp>
#include <fas/type_list/empty_list.hpp>
#include <fas/type_list/type_list.hpp>
#include <fas/type_list/type_list_n.hpp>
#include <fas/typemanip/empty_type.hpp>
#include <fas/typemanip/some_type.hpp>
#include <fas/algorithm/erase_if.hpp>
#include <fas/mp/placeholders.hpp>


namespace fas{ namespace detail{

template<typename A1, typename A2, typename A3, typename A4, typename A5>
struct aspect_merge_helper
{
  typedef aspect<
    typename erase_if<
      typename type_list_n<A1, A2, A3, A4, A5>::type,
      some_type<empty_type, _>
    >::type
  > type;
};

  
template<typename L1, typename L2, typename A1, typename A2>
struct aspect_merge_impl;
  
template<typename M1, typename M2, typename A1, typename A2>
struct aspect_merge_impl2;

template<typename A1, typename A2>
struct aspect_merge_helper<A1, A2, empty_type, empty_type, empty_type>
{
  typedef typename aspect_merge_impl<
      typename A1::advice_list,
      typename A2::advice_list,
      A1, A2
  >::type type;
};

template<typename L1, typename L2>
struct aspect_merge_helper< aspect<L1>, aspect<L2>, empty_type, empty_type, empty_type >
{
  typedef typename aspect_merge_impl<
      L1, L2,
      aspect<L1>, aspect<L2>
  >::type type;
};

template<typename A>
struct aspect_merge_helper< A, empty_type, empty_type, empty_type, empty_type >
{
  typedef A type;
};

template<typename A>
struct aspect_merge_helper< empty_type, A, empty_type, empty_type, empty_type >
{
  typedef A type;
};

template<typename L1, typename L2, typename A1, typename A2>
struct aspect_merge_impl
  : aspect_merge_impl2< metalist::type_list, metalist::type_list, A1, A2>
{
};

template<typename A1, typename A2>
struct aspect_merge_impl<empty_list, empty_list, A1, A2 >
  : aspect_merge_impl2< metalist::empty_list, metalist::empty_list, A1, A2>
{
};

template<typename L1, typename A1, typename A2>
struct aspect_merge_impl<L1, empty_list, A1, A2 >
  : aspect_merge_impl2< metalist::type_list, metalist::empty_list, A1, A2>
{
};

template<typename L2, typename A1, typename A2>
struct aspect_merge_impl< empty_list, L2, A1, A2 >
  : aspect_merge_impl2< metalist::empty_list, metalist::type_list, A1, A2>
{
};

template<typename A1, typename A2>
struct aspect_merge_impl2<metalist::empty_list, metalist::empty_list, A1, A2>
{
  typedef A1 type;
};

template<typename A1, typename A2>
struct aspect_merge_impl2<metalist::type_list, metalist::empty_list, A1, A2>
{
  typedef A1 type;
};

template<typename A1, typename A2>
struct aspect_merge_impl2<metalist::empty_list, metalist::type_list, A1, A2>
{
  typedef A2 type;
};

template<typename A1, typename A2>
struct aspect_merge_impl2<metalist::type_list, metalist::type_list, A1, A2>
{
  typedef aspect< type_list<A1, type_list<A2> > > type;
};


}}

#endif
