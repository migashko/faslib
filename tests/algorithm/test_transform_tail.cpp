//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/type_list.hpp>
#include <fas/algorithm/transform_tail_if.hpp>
#include <fas/algorithm/transform_tail.hpp>
#include <fas/algorithm/nothing.hpp>
#include <fas/algorithm/any.hpp>
#include <fas/typemanip.hpp>
#include <fas/static_check.hpp>

#include <fas/integral.hpp>

struct list2: fas::type_list_n<
  fas::int_<4>,
  fas::int_<5>,
  fas::int_<6>
>::type {};

typedef fas::type_list_n<
  fas::int_<1>,
  fas::int_<2>,
  fas::int_<3>,
  list2
>::type list1;

typedef fas::type_list_n<
  fas::int_<2>,
  fas::int_<4>,
  fas::int_<6>,
  fas::int_<8>,
  fas::int_<10>,
  fas::int_<12>
>::type check_list;

typedef fas::type_list_n<
  fas::int_<1>,
  fas::int_<2>,
  fas::int_<3>,
  fas::int_<4>,
  fas::int_<5>,
  fas::int_<6>
>::type check_list2;

typedef fas::type_list_n<
  fas::int_<1>,
  fas::int_<3>,  
  fas::int_<5>, 
  fas::int_<7>, 
  fas::int_<9>, 
  fas::int_<11>
>::type check_list3;

int main()
{
  typedef fas::any< fas::_> any;
  typedef fas::not_< any > nobody;
  typedef fas::nothing< fas::_> nothing;
  typedef fas::equal_to< fas::modulus<fas::_, fas::int_<2> >, fas::int_<0> > even;
  
  typedef fas::a< fas::make_int< fas::inc< fas::p< fas::_> > > > increment;
  typedef fas::transform< fas::_1, increment > increment_list;
  
  typedef fas::transform_tail_if< list1, increment_list, any >::type result_list;
  typedef fas::transform_tail_if< list1, nothing, nobody >::type nothing_list;
  typedef fas::transform_tail_t< list1, fas::nothing >::type nothing_list2;
  typedef fas::transform_tail_if< list1, increment_list, even >::type even_list;
  

  enum
  {
    test = fas::static_check< fas::some_type< result_list, check_list >::value >::value
         + fas::static_check< fas::some_type< list1, nothing_list >::value >::value
         + fas::static_check< fas::some_type< check_list2, nothing_list2 >::value >::value
         + fas::static_check< fas::some_type< even_list, check_list3 >::value >::value
         
  };
  
  return 0;
}


