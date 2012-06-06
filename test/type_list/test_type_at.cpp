//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/type_list.hpp>
#include <fas/static_check.hpp>
#include <fas/integral/int_.hpp>

using namespace ::fas;

struct A{};
struct B:A{};
struct C{};
struct D:C{};

struct abc_list: type_list<A, type_list<B, type_list<C, type_list<D> > > > {};

int main()
{
  
  enum {
    test = static_check< some_type<A, type_at< int_<0>, abc_list>::type >::value >::value
         + static_check< some_type<B, type_at< int_<1>, abc_list>::type >::value >::value
         + static_check< some_type<C, type_at< int_<2>, abc_list>::type >::value >::value
         + static_check< some_type<D, type_at< int_<3>, abc_list>::type >::value >::value
         // -DFASLIB_TYPE_LIST_CHECK for human readable error
         // + static_check< some_type<D, type_at< int_<5>, abc_list >::type >::value >::value
         // + static_check< some_type<D, type_at< int_<-1>, abc_list >::type >::value >::value
    
    
  };
  return 0;
}


