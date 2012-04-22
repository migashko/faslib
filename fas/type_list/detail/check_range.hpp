//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_DETAIL_CHECK_RANGE_HPP
#define FAS_TYPE_LIST_DETAIL_CHECK_RANGE_HPP

#include <fas/type_list/errorlist.hpp>
#include <fas/type_list/length.hpp>

namespace fas{ namespace detail{

template<int, int, int>
struct check_range_impl;

template<int I, typename L>
struct check_range_helper
  : check_range_impl<I, length<L>::value, ( (I>=0) && (I < length<L>::value) ) >
{
};

template<int I, typename L>
struct check_range_helper2
  : check_range_impl<I, length<L>::value, ( (I>=0) && (I <= length<L>::value) ) >
{
};

template<int, int, int>
struct check_range_impl
{
  typedef errorlist::noerror error;
  enum {value = 1};
};

template<int I, int L>
struct check_range_impl<I, L, false>
{
  typedef errorlist::out_of_range<I, L> error;
  enum {value = 0};
};

}}


#endif
