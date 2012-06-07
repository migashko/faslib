//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/type_list/type_list_n.hpp>
#include <fas/static_check.hpp>
#include <fas/type_list/unique.hpp>
#include <fas/algorithm/select.hpp>
#include <fas/type_list/type_at.hpp>
#include <fas/integral/less_equal.hpp>
#include <fas/mp/lambda.hpp>

using namespace ::fas;

struct list_1 : type_list_n<int_<1>, int_<2>, int_<3> >::type {};
struct list_2 : type_list_n<int_<4>, int_<5>, int_<6>, list_1>::type {};

typedef type_list_n<  int_<4>, list_1 >::type check_list1;

typedef select< list_2, less_equal< _1, int_<4> > >::type result_list1;
typedef select_t< list_2, lambda< less_equal< _1, int_<4> > >::apply >::type result_list1t;

int main()
{
  enum {
    test = static_check< some_type< result_list1, check_list1>::value >::value
         + static_check< some_type< result_list1t, check_list1>::value >::value
  };
  return 0;
}


