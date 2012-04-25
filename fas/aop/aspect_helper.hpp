//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_ASPECT_HELPER_HPP
#define FAS_AOP_ASPECT_HELPER_HPP

#include <fas/aop/aspect_select.hpp>
#include <fas/aop/group_call.hpp>
#include <fas/aop/is_advice.hpp>
#include <fas/aop/is_alias.hpp>
#include <fas/aop/is_group.hpp>
#include <fas/aop/is_remove_advice.hpp>
#include <fas/aop/is_forward.hpp>
#include <fas/aop/is_has_tag.hpp>
#include <fas/aop/tag_cast.hpp>


#include <fas/type_list/unique.hpp>
#include <fas/type_list/merge.hpp>
#include <fas/type_list/tail.hpp>
#include <fas/type_list/head.hpp>

#include <fas/algorithm/erase_if.hpp>
#include <fas/algorithm/transform_tail_if.hpp>
#include <fas/algorithm/transform.hpp>

#include <fas/mp/placeholders.hpp>
#include <fas/mp/a.hpp>
#include <fas/mp/p.hpp>

#include <fas/integral/or_.hpp>

namespace fas{
  
template<typename A>
struct aspect_helper
{
  typedef A aspect_type;
 
  typedef or_< is_alias<_1>, is_forward<_1> > ctrl_marks;
  typedef or_< is_remove_advice<_1>, ctrl_marks > marks;
  typedef or_< is_advice<_1>, marks > items;

  typedef typename aspect_select<aspect_type, items >::type advice_list1;
  
  typedef erase_if<
            tail< _1 >,
            a< is_has_tag< p<_>, tag_cast< head< _1 > > > >
          > remove_from_tail;
  
  typedef typename transform_tail_if<
    advice_list1,
    remove_from_tail,
    is_remove_advice<_>
  >::type common_list1;
  
  typedef typename erase_if< common_list1, ctrl_marks >::type advice_list;
  
  typedef typename aspect_select_t<aspect_type, is_group>::type group_list;
  
  typedef typename unique<typename transform_t<group_list, tag_cast >::type >::type group_tags;
  
  typedef typename transform<group_tags, group_call<_> >::type group_calls;
  
  typedef typename merge<group_calls, common_list1>::type common_list2;
  
  typedef typename unique<common_list2>::type common_list;
  
  typedef typename merge<group_calls, advice_list>::type hierarchy_list2;
  
  typedef typename unique<hierarchy_list2>::type hierarchy_list;
};

}

#endif
