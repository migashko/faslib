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
struct list_2 : type_list<float, type_list<int, list_1> > {};

typedef empty_list check_0_left;
typedef list_2 check_0_right;

typedef type_list<float> check_1_left;
typedef type_list<int, list_1> check_1_right;

typedef type_list<float, type_list<int> > check_2_left;
typedef list_1 check_2_right;


typedef list_2 check_4_left;
typedef empty_list check_4_right;


int main()
{
  
  enum {
    test = static_check< same_type< split< int_<0>, list_2>::left_list, check_0_left>::value >::value
         + static_check< same_type< split< int_<0>, list_2>::right_list, check_0_right>::value >::value
         + static_check< same_type< split< int_<1>, list_2>::left_list, check_1_left>::value >::value
         + static_check< same_type< split< int_<1>, list_2>::right_list, check_1_right>::value >::value
         + static_check< same_type< split< int_<2>, list_2>::left_list, check_2_left>::value >::value
         + static_check< same_type< split< int_<2>, list_2>::right_list, check_2_right>::value >::value
         + static_check< same_type< split< int_<4>, list_2>::left_list, check_4_left>::value >::value
         + static_check< same_type< split< int_<4>, list_2>::right_list, check_4_right>::value >::value
         // -DFASLIB_TYPE_LIST_CHECK for human readable error
         // + static_check< some_type< split< int_<-1>, list_2>::left_list, check_4_left>::value >::value
         // + static_check< some_type< split< int_<60>, list_2>::right_list, check_4_right>::value >::value
  };
  return 0;
}


