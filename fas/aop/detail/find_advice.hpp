//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_DETAIL_FIND_ADVICE_HPP
#define FAS_AOP_DETAIL_FIND_ADVICE_HPP

#include <fas/aop/private/is_has_tag.hpp>
#include <fas/aop/private/is_forward.hpp>
#include <fas/aop/private/is_alias.hpp>
#include <fas/aop/private/is_remover.hpp>
#include <fas/aop/private/target_cast.hpp>

#include <fas/algorithm/index_of_if.hpp>
#include <fas/mp/placeholders.hpp>

#include <fas/type_list/type_at_c.hpp>
#include <fas/type_list/length.hpp>
#include <fas/type_list/empty_list.hpp>
#include <fas/type_list/index_of.hpp>
#include <fas/type_list/push_front.hpp>


namespace fas{

struct _alternative_;
struct _no_alternative_;

template<typename Tg, typename T>
struct advice_not_found { enum { value = 0 }; };

template<typename Tg>
struct advice_not_found<Tg, empty_type>;

template<typename Tg, typename T>
struct advice_has_been_removed { enum { value = 0 }; };

template<typename Tg>
struct advice_has_been_removed<Tg, empty_type>;


template<typename Tg, typename AliasList, typename T>
struct recursive_alias{ enum { value = 0 }; };

template<typename Tg, typename AliasList>
struct recursive_alias<Tg, AliasList, empty_type>;

namespace detail
{

struct advace_category
{
  typedef enum{
    advice = 0,
    alias = 1,
    forward = 2,
    removed = 4
  } type;
};

template<typename Tg, typename L, typename ALT >
struct find_advice_helper;

template<typename Tg, typename L, typename ALT, int Pos, int Len, typename AliasList>
struct find_advice_impl_1;

template<typename Tg, typename L, typename ALT, int Pos, int Len, typename AliasList>
struct find_advice_impl_2;

template<typename Tg, typename L, typename ALT, int Pos, int Len, typename Cond, typename AliasList>
struct find_advice_impl_3;

template<typename Tg, typename L, typename ALT, int Len, typename AliasList, int RecursiveAlias>
struct find_advice_impl_4;

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
 : find_advice_impl_1<Tg, L, ALT, 0, length<L>::value, fas::empty_list >
{
};

/// //////////////////////


template<typename Tg, typename L, typename ALT, int Pos, int Len, typename AliasList>
struct find_advice_impl_1
{
  typedef typename type_at_c<Pos, L>::fulltail current_list;
  enum { position = index_of_if< current_list, is_has_tag< _, Tg > >::value };

  typedef typename find_advice_impl_2< Tg, L, ALT, ( position == -1 ? Len : Pos +  position ), Len, AliasList>::type type;
};

template<typename Tg, typename L, int Len, typename AliasList>
struct find_advice_impl_2<Tg, L, _no_alternative_, Len, Len, AliasList>
{
  enum { error = advice_not_found<Tg, empty_type>::value };
  typedef empty_type type;
};

template<typename Tg, typename L, typename ALT, int Len, typename AliasList>
struct find_advice_impl_2<Tg, L, ALT, Len, Len, AliasList >
{
  typedef ALT type;
};

template<typename Tg, typename L, typename ALT, int Pos, int Len, typename AliasList>
struct find_advice_impl_2
{
  typedef typename type_at_c<Pos, L>::type current;
  typedef int_<
    is_alias<current>::value
    + (is_forward<current>::value<<1)
    + (is_remover<current>::value<<2)
  > condition;
  typedef typename find_advice_impl_3< Tg, L, ALT, Pos, Len, condition, AliasList >::type type;
};

template<typename Tg, typename L, typename ALT, int Pos, int Len, typename AliasList>
struct find_advice_impl_3<Tg, L, ALT, Pos, Len, int_<advace_category::advice>, AliasList >
{
  typedef typename type_at_c<Pos, L>::type type;
};

template<typename Tg, typename L, typename ALT, int Pos, int Len, typename AliasList>
struct find_advice_impl_3<Tg, L, ALT, Pos, Len, int_<advace_category::alias>, AliasList >
{
  typedef typename type_at_c<Pos, L>::type alias_type;
  typedef typename target_cast<alias_type>::type alias_tag;
  enum { error = fas::index_of< alias_tag, AliasList>::value };
  typedef typename find_advice_impl_4< alias_tag, L, ALT, Len, AliasList, error >::type type;
};

template<typename Tg, typename L, typename ALT, int Pos, int Len, typename AliasList>
struct find_advice_impl_3<Tg, L, ALT, Pos, Len, int_<advace_category::forward>, AliasList >
{
  typedef typename type_at_c<Pos, L>::type forward_type;
  typedef typename find_advice_impl_1< typename target_cast<forward_type>::type, L, ALT, Pos + 1, Len, AliasList >::type type;
};

template<typename Tg, typename L, typename ALT, int Pos, int Len, typename AliasList>
struct find_advice_impl_3<Tg, L, ALT, Pos, Len, int_<advace_category::removed>, AliasList >
{
  enum { error = advice_has_been_removed<Tg, empty_type>::value };
  typedef empty_type type;
};

template<typename Tg, typename L, typename ALT, int Len, typename AliasList, int RecursiveAlias>
struct find_advice_impl_4
{
  enum { error = recursive_alias<Tg, AliasList, empty_type>::value };
  typedef fas::empty_type type;
};

template<typename Tg, typename L, typename ALT, int Len, typename AliasList>
struct find_advice_impl_4<Tg, L, ALT, Len, AliasList, -1>
{
  typedef typename push_front< Tg, AliasList >::type alias_list;
  typedef typename find_advice_impl_1< Tg, L, ALT, 0, Len, alias_list >::type type;
};


}}

#endif
