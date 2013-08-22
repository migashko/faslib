//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_DETAIL_IS_ORGANIZED_HPP
#define FAS_TYPE_LIST_DETAIL_IS_ORGANIZED_HPP

#include <fas/type_list/type_list.hpp>
#include <fas/type_list/empty_list.hpp>
#include <fas/type_list/is_type_list.hpp>
#include <fas/type_list/metalist.hpp>

namespace fas{ 

template<typename L>
struct is_organized;

namespace detail{

template<typename L, bool B>
struct is_organized_impl2;

template<typename L>
struct is_organized_impl3;

template<typename MT, typename L>
struct is_organized_impl4;

template<typename L, bool B>
struct is_organized_impl5;

template<typename L>
struct is_organized_impl
  : is_organized_impl2< L, is_type_list<L>::value >
{
};

template<typename L>
struct is_organized_impl2<L, false>
{
  enum { value = 0};
};

template<typename L>
struct is_organized_impl2<L, true>
{
  enum { value = is_organized_impl3<L>::value };
};

template<typename L>
struct is_organized_impl3
  : is_organized_impl4<typename L::metatype, L>
{
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename L, typename R>
struct is_organized_impl3< type_list<L, R> >
{
  enum { left_value = is_type_list< L >::value };
  enum { right_value = is_type_list< R >::value };
  enum { value = is_organized_impl5< type_list<L, R>, !left_value && right_value>::value };
};

template<>
struct is_organized_impl3< empty_list >
{
  enum { value = 1 };
};

template<typename L, typename R>
struct is_organized_impl5< type_list<L, R>, true>
{
  enum { value = is_organized<R>::value };
};



#endif // DISABLE_TYPE_LIST_SPEC

template<typename L>
struct is_organized_impl4<metalist::type_list, L>
{
  enum { left_value = is_type_list< typename L::left_type >::value };
  enum { right_value = is_type_list< typename L::right_type >::value };

  enum { value = is_organized_impl5<L, !left_value && right_value>::value };
};

template<typename L>
struct is_organized_impl4<metalist::empty_list, L>
{
  enum { value = 1 };
};

template<typename L>
struct is_organized_impl5<L, false>
{
  enum { value = 0};
};

template<typename L>
struct is_organized_impl5<L, true>
{
  enum { value = is_organized<typename L::right_type>::value };
};

}}


#endif
