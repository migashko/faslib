//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/type_list.hpp>
#include <fas/static_check.hpp>
#include <fas/typemanip/same_type.hpp>

#include <string>

using namespace ::fas;

struct list_1 : type_list<char, type_list<long> > {};
struct list_2 : type_list<float, type_list<int> > {};

typedef type_list<char, type_list<long, list_2 > > check_1;
typedef type_list<float, type_list<int, list_1 > > check_2;

int main()
{
  enum {
    test = static_check< same_type<merge<list_1, list_2>::type, check_1>::value >::value
         + static_check< same_type<merge<list_2, list_1>::type, check_2>::value >::value
         + static_check< same_type<merge<empty_list, list_1>::type, list_1>::value >::value
         + static_check< same_type<merge<list_1, empty_list>::type, list_1>::value >::value
         + static_check< same_type<merge<empty_list, empty_list>::type, empty_list>::value >::value
         + static_check< same_type<merge<empty_list, int>::type, type_list<int> >::value >::value
         + static_check< same_type<merge<int, type_list<long> >::type, type_list<int, type_list<long> > >::value >::value
         //+ static_check< same_type<merge<int, int>::type, type_list<int, type_list<int> > >::value >::value
  };
  return 0;
}


