//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/type_list/type_list.hpp>
#include <fas/static_check.hpp>
#include <fas/algorithm/find_if.hpp>
#include <fas/typemanip/super_subclass.hpp>
#include <fas/typemanip/super_subclass_strict.hpp>

using namespace ::fas;

struct A{};
struct B:A{};
struct C{};
struct D:C{};

struct abc_list: type_list< A, type_list<B, type_list<C, type_list<D> > > > {};

int main()
{
  using namespace ::fas;

  enum 
  {
    test = static_check< same_type< C, find_if< abc_list, super_subclass<_1, D> >::type >::value == 1 >::value
         + static_check< same_type< D, find_if< abc_list, super_subclass<D, _1> >::type >::value == 1 >::value
         + static_check< same_type< D, find_if< abc_list, super_subclass_strict<C, _1> >::type >::value == 1 >::value
         + static_check< same_type< empty_type, find_if< abc_list, super_subclass_strict<_1, C> >::type >::value == 1 >::value
  };

  return 0;
}
