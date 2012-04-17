// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_DETAIL_MAKE_ADVICE_LIST_HPP
#define FAS_AOP_DETAIL_MAKE_ADVICE_LIST_HPP

#include <fas/aop/metalist.hpp>
#include <fas/aop/is_has_tag.hpp>
#include <fas/mp/placeholders.hpp>
//#include <fas/aop/is_advice.hpp>
#include <fas/aop/aspect_select.hpp>
//#include <fas/type_list/metalist.hpp>
//#include <fas/type_list/merge.hpp>
//#include <fas/type_list/el.hpp>
//#include <fas/type_list/make_type_list.hpp>
//#include <fas/type_list/unique.hpp>
//#include <fas/algorithm/find_if.hpp>
//#include <fas/type_selection/if_c.hpp>

namespace fas{ namespace detail{
  


template<typename A>
struct make_advice_list_helper
{
  // typedef typename aspect_select<A, is_advice< p< a< _1> > > >::type advice_list;
  //typedef typename aspect_select<A, is_advice< a<_1> > >::type advice_list;
  //typedef typename aspect_select_t<A, is_advice >::type advice_list;
  //typedef typename unique<advice_list>::type type;
  //typedef advice_list type;
  /*
  // выгребаем все сущности 
  typedef typename aspect_select<A>::type entity_list;
  // строим список адвайсов с учетом алиасов
  typedef typename make_advice_list_impl<entity_list, empty_list>::type advice_list;
  typedef typename unique_first_if<
    advice_list,
    a< some_type< 
      has_tag< a< _1 > >, 
      has_tag< p< a< _1 > > > 
    > > 
  >::type type;
  */

};

/*
template<typename Tg, typename L >
struct find_advice_impl<-1, Tg, L>
{
  typedef empty_type type;
};

template<int P, typename Tg, typename L >
struct find_advice_impl
{
  typedef type_at_c<P, L> type_at_type;
  typedef typename type_at_type::type head;
  typedef typename type_at_type::fulltail tail;
  typedef typename find_advice_impl2<typename head::metatype, Tg, tail>::type type;
};

template<typename Tg, typename L >
struct find_advice_impl2<metalist::advice, Tg, L>
{
  typedef typename L::left_type type;
};

template<typename Tg, typename L >
struct find_advice_impl2<metalist::alias, Tg, L>
{
  typedef typename L::left_type head;
  typedef typename L::right_type tail;
  // продолжаем поиск в хвосте
  typedef typename find_advice_helper<typename head::target, tail>::type type;
};
*/


}}

#endif
