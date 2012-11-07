//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011, 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_DETAIL_HAS_ADVICE_HPP
#define FAS_AOP_DETAIL_HAS_ADVICE_HPP

#include <fas/aop/private/is_has_tag.hpp>
#include <fas/aop/private/is_remove_advice.hpp>
#include <fas/algorithm/index_of_if.hpp>
#include <fas/mp/placeholders.hpp>
#include <fas/integral/and_.hpp>
#include <fas/integral/not_.hpp>

namespace fas { namespace detail{

template<typename Tg, typename A>
struct has_advice_helper
{
  typedef index_of_if<
    typename A::common_list,
    and_< is_has_tag< _1, Tg>, not_< is_remove_advice<_1> > >
  > helper;

  enum { value = helper::value!=-1 };
  typedef bool_< value!=0 > type;
};

template<typename Tg, typename A>
struct has_advice_aspect
{
  typedef has_advice_helper<Tg, A> helper;
  typedef typename helper::type type;
  enum { value = helper::value};
};


}}

#endif
