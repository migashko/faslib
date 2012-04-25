//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_DETAIL_FIND_ADVICE_HPP
#define FAS_AOP_DETAIL_FIND_ADVICE_HPP

#include <fas/aop/is_has_tag.hpp>
#include <fas/aop/is_forward.hpp>
#include <fas/aop/is_alias.hpp>
#include <fas/aop/target_cast.hpp>

#include <fas/algorithm/index_of_if.hpp>
#include <fas/mp/placeholders.hpp>

#include <fas/type_list/type_at_c.hpp>
#include <fas/type_list/length.hpp>
#include <fas/type_list/type_list.hpp>
#include <fas/type_list/empty_list.hpp>

#include <fas/typemanip/pair.hpp>
#include <fas/integral/bool_.hpp>

namespace fas{ 

struct _alternative_;
struct _no_alternative_;

template<typename Tg, typename T>
struct advice_not_found { enum { value = 0 }; };

template<typename Tg>
struct advice_not_found<Tg, empty_type>;

  
namespace detail 
{

template<typename Tg, typename L, typename ALT >
struct find_advice_helper;

template<typename Tg, typename L, typename ALT, int Pos, int Len>
struct find_advice_impl_1;

template<typename Tg, typename L, typename ALT, int Pos, int Len>
struct find_advice_impl_2;

template<typename Tg, typename L, typename ALT, int Pos, int Len, typename Cond>
struct find_advice_impl_3;


template<typename Tg, typename ALT >
struct find_advice_helper<Tg, empty_list, ALT>
{
  enum { error = 0 };
  typedef ALT type;
};

template<typename Tg >
struct find_advice_helper<Tg, empty_list, _no_alternative_>
{
  enum { error = advice_not_found<Tg, empty_type>::value };
};

template<typename Tg, typename L, typename ALT >
struct find_advice_helper
 : find_advice_impl_1<Tg, L, ALT, 0, length<L>::value >
{
};

/// //////////////////////


template<typename Tg, typename L, typename ALT, int Pos, int Len>
struct find_advice_impl_1
{
  typedef typename type_at_c<Pos, L>::fulltail current_list;
  enum { position = index_of_if< current_list, is_has_tag< _, Tg > >::value };
  
  typedef typename find_advice_impl_2< Tg, L, ALT, ( position == -1 ? Len : Pos +  position ) , Len  >::type type;
};

template<typename Tg, typename L, int Len>
struct find_advice_impl_2<Tg, L, _no_alternative_, Len, Len >
{
  enum { error = advice_not_found<Tg, empty_type>::value };
  typedef empty_type type;
};

template<typename Tg, typename L, typename ALT, int Len>
struct find_advice_impl_2<Tg, L, ALT, Len, Len >
{
  typedef ALT type;
};

template<typename Tg, typename L, typename ALT, int Pos, int Len>
struct find_advice_impl_2
{
  typedef typename type_at_c<Pos, L>::type current;
  typedef pair< typename is_alias<current>::type, typename is_forward<current>::type > condition;
  typedef typename find_advice_impl_3< Tg, L, ALT, Pos, Len, condition >::type type;
};

template<typename Tg, typename L, typename ALT, int Pos, int Len>
struct find_advice_impl_3<Tg, L, ALT, Pos, Len, pair<false_, false_> >
{
  typedef typename type_at_c<Pos, L>::type type;
};

template<typename Tg, typename L, typename ALT, int Pos, int Len>
struct find_advice_impl_3<Tg, L, ALT, Pos, Len, pair<true_, false_> >
{
  typedef typename type_at_c<Pos, L>::type alias_type;
  typedef typename find_advice_impl_1< typename target_cast<alias_type>::type, L, ALT, 0, Len >::type type;
};

template<typename Tg, typename L, typename ALT, int Pos, int Len>
struct find_advice_impl_3<Tg, L, ALT, Pos, Len, pair<false_, true_ > >
{
  typedef typename type_at_c<Pos, L>::type forward_type;
  typedef typename find_advice_impl_1< typename target_cast<forward_type>::type, L, ALT, Pos + 1, Len >::type type;
};

}}

#endif
