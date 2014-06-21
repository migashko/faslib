//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/type_list.hpp>
#include <fas/algorithm/nothing.hpp>
#include <fas/algorithm/transform.hpp>
#include <fas/algorithm/transform_if.hpp>
#include <fas/typemanip.hpp>
#include <fas/integral.hpp>
#include <fas/mp.hpp>
#include <fas/static_check.hpp>

using namespace ::fas;

typedef type_list_n<
  char, 
  int,
  long,
  double
>::type lst1;

typedef type_list_n<
  type2type<char>,
  type2type<int>,
  type2type<long>,
  type2type<double>
>::type chk1;

typedef type_list_n<
  fas::int_<1>, 
  fas::int_<2>,
  fas::int_<3>,
  fas::int_<4>
>::type lst2;

typedef type_list_n<
  fas::int_<2>, 
  fas::int_<4>,
  fas::int_<6>,
  fas::int_<8>
>::type chk2;

typedef type_list_n<
  fas::integral_c<int, 2>, 
  fas::integral_c<int, 3>,
  fas::integral_c<int, 4>,
  fas::integral_c<int, 5>
>::type chk3;

int main()
{
  typedef transform<lst1, type2type<_1> >::type res1;
  typedef transform<lst2, make_int< times<_1, int_<2> > > >::type res2;
  typedef transform_t<lst2, inc >::type res3;
  typedef transform<lst2, inc<_> >::type res4;

  enum { 
    result = static_check< same_type<res1, chk1>::value>::value
           + static_check< same_type<res2, chk2>::value>::value
           + static_check< same_type<res3, chk3>::value>::value
           + static_check< same_type<res4, chk3>::value>::value
  };
  
  
  
  return 0;
}


