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
#include <fas/aop/is_aspect.hpp>
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
#include <fas/algorithm/transform_tail.hpp>
#include <fas/algorithm/transform.hpp>
#include <fas/algorithm/transform_if.hpp>
#include <fas/algorithm/any.hpp>

#include <fas/mp/placeholders.hpp>
#include <fas/mp/a.hpp>
#include <fas/mp/p.hpp>


#include <fas/integral/or_.hpp>
#include <fas/integral/and_.hpp>
#include <fas/typemanip/empty_type.hpp>
#include <fas/typemanip/is_empty_type.hpp>
#include <fas/typemanip/switch_.hpp>
#include <fas/typemanip/case_.hpp>
#include <fas/typemanip/default_.hpp>

namespace fas{

template<typename A>
struct aspect_helper
{
  typedef A aspect_type;

public:
  // выбираем все элементы всех аспектов (любого уровня вложенности)
  // и строим плоский список эементов
  
  typedef typename aspect_select_t<
    aspect_type,
    any
  >::type flat_list1;


private:
  
  // метафункция заменяет все элемнты в списке, тег которых совпадает с тегом первого
  // элемента списка на empty_type (в том числе и первый элемент)
  typedef transform_if<
    tail<_1>,
    empty_type,
    a< is_has_tag< p<_1>, tag_cast< head< _1 > > > >
  > replace_removed;

public:

    ///  ------------------------
/*
  typedef a< and_< is_group< p<_1> >, is_has_tag< p<_1>, tag_cast< head<_1> > > > > mf_if_group_has_tag;
  // Извлекает все элементы с тегом, как у первого элемента в списке
  typedef select< _1, mf_if_group_has_tag > mf_select_by_head_tag;
  // Извлекает списки тегов, определенные в поле target, у каждого элемента списка
  typedef organize< transform_if< mf_select_by_head_tag, a< target_cast< p<_1> > >, a< is_group< p<_1> > > > > mf_get_target;
  // Строит новый, общий,  элемент group, из множества других в списке (они больше не нужны), с общим списком целей
  typedef group< tag_cast< head< _1 >  >, mf_get_target > mf_group;
  // Удаляет все элементы с тегом, как у первого элемента в списке
  typedef erase_if< _1, mf_if_group_has_tag > mf_erase_group_by_head_tag;
  //
  typedef merge< mf_group, mf_erase_group_by_head_tag> mf_rebuild_group;

  ///  ------------------------

  typedef a< is_has_tag< p<_1>, tag_cast< head<_1> > > > mf_if_head_has_tag;
  typedef merge< head<_1>, erase_if< tail<_1>, mf_if_head_has_tag > >  mf_erase_by_head_tag;
  */
  //typedef erase_if< replace_removed, a< is_empty_type< p< _1 > > > > mf_erase_by_head_tag;

  /*
  typedef typename transform_tail<
    flat_list1,
    switch_<
      case_< is_group< head< _1 > >, mf_rebuild_group >,
      case_< is_remove_advice< head< _1 > >, mf_erase_by_head_tag >,
      default_< _1 >
    >
  >::type replaced_list2;
  typedef typename organize<replaced_list2>::type  replaced_list3;*/


  // заменяем remove_advice и следующие за ним элементы с такми же тегом на empty_type
  typedef typename transform_tail_if<
    flat_list1,
    merge< head<_1>, replace_removed >,
    is_remove_advice<_1>
  >::type replaced_list;

  // удаляем empty_type из списка
  typedef /*typename erase_if_t<*/
    replaced_list/*,
    is_remove_advice
  >::type*/ net_list;
  /*typedef typename erase_if_t<
    replaced_list,
    is_empty_type
  >::type net_list;*/

  // заменяем group<_tag_> на group_call<_tag_> и удаляем дубликаты элементов, оставляя первое вхождение
  // это список по которому будет производиться поиск с помощью find_advice
  typedef typename unique_first<
    typename transform_if<
      net_list,
      group_caller< tag_cast< _1 > > ,
      is_group<_>
    >::type
  >::type common_list;

  // удаляем из общего списка элементы alias и forward
  // на базе этого списка будет строиться иерархия
  typedef typename erase_if<
    common_list,
    or_< is_alias<_1>, is_forward<_1> >
  >::type hierarchy_list;

  // формируем список состоящий только из груп
  typedef typename select_t<
    net_list,
    is_group
  >::type group_list1;

  ///  ------------------------

  // typedef typename select_t<replaced_list, is_group>::type group_list1;
  
  typedef a< and_< is_group< p<_1> >, is_has_tag< p<_1>, tag_cast< head<_1> > > > > mf_if_group_has_tag;
  // Извлекает все элементы с тегом, как у первого элемента в списке
  typedef select< _1, mf_if_group_has_tag > mf_select_by_head_tag;
  // Извлекает списки тегов, определенные в поле target, у каждого элемента списка
  typedef unique_first< organize< transform_if< mf_select_by_head_tag, a< target_cast< p<_1> > >, a< is_group< p<_1> > > > > > mf_get_target;
  // Строит новый, общий,  элемент group, из множества других в списке (они больше не нужны), с общим списком целей
  typedef group< tag_cast< head< _1 >  >, mf_get_target > mf_group;
  // Удаляет все элементы с тегом, как у первого элемента в списке
  typedef erase_if< _1, mf_if_group_has_tag > mf_erase_by_head_tag;
  // 
  typedef merge< mf_group, mf_erase_by_head_tag> mf_rebuild_group;

  ///  ------------------------

  typedef typename transform_tail<
    group_list1,
    mf_rebuild_group
    /*switch_<
      case_< is_group< head< _1 > >, mf_rebuild_group >,
      default_< _1 >
    >*/
  >::type group_list;

  /*
  typedef typename transform_tail<
    group_list1,
    merge<
      group<
        tag_cast< head< _1 >  >,
        organize<
          transform<
            select< _1, a< is_has_tag< p<_1>, tag_cast< head<_1> > > > >,
            a< target_cast< p<_1> > >
          >
        > // transform_if
      >, // group
      erase_if<
        _1,
        a< is_has_tag<
          p<_1>,
          tag_cast< head<_1> >
        > >
      >
    >
  >::type group_listX;
  */
};
}

#endif
