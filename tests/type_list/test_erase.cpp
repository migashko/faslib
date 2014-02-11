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

typedef type_list<int, list_1> check_0;
typedef type_list<float, type_list<int, type_list<char> > > check_3;


int main()
{
  enum {
    test = static_check< same_type< erase< int_<0>, list_2>::type, check_0>::value >::value
         + static_check< same_type< erase< int_<3>, list_2>::type, check_3>::value >::value
         
         // if -DFASLIB_TYPE_LIST_CHECK
         //   error: invalid use of incomplete type ‘fas::static_error<fas::errorlist::out_of_range<8, 4>, 0>::type {aka struct fas::errorlist::out_of_range<8, 4>}’
         // else
         //   error: no type named ‘left_type’ in ‘struct fas::empty_list’
         // + static_check< some_type< erase< int_<8>, list_2>::type, check_3>::value >::value

         // if -DFASLIB_TYPE_LIST_CHECK
         // error: invalid use of incomplete type ‘fas::static_error<fas::errorlist::out_of_range<-0x00000000000000006, 4>, 0>::type {aka struct fas::errorlist::out_of_range<-0x00000000000000006, 4>}’
         // + static_check< some_type< erase< int_<-6>, list_2>::type, check_3>::value >::value*/
  };
  return 0;
}


