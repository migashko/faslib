//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_CREATOR_HPP
#define FAS_AOP_CREATOR_HPP

#include <fas/aop/metalist.hpp>

namespace fas{

template<typename Tg, typename M >
struct creator
{
  typedef metalist::advice metatype;
  typedef Tg tag;
  typedef creator<Tg, M> advice_class;

  advice_class& get_advice() { return *this;}
  const advice_class& get_advice() const { return *this;}

  template<typename T>
  struct apply
  {
    typedef M type;
  };
  
  template<typename T>
  M operator()(T&) const
  {
    return M();
  }

  template<typename T, typename P1>
  M operator()(T&, P1 p1) const
  {
    return M(p1);
  }
  
  template<typename T, typename P1, typename P2>
  M operator()(T&, P1 p1, P2 p2) const
  {
    return M(p1, p2);
  }

  template<typename T, typename P1, typename P2, typename P3>
  M operator()(T&, P1 p1, P2 p2, P3 p3) const
  {
    return M(p1, p2, p3);
  }

  template<typename T, typename P1, typename P2, typename P3, typename P4>
  M operator()(T&, P1 p1, P2 p2, P3 p3, P3 p4) const
  {
    return M(p1, p2, p3, p4);
  }

  template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
  M operator()(T&, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) const
  {
    return M(p1, p2, p3, p4, p5);
  }
};

}

#endif
