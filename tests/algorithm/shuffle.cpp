
#include <fas/type_list/type_list_n.hpp>
#include <fas/type_list/reverse.hpp>
#include <fas/algorithm/random_shuffle.hpp>
#include <fas/static_check.hpp>

using namespace ::fas;

/**
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

 */


typedef type_list_n< char, short, int, long, double >::type list;
typedef type_list_n< int_<5>, int_<4>, int_<3>, int_<2>, int_<1> >::type shuffle_list;

typedef shuffle< list, shuffle_list>::type shuffled;

int main()
{
  enum 
  {
    result = static_check< some_type< reverse<list>::type, shuffled >::value  >::value
  };
  return 0;
}





