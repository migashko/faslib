//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/integral/types.hpp>
#include <fas/integral/comparisons.hpp>
#include <fas/static_check.hpp>

using namespace ::fas;

int main()
{
  enum
  {
    test1_1 = static_check< equal_to< int_<1>, int_<1> >::type::value >::value,
    test1_2 = static_check< equal_to< int_<-1>, int_<-1> >::type::value >::value,
    test1_3 = static_check< equal_to< int_<0>, int_<0> >::type::value >::value,
    test1_4 = static_check< equal_to< int_<0>, int_<-1> >::type::value == 0 >::value,
    test1_5 = static_check< equal_to< int_<-1>, int_<1> >::type::value == 0 >::value,

    test2_1 = static_check< not_equal_to< int_<1>, int_<1> >::type::value == 0>::value,
    test2_2 = static_check< not_equal_to< int_<-1>, int_<-1> >::type::value == 0 >::value,
    test2_3 = static_check< not_equal_to< int_<0>, int_<0> >::type::value == 0 >::value,
    test2_4 = static_check< not_equal_to< int_<0>, int_<-1> >::type::value >::value,
    test2_5 = static_check< not_equal_to< int_<-1>, int_<1> >::type::value >::value,

    test3_1 = static_check< less< int_<1>, int_<2> >::type::value >::value,
    test3_2 = static_check< less< int_<-2>, int_<-1> >::type::value >::value,
    test3_3 = static_check< less< int_<0>, int_<0> >::type::value == 0 >::value,
    test3_4 = static_check< less< int_<0>, int_<-1> >::type::value == 0 >::value,
    test3_5 = static_check< less< int_<-1>, int_<-1> >::type::value == 0 >::value,

    test4_1 = static_check< less_equal< int_<1>, int_<2> >::type::value >::value,
    test4_2 = static_check< less_equal< int_<-2>, int_<-1> >::type::value >::value,
    test4_3 = static_check< less_equal< int_<0>, int_<0> >::type::value >::value,
    test4_4 = static_check< less_equal< int_<0>, int_<-1> >::type::value == 0 >::value,
    test4_5 = static_check< less_equal< int_<-1>, int_<-1> >::type::value >::value,

    test5_1 = static_check< greater< int_<2>, int_<1> >::type::value >::value,
    test5_2 = static_check< greater< int_<-1>, int_<-2> >::type::value >::value,
    test5_3 = static_check< greater< int_<0>, int_<0> >::type::value == 0 >::value,
    test5_4 = static_check< greater< int_<-1>, int_<0> >::type::value == 0 >::value,
    test5_5 = static_check< greater< int_<-1>, int_<-1> >::type::value == 0 >::value,

    test6_1 = static_check< greater_equal< int_<2>, int_<1> >::type::value >::value,
    test6_2 = static_check< greater_equal< int_<-1>, int_<-2> >::type::value >::value,
    test6_3 = static_check< greater_equal< int_<0>, int_<0> >::type::value >::value,
    test6_4 = static_check< greater_equal< int_<-1>, int_<0> >::type::value == 0 >::value,
    test6_5 = static_check< greater_equal< int_<-1>, int_<-1> >::type::value >::value
  };
  return 0;
}


