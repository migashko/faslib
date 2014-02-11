//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/type_list.hpp>
#include <fas/static_check.hpp>
#include <fas/integral/int_.hpp>

using namespace ::fas;

struct list_1 : type_list<char, type_list<long> > {};
struct list_2 : type_list<float, type_list<int> > {};


typedef push_back<list_1, list_2>::type result_list;
typedef type_list<float, type_list<int, list_1 > > check_list1;

int main()
{
  enum 
  {
    test = static_check< length< result_list>::value == 4 >::value
         + static_check< same_type< type_at< int_<0>, result_list>::type, float>::value >::value
         + static_check< same_type< type_at< int_<1>, result_list>::type, int>::value >::value
         + static_check< same_type< type_at< int_<2>, result_list>::type, char>::value >::value
         + static_check< same_type< type_at< int_<3>, result_list>::type, long>::value >::value
         + static_check< same_type< check_list1, result_list>::value >::value
  };
  
  return 0;
}

