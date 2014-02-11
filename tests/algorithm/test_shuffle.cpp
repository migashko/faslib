//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/type_list/type_list_n.hpp>
#include <fas/type_list/reverse.hpp>
#include <fas/algorithm/random_shuffle.hpp>
#include <fas/static_check.hpp>

using namespace ::fas;


typedef type_list_n< char, short, int, long, double >::type list;
typedef type_list_n< int_<5>, int_<4>, int_<3>, int_<2>, int_<1> >::type shuffle_list;

typedef shuffle< list, shuffle_list>::type shuffled;

int main()
{
  enum 
  {
    test = static_check< same_type< reverse<list>::type, shuffled >::value  >::value
  };
  return 0;
}
