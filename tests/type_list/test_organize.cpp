//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/type_list.hpp>
#include <fas/static_check.hpp>
#include <fas/integral/int_.hpp>
#include <string>

using namespace ::fas;

struct A{};
struct B:A{};
struct C{};
struct D:C{};

struct list_1 : type_list<char, long> {};
struct list_2 : type_list<float, type_list<int> > {};
struct list_3 : type_list<list_1, list_2> {};
struct list_4 : type_list<D, type_list<C> > {};
struct list_5 : type_list< type_list<list_4, list_3 >, type_list<A, B> > {};

struct list_6_1 : type_list< type_list< empty_list, type_list< empty_list, type_list< A, type_list< empty_list, type_list< empty_list, type_list< empty_list > > > > > > > {};
struct list_6   : type_list< type_list<empty_list, type_list<empty_list> > , type_list<type_list<empty_list>, A > >{};

struct list_7 : type_list<empty_list> {};
struct list_8 : type_list<B, type_list<empty_list, type_list<empty_list> > > {};

typedef type_list<char, type_list<long> > check_1;

typedef type_list<char, type_list<long, list_2 > > check_3;

typedef type_list<D, type_list<C, type_list<char, type_list<long, type_list<float, type_list<int, type_list<A, type_list<B> > > > > > > > check_5;
typedef type_list<A> check_6;
typedef type_list<B> check_8;
typedef empty_list check_7;

typedef type_list<int_<100>,type_list<type_list<int_<2>, type_list<int_<3>,type_list<int_<4>, empty_list> > >,
                      empty_list> > list_9;
typedef type_list_n< int_<100>, int_<2>, int_<3>, int_<4> >::type check_9;


int main()
{
 enum {
    test = static_check< same_type<organize<list_1>::type, check_1>::value >::value
         + static_check< same_type<organize<list_2>::type, list_2>::value >::value
         + static_check< same_type<organize<list_3>::type, check_3>::value >::value
         + static_check< same_type<organize<list_5>::type, check_5>::value >::value
         + static_check< same_type<organize<list_6>::type, check_6>::value >::value
         + static_check< same_type<organize<list_6_1>::type, check_6>::value >::value
         + static_check< same_type<organize<list_7>::type, check_7>::value >::value
         + static_check< same_type<organize<list_8>::type, check_8>::value >::value
         + static_check< same_type<organize<list_9>::type, check_9>::value >::value
  };
  return 0;
}


