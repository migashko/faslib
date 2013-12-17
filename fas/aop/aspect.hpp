//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_ASPECT_HPP
#define FAS_AOP_ASPECT_HPP

#include <fas/aop/metalist.hpp>
#include <fas/type_list/empty_list.hpp>

#if __cplusplus >= 201103L

#include <fas/type_list/type_list_n.hpp>
namespace fas{

template<typename ... Args>
struct aspect
{
  typedef typename type_list_n<Args...>::type advice_list;
  typedef metalist::aspect metatype;
};

}
  
#else

namespace fas{

#include <fas/type_list/normalize.hpp>
  
template<typename L = empty_list>
struct aspect
{
  typedef typename normalize<L>::type advice_list;
  typedef metalist::aspect metatype;
};

}

#endif



#endif
