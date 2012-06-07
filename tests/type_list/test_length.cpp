//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/type_list.hpp>
#include <fas/static_check.hpp>

using namespace ::fas;

struct good_list: type_list<char, type_list< int, type_list< long > > > {};
struct void_list: empty_list {};
struct one_list: type_list<char[12]> {};

int main()
{
  enum {
    test = static_check< length<good_list>::value == 3 >::value
         + static_check< length<void_list>::value == 0 >::value
         + static_check< length<one_list>::value == 1 >::value
         // -DFASLIB_TYPE_LIST_CHECK for human readable error
         // + static_check< length<int>::value == 1 >::value
         // + static_check< length< type_list<int, char>  >::value == 2 >::value
    
    
  };
  return 0;
}


