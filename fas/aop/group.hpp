//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_GROUP_HPP
#define FAS_AOP_GROUP_HPP

#include <fas/aop/metalist.hpp>
#include <fas/type_list/normalize.hpp>


namespace fas{

template<typename Tg, typename TgL>
struct group
{
  typedef metalist::group metatype;
  typedef Tg tag;
  typedef typename normalize<TgL>::type target;
};

}

#endif
