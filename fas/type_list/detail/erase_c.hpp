//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_IMPLEMENTATION_DETAIL_ERASE_HPP
#define FAS_IMPLEMENTATION_DETAIL_ERASE_HPP

#include <fas/static_check/verifying.hpp>
#include <fas/type_list/split_c.hpp>
#include <fas/type_list/check_range_c.hpp>

namespace fas{ namespace detail{

template<int I, typename L>
struct erase_impl;


#ifdef FASLIB_TYPE_LIST_CHECK

template<int I, typename L>
struct erase_verifying;

template<int I,typename L>
struct erase_helper
  : verifying< erase_verifying<I, L>, check_range_c<I, L> >::type
{
};

template<int I, typename L>
struct erase_verifying
  : erase_impl< I, L>
{
};

#else

template<int I,typename L>
struct erase_helper
  : erase_impl< I, L>
{
};

#endif


template<int I, typename L>
struct erase_impl
{
  typedef typename split_c<I, L>::left_list left_list;
  typedef typename split_c<I, L>::right_list right_list;

  typedef typename merge<
      left_list,
      typename right_list::right_type
  >::type type;
};


}}


#endif
