//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_PRIVATE_GROUP_CALLER_HPP
#define FAS_AOP_PRIVATE_GROUP_CALLER_HPP

#include <fas/aop/detail/group_call.hpp>
#include <fas/aop/metalist.hpp>
#include <fas/aop/advice_cast.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/group_call.hpp>

#include <fas/algorithm/select.hpp>

#include <fas/mp/lambda.hpp>
#include <fas/mp/placeholders.hpp>

#include <fas/type_list/length.hpp>
#include <fas/integral/int_.hpp>


namespace fas {

template<typename Tg>
class group_caller
{
public:

  typedef metalist::advice metatype;
  typedef Tg tag;
  typedef group_caller<Tg> advice_class;

  advice_class& get_advice() { return *this;}
  const advice_class& get_advice() const { return *this;}

  template<typename T, typename F>
  F for_each(T& t, F f) const
  {
    return ::fas::group_for_each<Tg>(t, f);
  }

  
  template< template<typename> class IF, typename T, typename F>
  F for_each_if_t(T& t, F f) const
  {
    typedef typename T::aspect::template select_group<Tg>::type group_tags;
    typedef typename select< group_tags, IF< advice_cast< _ ,  T > > >::type selected_tags;
    return detail::group_helper1::for_each_group( selected_tags(), t, f, int_<0>(), int_< length<selected_tags>::value >() );
  }

  template< class IF, typename T, typename F>
  F for_each_if(T& t, F f) const
  {
    return for_each_if_t< lambda< FAS_T_SIMPLIFY(IF) >::template apply >(t, f);
  }
  

  template<typename T>
  void operator()(T& t) const
  {
    ::fas::group_call<Tg>(t);
  }

  template<typename T, typename P1>
  void operator()(T& t, P1 p1)  const
  {
    ::fas::group_call<Tg>(t, p1);
  }

  template<typename T, typename P1, typename P2>
  void operator()(T& t, P1 p1, P2 p2)  const
  {
    ::fas::group_call<Tg>(t, p1, p2);
  }

  template<typename T, typename P1, typename P2, typename P3>
  void operator()(T& t, P1 p1, P2 p2, P3 p3)  const
  {
    ::fas::group_call<Tg>(t, p1, p2, p3);
  }

  template<typename T, typename P1, typename P2, typename P3, typename P4>
  void operator()(T& t, P1 p1, P2 p2, P3 p3, P4 p4) const
  {
    ::fas::group_call<Tg>(t, p1, p2, p3, p4);
  }

  template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
  void operator()(T& t, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) const
  {
    ::fas::group_call<Tg>(t, p1, p2, p3, p4, p5);
  }
};









  
template<typename Tg, typename T>
struct gth
{
  // struct group_tags: T::aspect::template select_group<Tg>::type {};
  typedef typename T::aspect::template select_group<Tg>::type group_tags;
};

template<typename Tg, template<typename> class T, typename A>
struct gth<Tg, T< aspect<A> > >
{
  typedef typename T< aspect<A> >::aspect::template select_group<Tg>::type group_tags;
};

template<typename Tg>
class group_caller_old
{
public:

  typedef metalist::advice metatype;
  typedef Tg tag;
  typedef group_caller<Tg> advice_class;

  advice_class& get_advice() { return *this;}
  const advice_class& get_advice() const { return *this;}

  template<typename T, typename F>
  F for_each(T& t, F f) const
  {
    typedef typename gth<Tg, T>::group_tags group_tags;
    return detail::group_helper1::for_each_group( group_tags(), t, f, int_<0>(), int_< length<group_tags>::value >() );
  }

  template< template<typename> class IF, typename T, typename F>
  F for_each_if_t(T& t, F f) const
  {
    typedef typename T::aspect::template select_group<Tg>::type group_tags;
    typedef typename select< group_tags, IF< advice_cast< _ , typename T::aspect  > > >::type selected_tags;
    return detail::group_helper1::for_each_group( selected_tags(), t, f, int_<0>(), int_< length<selected_tags>::value >() );
  }

  template< class IF, typename T, typename F>
  F for_each_if(T& t, F f) const
  {
    return for_each_if_t< lambda< FAS_T_SIMPLIFY(IF) >::template apply >(t, f);
  }

  template<typename T>
  void operator()(T& t) const
  {
    typedef typename T::aspect::template select_group<Tg>::type group_tags;
    detail::group_helper1::group_call_helper( group_tags(), t);
  }

  template<typename T, typename P1>
  void operator()(T& t, P1 p1)  const
  {
    typedef typename T::aspect::template select_group<Tg>::type group_tags;
    detail::group_helper1::group_call_helper( group_tags(), t, p1);
  }

  template<typename T, typename P1, typename P2>
  void operator()(T& t, P1 p1, P2 p2)  const
  {
    typedef typename T::aspect::template select_group<Tg>::type group_tags;
    detail::group_helper1::group_call_helper( group_tags(), t, p1, p2);
  }

  template<typename T, typename P1, typename P2, typename P3>
  void operator()(T& t, P1 p1, P2 p2, P3 p3)  const
  {
    typedef typename T::aspect::template select_group<Tg>::type group_tags;
    detail::group_helper1::group_call_helper( group_tags(), t, p1, p2, p3);
  }

  template<typename T, typename P1, typename P2, typename P3, typename P4>
  void operator()(T& t, P1 p1, P2 p2, P3 p3, P4 p4) const
  {
    typedef typename T::aspect::template select_group<Tg>::type group_tags;
    detail::group_helper1::group_call_helper( group_tags(), t, p1, p2, p3, p4);
  }

  template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
  void operator()(T& t, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) const
  {
    typedef typename T::aspect::template select_group<Tg>::type group_tags;
    detail::group_helper1::group_call_helper( group_tags(), t, p1, p2, p3, p4, p5);
  }
};

}

#endif
