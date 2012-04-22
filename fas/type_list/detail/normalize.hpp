//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_DETAIL_NORMALIZE_HPP
#define FAS_TYPE_LIST_DETAIL_NORMALIZE_HPP

#include <fas/type_list/type_list.hpp>
#include <fas/type_list/organize.hpp>

namespace fas{ namespace detail{

template<typename L, int B>
struct normalize_helper;

template<typename T>
struct normalize_helper< T, false>
{
  typedef type_list<T> type;
};

template<typename L, int B>
struct normalize_helper
{
  typedef typename organize< L >::type type;
};

}}

#endif
