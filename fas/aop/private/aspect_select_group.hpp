//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//


#ifndef FAS_AOP_ASPECT_SELECT_GROUP_HPP
#define FAS_AOP_ASPECT_SELECT_GROUP_HPP

#include <fas/aop/private/aspect_select.hpp>
#include <fas/aop/is_group.hpp>
#include <fas/aop/is_has_tag.hpp>
#include <fas/aop/target_cast.hpp>

#include <fas/algorithm/transform.hpp>

#include <fas/type_list/organize.hpp>
#include <fas/type_list/organize.hpp>
#include <fas/type_list/length.hpp>
#include <fas/typemanip/if_c.hpp>
#include <fas/integral/and_.hpp>

namespace fas{

  /*
template<typename L, typename Tg, bool IsAdvice>
struct aspect_select_group
{
  typedef typename select<L, is_has_tag<_1, Tg> >::type type1;
  typedef typename transform_t<type1, target_cast>::type type2;
  typedef typename organize<type2>::type type3;
  typedef typename unique_first<type3>::type type;
};

template<typename L, typename Tg>
struct aspect_select_group<L, Tg, true>
{
  typedef type_list<Tg> type;
};*/

}

#endif
