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
#include <string>

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

  typedef std::map<int, std::string> orig_map;
  typedef fas::advice_cast<_map_, class1::aspect>::type::type metamap;
  typedef fas::apply<
    metamap,
    orig_map::key_type,
    orig_map::mapped_type,
    orig_map::key_compare,
    orig_map::allocator_type
  >::type map_type;

  map_type m;
  m[1]="test";
  
  return 0;
}
