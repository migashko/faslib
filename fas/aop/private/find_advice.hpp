//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_FIND_ADVICE_HPP
#define FAS_AOP_FIND_ADVICE_HPP

#include <fas/aop/detail/find_advice.hpp>

namespace fas{

template<typename Tg, typename L, typename ALT = _no_alternative_ >
struct find_advice
{
  // it's worked, but very long compiled
  // compile time for tutorial/aop/aop15 : 0m19.857s

  /*
  typedef typename find_if< L, is_has_tag<_1, Tg > >::type firts_item;
  typedef pair< firts_item , L > initial;
  typedef is_alias< first< _1 > > cond;
  typedef index_of< first<_1>, second< _1 > > find_index;
  typedef second< split< find_index, second< _1 > > > tail_list; 
  typedef find_if< tail_list, a< is_has_tag< p<_1> , target< first<_1> > > > > find_func;
  typedef pair< find_func, tail_list> doit;
  typedef typename for_< initial, doit, cond >::type::first type;
  */

  // compile time for tutorial/aop/aop15 : 0m2.621s (g++-4.7), 43.12s (g++-3.3)
  typedef typename detail::find_advice_impl<Tg, L, ALT >::type type;
};

}

#endif
