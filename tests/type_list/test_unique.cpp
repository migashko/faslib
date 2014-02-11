//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//


#include <fas/type_list.hpp>
#include <fas/static_check.hpp>
#include <fas/integral/int_.hpp>

using namespace ::fas;

struct list_1 : type_list_n<char, int, long>::type {};
struct list_2 : type_list_n<char, int, double, list_1>::type {};
struct list_3 : type_list_n<list_1, char, int, double>::type {};
struct list_4 : type_list_n<char, int, int>::type {};

typedef type_list_n<double, list_1 >::type check_list1;
typedef type_list_n<long, char, int, double>::type check_list2;
typedef type_list_n<char, int>::type check_list3;

typedef unique<list_2>::type result_list1;
typedef unique<list_3>::type result_list2;
typedef unique<list_4>::type result_list3;


int main()
{
  enum {
    test = static_check< same_type< type_at< int_<0>, result_list1>::type, double>::value >::value
         + static_check< same_type< type_at< int_<0>, result_list3>::type, char>::value >::value
         + static_check< same_type< type_at< int_<1>, result_list3>::type, int>::value >::value
         + static_check< same_type< result_list1, check_list1>::value >::value
         + static_check< same_type< result_list2, check_list2>::value >::value
         + static_check< same_type< result_list3, check_list3>::value >::value
  };
  return 0;
}


