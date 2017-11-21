//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/type_list.hpp>
#include <fas/static_check.hpp>
#include <fas/typemanip.hpp>

using namespace ::fas;

typedef char char12[12];
struct good_list: type_list<char, type_list< int, type_list< long, type_list<char> > > > {};
struct void_list: empty_list {};
struct one_list: type_list<char12> {};

struct A{};
struct B:A{};
struct C{};
struct D:C,B{};

struct abc_list: type_list<A, type_list<B, type_list<C, type_list<D> > > > {};

int main()
{
  enum 
  {
    test =  static_check< type_count<char, good_list>::value == 2 >::value
        + static_check< type_count<int, good_list>::value == 1 >::value
        + static_check< type_count<long, good_list>::value == 1 >::value
        + static_check< type_count<short, good_list>::value == 0 >::value
        + static_check< type_count<empty_list, good_list>::value == 0 >::value
        + static_check< type_count<empty_list, void_list>::value == 0 >::value
        + static_check< type_count<empty_list, one_list>::value == 0 >::value
        + static_check< type_count<char12, one_list>::value == 1 >::value
        + static_check< type_count<A, abc_list>::value == 1 >::value
        + static_check< type_count<B, abc_list>::value == 1 >::value
        + static_check< type_count<C, abc_list>::value == 1 >::value
        + static_check< type_count<D, abc_list>::value == 1 >::value
  };
	
  return 0;
}


