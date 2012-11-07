//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011, 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_PRIVATE_GROUP_OBJECT_HPP
#define FAS_AOP_PRIVATE_GROUP_OBJECT_HPP

#include <fas/aop/detail/group_helper.hpp>
#include <fas/aop/metalist.hpp>
#include <fas/aop/select_group.hpp>

namespace fas {

template<typename Tg>
class group_object
{
public:

  typedef metalist::advice metatype;
  typedef Tg tag;
  typedef group_object<Tg> advice_class;

  advice_class& get_advice() { return *this;}
  const advice_class& get_advice() const { return *this;}

  template<typename T, typename F>
  F for_each(T& t, F f) const
  {
    typedef typename select_group<Tg, T>::type tag_list;
    return detail::group_helper().for_each( tag_list(), t, f);
  }

  template<typename T>
  void operator()(T& t) const
  {
    typedef typename select_group< Tg, T>::type tag_list;
    detail::group_helper().call(tag_list(), t);
  }

  template<typename T, typename P1>
  void operator()(T& t, P1 p1)  const
  {
    typedef typename select_group< Tg, T>::type tag_list;
    detail::group_helper().call(tag_list(), t, p1);
  }

  template<typename T, typename P1, typename P2>
  void operator()(T& t, P1 p1, P2 p2)  const
  {
    typedef typename select_group< Tg, T>::type tag_list;
    detail::group_helper().call(tag_list(), t, p1, p2);
  }

  template<typename T, typename P1, typename P2, typename P3>
  void operator()(T& t, P1 p1, P2 p2, P3 p3)  const
  {
    typedef typename select_group< Tg, T>::type tag_list;
    detail::group_helper().call(tag_list(), t, p1, p2, p3);
  }

  template<typename T, typename P1, typename P2, typename P3, typename P4>
  void operator()(T& t, P1 p1, P2 p2, P3 p3, P4 p4) const
  {
    typedef typename select_group< Tg, T>::type tag_list;
    detail::group_helper().call(tag_list(), t, p1, p2, p3, p4);
  }

  template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
  void operator()(T& t, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) const
  {
    typedef typename select_group< Tg, T>::type tag_list;
    detail::group_helper().call(tag_list(), t, p1, p2, p3, p4, p5);
  }
};

}

#endif
