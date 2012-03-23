//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_DETAIL_CHECK_LIST_HPP
#define FAS_TYPE_LIST_DETAIL_CHECK_LIST_HPP

#include <fas/type_list/errorlist.hpp>
#include <fas/type_list/is_type_list.hpp>
#include <fas/type_list/is_organized.hpp>
#include <fas/typemanip/if_c.hpp>

namespace fas{ 

template<typename L>
struct is_organized;

namespace detail{

template<typename L, bool B>
struct check_list_impl_1;

template<typename L, bool B>
struct check_list_impl_2;

template<typename L>
struct check_list_helper
  : check_list_impl_1< L, is_type_list<L>::value >
{
};

template<typename L>
struct check_list_impl_1<L, false>
{
  typedef typename if_c<
      has_metatype<L>::value,
      errorlist::bad_metatype,
      errorlist::type_without_metatype
  >::type error;
  enum { value = 0 };
};

template<typename L>
struct check_list_impl_1<L, true>
{
  enum { value = is_organized<L>::value };
  typedef typename check_list_impl_2<L, value>::error error;
};

template<typename L>
struct check_list_impl_2<L, false>
{
  typedef errorlist::not_organized error;
};

template<typename L>
struct check_list_impl_2<L, true>
{
  typedef errorlist::noerror error;
};

}}


#endif
