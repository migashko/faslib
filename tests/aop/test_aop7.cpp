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
using fas::_;


struct _map_;
struct _value_;

struct aspect1: fas::aspect< fas::type_list_n<
  fas::type_advice<_map_, w < std::map<_,_,_,_> > >,
  fas::value_advice<_value_, int>
>::type>{};

int main()
{
  typedef fas::aspect_class<aspect1> class1;
  class1 c1;
  c1.get_aspect().get<_value_>() = 10;
  return 0;
}
