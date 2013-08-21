//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/type_list.hpp>
#include <fas/aop.hpp>
#include <fas/mp.hpp>
#include <fas/typemanip.hpp>
#include <fas/static_check/static_check.hpp>
#include <map>
#include <set>
#include <string>

using fas::w;
using fas::_;


struct _map1_;
struct _map2_;
struct _map3_;
struct _map4_;
struct _value_;

struct aspect1: fas::aspect< fas::type_list_n<
  fas::type_advice<_map1_, w< std::set<_,_,_> > >,
  fas::alias< _map3_, _map4_>,
  fas::forward< _map2_, _map4_>,
  fas::forward< _map4_, _map1_>,
  fas::type_advice<_map1_, w< std::map<_,_,_,_> > >,
  fas::value_advice<_value_, int>
>::type>{};

int main()
{
  typedef fas::aspect_class<aspect1> class1;
  class1 c1;
  c1.get_aspect().get<_value_>() = 10;
  typedef class1::aspect::advice_cast<_map2_>::type wmap_type;
  typedef std::map<int, std::string> orig_map;
  typedef fas::apply<
              wmap_type::type,
              orig_map::key_type,
              orig_map::mapped_type,
              orig_map::key_compare,
              orig_map::allocator_type
          >::type map_type;
  map_type mt;
  mt[10]="test";
  return 0;
}
