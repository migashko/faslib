//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/type_list/type_list_n.hpp>
#include <fas/algorithm/random_shuffle.hpp>
#include <fas/static_check.hpp>

using namespace ::fas;

/***************
  11837123  1
  8949370   2
  9722709   3
  4858052   4
  5065847   5
  12997982  6
  235177    7
  12762824  8
  13664875  9
  11895682  10
  760893    11
 
  235177    7
  760893    11
  4858052   4 
  5065847   5
  8949370   2
  9722709   3
  11837123  1
  11895682  10
  12762824  8
  12997982  6
  13664875  9
 ***************/

typedef type_list_n< int_<1>, int_<2>,  int_<3>, int_<4>, int_<5>, int_<6>, int_<7>, int_<8>,  int_<9>, int_<10>, int_<11> >::type list;
typedef type_list_n< int_<7>, int_<11>, int_<4>, int_<5>, int_<2>, int_<3>, int_<1>, int_<10>, int_<8>, int_<6>,  int_<9>  >::type check;
typedef random_shuffle< int_<0x50000>/*rand<>::type*/, list>::type shuffled;

int main()
{
  enum 
  {
    result = static_check< some_type< check, shuffled >::value  >::value
  };
  return 0;
}
