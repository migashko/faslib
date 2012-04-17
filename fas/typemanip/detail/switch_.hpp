//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_DETAIL_SWITCH__HPP
#define FAS_TYPEMANIP_DETAIL_SWITCH__HPP

#include <fas/typemanip/empty_type.hpp>
#include <fas/type_list/type_list.hpp>

namespace fas{ namespace detail {
  
template<typename L>
struct switch_helper;

template<typename H, typename L, int >
struct switch_impl
{
  typedef typename H::type type;
};

template<typename H, typename L>
struct switch_impl<H, L, false>
{
  typedef typename switch_helper<L>::type type;
};

template<typename L>
struct switch_helper
{
  typedef typename L::left_type head;
  typedef typename L::right_type tail;
  typedef typename switch_impl< head, tail, head::value>::type type;
};


template<typename L, typename R>
struct switch_helper< type_list<L, R> >
{
  typedef L head;
  typedef R tail;
  typedef typename switch_impl< head, tail, head::value>::type type;
};

template<>
struct switch_helper<empty_list>
{
  typedef empty_type type;
};

}}

#endif
