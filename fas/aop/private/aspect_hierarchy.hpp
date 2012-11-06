//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_ASPECT_HIERARCHY_HPP
#define FAS_AOP_ASPECT_HIERARCHY_HPP

#include <fas/aop/private/aspect_helper.hpp>
#include <fas/aop/private/find_advice.hpp>
#include <fas/aop/private/group_call.hpp>
#include <fas/aop/private/aspect_select_group.hpp>

#include <fas/aop/aspect.hpp>

#include <fas/hierarchy/scatter_hierarchy.hpp>
#include <fas/hierarchy/field.hpp>

#include <fas/type_list/type_list.hpp>
#include <fas/algorithm/index_of_if.hpp>
#include <fas/mp/bind2nd.hpp>

namespace fas{

template<typename A>
struct aspect_common_helper
{
  typedef aspect_helper<A> helper;
  struct common_list: helper::common_list{};
  struct group_list: helper::group_list{};
};

template<typename L>
struct aspect_common_helper< aspect<L> >
{
  typedef aspect_helper< aspect<L> > helper;
  typedef typename helper::common_list common_list;
  typedef typename helper::group_list group_list;
};

template<typename A>
class aspect_hierarchy
  : public scatter_hierarchy< typename aspect_helper<A>::hierarchy_list >
{
  typedef aspect_helper<A> helper;
public:
  typedef typename helper::hierarchy_list hierarchy_list;
  typedef typename aspect_common_helper<A>::common_list common_list;
  typedef typename aspect_common_helper<A>::group_list group_list;

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
    typedef index_of_if_t<
      common_list,
      bind2nd<is_has_tag, Tg>::template apply
    > helper;

    enum { value = helper::value!=-1 };
    typedef bool_< value!=0 > type;
  };

  template<typename Tg>
  group_caller<Tg> getg() const
  {
    return group_caller<Tg>();
  }

  template<typename Tg>
  struct select_group
  {
    typedef typename find_advice< Tg, typename helper::net_list, empty_type >::type type1;

    typedef typename aspect_select_group<
      group_list,
      Tg,
      is_advice<type1>::value && !some_type< type1, empty_type>::value
    >::type type;
  };
};

}

#endif
