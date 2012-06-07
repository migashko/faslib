//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/type_list.hpp>
#include <fas/static_check.hpp>

#include <string>

using namespace ::fas;

struct good_list: type_list<char, type_list< int, type_list< long > > > {};
struct void_list: empty_list {};
struct one_list: type_list<char[12]> {};
struct bad_list: type_list< type_list< int, type_list< long > >, char > {};

int main()
{
  enum {
    test = static_check< is_organized<good_list>::value >::value
           + static_check< is_organized<void_list>::value >::value
           + static_check< is_organized<one_list>::value >::value
           + static_check< !is_organized<bad_list>::value >::value
  };
  
  return 0;
}


