  //
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011, 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_ASPECT_HELPER_HPP
#define FAS_AOP_ASPECT_HELPER_HPP

#include <fas/aop/private/aspect_select.hpp>
#include <fas/aop/private/group_call.hpp>
#include <fas/aop/is_advice.hpp>
#include <fas/aop/is_alias.hpp>
#include <fas/aop/is_group.hpp>
#include <fas/aop/is_remove_advice.hpp>
#include <fas/aop/is_forward.hpp>
#include <fas/aop/is_has_tag.hpp>
#include <fas/aop/tag_cast.hpp>


#include <fas/type_list/unique.hpp>
#include <fas/type_list/unique_first.hpp>
#include <fas/type_list/merge.hpp>
#include <fas/type_list/tail.hpp>
#include <fas/type_list/head.hpp>

#include <fas/algorithm/erase_if.hpp>
#include <fas/algorithm/transform_tail_if.hpp>
#include <fas/algorithm/transform.hpp>
#include <fas/algorithm/transform_if.hpp>
#include <fas/algorithm/any.hpp>

#include <fas/mp/placeholders.hpp>
#include <fas/mp/a.hpp>
#include <fas/mp/p.hpp>


#include <fas/integral/or_.hpp>

namespace fas{

template<typename A>
struct aspect_helper
{
  typedef A aspect_type;

public:
  // строим плоский список
  typedef typename aspect_select_t< 
    aspect_type, 
    any
  >::type flat_list;
  
  // метафункция удаления из хвоста списка элементов с тегом элемента головы списка 
  typedef erase_if<
    /*tail< */_1 /*>*/,
    a< is_has_tag< p<_1>, tag_cast< head< _1 > > > >
  > remove_from_tail;

public:
  
  // для каждого remove_advice<_tag_> в списке удаляем элементы _tag_ расположенные за ним
  typedef typename transform_tail_if<
    flat_list,
    remove_from_tail,
    is_remove_advice<_1>
  >::type net_list;

  // заменяем group<_tag_> на group_call<_tag_> и оставляем первое вхождение
  // это список по которому будет производиться поиск с помощью find_advice
  typedef typename unique_first<
    typename transform_if<
      net_list, 
      group_call< tag_cast< _1 > > ,
      is_group<_>
    >::type 
  >::type common_list;
  
  // удаляем из общего списка элементы alias и forward
  // на базе этого списка будет строиться иерархия
  typedef typename erase_if<
    common_list,
    or_< is_alias<_1>, is_forward<_1> >
  >::type hierarchy_list;

  // извлекаем элементы group<_tag_>
  // этот список использует group_call для групповых вызовов
  /*typedef typename aspect_select_t<
    aspect_type,
    is_group
  >::type group_list;
  */

  typedef typename select_t<
    net_list,
    is_group
  >::type group_list;

};
}

#endif
