//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011, 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_ASPECT_HIERARCHY_HPP
#define FAS_AOP_ASPECT_HIERARCHY_HPP

#include <fas/aop/private/aspect_helper.hpp>
#include <fas/aop/private/find_advice.hpp>
#include <fas/aop/detail/select_group.hpp>
#include <fas/aop/detail/has_advice.hpp>

#include <fas/hierarchy/scatter_hierarchy.hpp>
#include <fas/hierarchy/field.hpp>

namespace fas{

template<typename A>
class aspect_hierarchy
  : public scatter_hierarchy< typename aspect_helper<A>::hierarchy_list >
{
  typedef aspect_helper<A> helper;
public:
  typedef typename helper::hierarchy_list hierarchy_list;
  typedef typename helper::common_list common_list;
  typedef typename helper::group_list group_list;

  typedef scatter_hierarchy< hierarchy_list > super;

  template<typename Tg>
  typename find_advice< Tg, common_list>::type::advice_class&
  get()
  {
    typedef typename find_advice< Tg, common_list>::type advice_type;
    return field<advice_type>::get( static_cast<super&>(*this) ).get_advice();
  }

  template<typename Tg>
  const typename find_advice< Tg, common_list>::type::advice_class&
  get() const
  {
    typedef typename find_advice< Tg, common_list>::type advice_type;
    return field<advice_type>::get_const( static_cast<const super&>(*this) ).get_advice();
  }

  template<typename Tg>
  struct advice_cast
  {
    typedef typename find_advice< Tg, common_list>::type::advice_class type;
  };

  template<typename Tg>
  struct has_advice
  {
    typedef detail::has_advice_aspect<Tg, aspect_hierarchy<A> > helper;
    typedef typename helper::type type;
    enum { value = helper::value};
  };

  template<typename Tg>
  group_object<Tg> getg() const
  {
    return group_object<Tg>();
  }

  template<typename Tg>
  struct select_group
  {
    typedef typename detail::select_group_aspect< Tg, aspect_hierarchy<A> >::type type;
  };
};

}

#endif
