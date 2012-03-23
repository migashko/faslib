// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_FIND_ADVICE_HPP
#define FAS_AOP_FIND_ADVICE_HPP

#include "detail/find_advice.hpp"
#include <fas/algorithm/find_if.hpp>
#include <fas/algorithm/do_while.hpp>
#include <fas/type_list/split.hpp>
#include <fas/type_list/index_of.hpp>
#include <fas/typemanip/pair.hpp>
#include <fas/typemanip/first.hpp>
#include <fas/typemanip/second.hpp>
#include <fas/integral/not_.hpp>
#include <fas/integral/and_.hpp>
#include <fas/aop/is_has_tag.hpp>
#include <fas/aop/is_alias.hpp>

namespace fas{

// L - список адвайсов, полученных через aspect_select
template<typename Tg, typename L, typename ALT = _no_alternative_ >
struct find_advice
{
  // it's worked, but very long compiled
  // compile time for tutorial/chain/chain4 : 0m19.857s

  /*
  typedef typename find_if< L, is_has_tag<_1, Tg > >::type firts_item;
  typedef pair< firts_item , L > initial;
  typedef is_alias< first< _1 > > cond;
  typedef index_of< first<_1>, second< _1 > > find_index;
  typedef second< split< find_index, second< _1 > > > tail_list; 
  typedef find_if< tail_list, a< is_has_tag< p<_1> , target< first<_1> > > > > find_func;
  typedef pair< find_func, tail_list> doit;
  typedef typename do_while< initial, doit, cond >::type::first type;
  */

  // compile time for tutorial/chain/chain4 : 0m2.621s
  typedef typename detail::find_advice_helper<Tg, L, ALT >::type type;
};

/// /////////////////////////////////////////

/*
template<typename Tg, typename L>
struct advice_cast
{
  typedef typename find_advice< Tg, L>::type::advice_class type;
};

template<typename Tg, typename L>
struct has_advice
{
  typedef index_of_if_t< L, bind2nd<is_has_tag, Tg>::template apply > helper;
  enum { value = helper::value!=-1 };
};
*/

/*
template<typename Tg, typename T>
typename advice_cast<Tg, typename T::advice_list>::type&
get_advice(T& t)
{
  return t.get_aspect().template get<Tg>();
}

template<typename Tg, typename T>
const typename advice_cast<Tg, typename T::advice_list>::type&
get_advice(const T& t)
{
  return t.get_aspect().template get<Tg>();
}
*/
/// /////////////////////////////////////////


/*
template<typename Tg, typename L1, typename L2>
struct alter_cast
{
  typedef typename find_advice< 
    Tg, L1,
    typename find_advice<Tg, L2>::type
  >::type::advice_class type;
};

template<typename Tg, typename T1, typename T2>
typename alter_cast<Tg, typename T1::aspect::advice_list, typename T2::aspect::advice_list>::type&
get_advice_helper(T1& t1, T2& t2, bool_<true>)
{
  return t1.get_aspect().template get<Tg>();
};

template<typename Tg, typename T1, typename T2>
typename alter_cast<Tg, typename T1::aspect::advice_list, typename T2::aspect::advice_list>::type&
get_advice_helper(T1& t1, T2& t2, bool_<false>)
{
  return t2.get_aspect().template get<Tg>();
};

template<typename Tg, typename T1, typename T2>
const typename alter_cast<Tg, typename T1::aspect::advice_list, typename T2::aspect::advice_list>::type&
get_advice_helper(const T1& t1, const T2& t2, bool_<true>)
{
  return t1.get_aspect().template get<Tg>();
};

template<typename Tg, typename T1, typename T2>
const typename alter_cast<Tg, typename T1::aspect::advice_list, typename T2::aspect::advice_list>::type&
get_advice_helper(const T1& t1, const T2& t2, bool_<false>)
{
  return t2.get_aspect().template get<Tg>();
};


template<typename Tg, typename T1, typename T2>
typename alter_cast<Tg, typename T1::aspect::advice_list, typename T2::aspect::advice_list>::type&
get_advice(T1& t1, T2& t2)
{
  return get_advice_helper<Tg>(t1, t2, bool_< has_advice<Tg, typename T1::aspect::advice_list>::value >() );
};

template<typename Tg, typename T1, typename T2>
const typename alter_cast<Tg, typename T1::aspect::advice_list, typename T2::aspect::advice_list>::type&
get_advice(const T1& t1, const T2& t2)
{
  return get_advice_helper<Tg>(t1, t2, bool_< has_advice<Tg, typename T1::aspect::advice_list>::value >() );
};
*/

}

#endif
