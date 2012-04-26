//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_ASPECT_HIERARCHY_HPP
#define FAS_AOP_ASPECT_HIERARCHY_HPP

#include <fas/aop/aspect_helper.hpp>
#include <fas/aop/find_advice.hpp>
#include <fas/aop/group_call.hpp>
#include <fas/aop/aspect_select_group.hpp>

#include <fas/hierarchy/scatter_hierarchy.hpp>
#include <fas/hierarchy/field.hpp>

#include <fas/algorithm/index_of_if.hpp>
#include <fas/mp/bind2nd.hpp>

namespace fas{
  

template<typename A>
class aspect_hierarchy
  : public scatter_hierarchy< typename aspect_helper<A>::hierarchy_list >
{
  typedef aspect_helper<A> helper;
public:

  typedef typename helper::hierarchy_list hierarchy_list;
  typedef typename helper::common_list advice_list;
  typedef typename helper::group_list group_list;
  typedef scatter_hierarchy< hierarchy_list > super;

  template<typename Tg>
  typename find_advice< Tg, advice_list>::type::advice_class&
  get()
  {
    typedef typename find_advice< Tg, advice_list>::type advice_type;
    return field<advice_type>( static_cast<super&>(*this) ).get_advice();
  };

  template<typename Tg>
  const typename find_advice< Tg, advice_list>::type::advice_class&
  get() const
  {
    typedef typename find_advice< Tg, advice_list>::type advice_type;
    return field<advice_type>( static_cast<const super&>(*this) ).get_advice();
  };

  template<typename Tg>
  struct advice_cast
  {
    typedef typename find_advice< Tg, advice_list>::type::advice_class type;
  };
  
  template<typename Tg>
  struct has_advice
  {
    typedef index_of_if_t< advice_list, bind2nd<is_has_tag, Tg>::template apply > helper;
    
    enum { value = helper::value!=-1 };
    typedef bool_< value!=0 > type;
  };
  
  template<typename Tg>
  group_call<Tg> getg() const
  {
    return group_call<Tg>();
  }

  template<typename Tg>
  struct select_group
  {
    typedef typename aspect_select_group<group_list, Tg>::type type;
  };
};


}

#endif
