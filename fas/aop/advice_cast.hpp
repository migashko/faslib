// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_ADVICE_CAST_HPP
#define FAS_AOP_ADVICE_CAST_HPP

/*
#include <fas/algorithm/find_if.hpp>
#include <fas/type_list/split.hpp>

#include <fas/typemanip/pair.hpp>
#include <fas/typemanip/first.hpp>
#include <fas/typemanip/second.hpp>
#include <fas/integral/not_.hpp>
#include <fas/integral/and_.hpp>
#include <fas/aop/is_has_tag.hpp>
#include <fas/aop/is_alias.hpp>
*/

#include <fas/aop/find_advice.hpp>
#include <fas/type_list/index_of.hpp>
#include <fas/integral/bool_.hpp>
#include <fas/mp/bind.hpp>

namespace fas{


template<typename Tg, typename A>
struct advice_cast
{
  typedef typename find_advice< Tg, typename A::advice_list >::type::advice_class type;
};

template<typename Tg, typename A>
struct has_advice
{
  typedef index_of_if_t< typename A::advice_list, bind2nd<is_has_tag, Tg>::template apply > helper;
  enum { value = helper::value!=-1 };
};

/// /////////////////////////////////////////


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
  return get_advice_helper<Tg>(t1, t2, bool_< has_advice<Tg, typename T1::aspect/*::advice_list*/>::value >() );
};

template<typename Tg, typename T1, typename T2>
const typename alter_cast<Tg, typename T1::aspect::advice_list, typename T2::aspect::advice_list>::type&
get_advice(const T1& t1, const T2& t2)
{
  return get_advice_helper<Tg>(t1, t2, bool_< has_advice<Tg, typename T1::aspect/*::advice_list*/>::value >() );
};

}

#endif
