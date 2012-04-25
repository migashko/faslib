//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_HAS_ADVICE_HPP
#define FAS_AOP_HAS_ADVICE_HPP

#include <fas/mp/bind2nd.hpp>
#include <fas/algorithm/index_of_if.hpp>
#include <fas/aop/is_has_tag.hpp>

namespace fas {

template<typename Tg, typename A>
struct has_advice
{
  typedef index_of_if_t< typename A::advice_list, bind2nd<is_has_tag, Tg>::template apply > helper;
  enum { value = helper::value!=-1 };
};

}

#endif
