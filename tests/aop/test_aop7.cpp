//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/type_list.hpp>
#include <fas/aop.hpp>
#include <fas/mp.hpp>
#include <fas/static_check/static_check.hpp>
#include <map>

using fas::w;
using fas::_1;
using fas::_2;
using fas::_3;
using fas::_4;


struct _map_;

struct aspect1: fas::aspect< fas::type_list_n<
  fas::advice<_map_, w < std::map<_1, _2, _3, _4> > >
>::type>{};




int main()
{
  typedef fas::aspect_class<aspect1> class1;
  class1 c1;
  return 0;
}
