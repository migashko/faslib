//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/integral/types.hpp>
#include <fas/integral/logical_op.hpp>
#include <fas/static_check.hpp>

using namespace ::fas;

int main()
{
  enum
  {
    test1 = static_check< and_< bool_<true>, bool_<true> >::type::value >::value,
    test2 = static_check< and_< true_, true_ >::value >::value,
    test3 = static_check< and_< true_, false_ >::value == false >::value,
    test4 = static_check< and_< false_, true_  >::value == false >::value,
    test5 = static_check< and_< int_<10>, int_<0>  >::value == false >::value,
    test6 = static_check< and_< int_<10>, int_<5>  >::value == true >::value,

    test7 = static_check< or_< int_<0>, int_<0>  >::type::value == false >::value,
    test8 = static_check< or_< int_<10>, int_<0>  >::value == true >::value,

    test9 = static_check< not_< int_<0> >::type::value == true >::value,
    test10 = static_check< not_< int_<10> >::value == false >::value
  };
  return 0;
}
