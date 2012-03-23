// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_DETAIL_FIND_ADVICE_HPP
#define FAS_AOP_DETAIL_FIND_ADVICE_HPP

#include <fas/aop/metalist.hpp>
#include <fas/aop/is_has_tag.hpp>
#include <fas/aop/is_alias.hpp>
#include <fas/type_list/metalist.hpp>
#include <fas/type_list/index_of.hpp>
//#include <fas/type_list/merge.hpp>
//#include <fas/type_list/el.hpp>
//#include <fas/type_list/make_type_list.hpp>
//#include <fas/algorithm/find_if.hpp>
#include <fas/typemanip/if_c.hpp>
#include <fas/algorithm/index_of_if.hpp>
#include <fas/algorithm/find_if.hpp>
#include <fas/mp/bind.hpp>

namespace fas{ 

struct _alternative_;
struct _no_alternative_;

template<typename Tg, typename T>
struct advice_not_found { enum { value = 0 }; };

template<typename Tg>
struct advice_not_found<Tg, empty_type>;

  
namespace detail 
{
  
template<typename Tg, typename L, typename C, typename ALT, int B >
struct find_advice_impl;


template<typename Tg, typename L, typename ALT >
struct find_advice_helper
{
  typedef find_if_t< L, bind2nd<is_has_tag, Tg>::template apply > helper;
  typedef typename helper::type current;
  typedef typename helper::tail tail;

  //enum { error = advice_not_found<Tg, current>::value };
  typedef typename find_advice_impl<Tg, tail, current, ALT, is_alias<current>::value >::type type;
};

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


template<typename Tg, typename L, typename C, typename ALT, int B >
struct find_advice_impl
{
  typedef typename find_advice_helper<
    typename C::target,
    L,
    ALT
  >::type type;
};
  
template<typename Tg, typename L>
struct find_advice_impl<Tg, L, empty_type, _no_alternative_, false>
{
  enum { error = advice_not_found<Tg, empty_type>::value };
  typedef empty_type type;
};

template<typename Tg, typename L, typename ALT>
struct find_advice_impl<Tg, L, empty_type, ALT, false>
{
  enum { error = 0 };
  typedef ALT type;
};

template<typename Tg, typename L, typename C, typename ALT>
struct find_advice_impl<Tg, L, C, ALT, false>
{
  enum { error = 0 };
  typedef C type;
};

}}

#endif
