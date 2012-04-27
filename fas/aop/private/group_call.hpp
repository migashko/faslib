//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_GROUP_CALL_HPP
#define FAS_AOP_GROUP_CALL_HPP

#include <fas/aop/detail/group_call.hpp>

#include <fas/aop/metalist.hpp>
#include <fas/aop/advice_cast.hpp>
#include <fas/algorithm/select.hpp>
#include <fas/mp/lambda.hpp>
#include <fas/mp/placeholders.hpp>

namespace fas {

template<typename Tg>
class group_call
{
public:
  
  typedef metalist::advice metatype;
  typedef Tg tag;
  typedef group_call<Tg> advice_class;

  advice_class& get_advice() { return *this;}
  const advice_class& get_advice() const { return *this;}

  template<typename T, typename F>
  F for_each(T& t, F f)
  {
    typedef typename T::aspect::template select_group<Tg>::type group_tags;
    return detail::for_each_group( group_tags(), t, f );
  }

  template< template<typename> class IF, typename T, typename F>
  F for_each_if_t(T& t, F f)
  {
    typedef typename T::aspect::template select_group<Tg>::type group_tags;
    typedef typename select< group_tags, IF< advice_cast< _ , typename T::aspect  > > >::type selected_tags;
    return detail::for_each_group( selected_tags(), t, f );
  }
  
  template< class IF, typename T, typename F>
  F for_each_if(T& t, F f)
  {
    return for_each_if_t< lambda< FAS_T_SIMPLIFY(IF) >::template apply >(t, f);
  }

  template<typename T>
  void operator()(T& t)
  {
    typedef typename T::aspect::template select_group<Tg>::type group_tags;
    detail::group_call_helper( group_tags(), t);
  }

  template<typename T, typename P1>
  void operator()(T& t, P1 p1)
  {
    typedef typename T::aspect::template select_group<Tg>::type group_tags;
    detail::group_call_helper( group_tags(), t, p1);
  }

  template<typename T, typename P1, typename P2>
  void operator()(T& t, P1 p1, P2 p2)
  {
    typedef typename T::aspect::template select_group<Tg>::type group_tags;
    detail::group_call_helper( group_tags(), t, p1, p2);
  }

  template<typename T, typename P1, typename P2, typename P3>
  void operator()(T& t, P1 p1, P2 p2, P3 p3) 
  {
    typedef typename T::aspect::template select_group<Tg>::type group_tags;
    detail::group_call_helper( group_tags(), t, p1, p2, p3);
  }

  template<typename T, typename P1, typename P2, typename P3, typename P4>
  void operator()(T& t, P1 p1, P2 p2, P3 p3, P4 p4) 
  {
    typedef typename T::aspect::template select_group<Tg>::type group_tags;
    detail::group_call_helper( group_tags(), t, p1, p2, p3, p4);
  }

  template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
  void operator()(T& t, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
  {
    typedef typename T::aspect::template select_group<Tg>::type group_tags;
    detail::group_call_helper( group_tags(), t, p1, p2, p3, p4, p5);
  }
};


}

#endif
