//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/type_list.hpp>
#include <fas/static_check.hpp>
#include <string>

using namespace ::fas;

typedef char  char12[12];
struct good_list: type_list<char, type_list< int, type_list< long > > > {};
struct void_list: empty_list {};
// cppcheck-suppress syntaxError
struct one_list: type_list<char12> {};

int main()
{
  typedef reverse<good_list>::type rgood_list;
  typedef reverse<empty_list>::type rempty_list;
  typedef reverse<one_list>::type rone_list;
  enum {
    test = static_check< length<rgood_list>::value == 3 >::value
         + static_check< length<rempty_list>::value == 0 >::value
         + static_check< length<rone_list>::value == 1 >::value
         + static_check< index_of<char, rgood_list>::value == 2 >::value
         + static_check< index_of<int, rgood_list>::value == 1 >::value
         + static_check< index_of<long, rgood_list>::value == 0 >::value
  };
  return 0;
}


