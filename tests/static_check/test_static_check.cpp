//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/static_check.hpp>

using namespace ::fas;

int main()
{
  static_check< true > test1obj;
  static_check< 1 > test2obj;
  test1obj = test2obj;
  // static_check< 0 > test3obj; // error: aggregate 'fas::static_check<0> test3obj' has incomplete type and cannot be defined
  // static_check< false > test4obj; // error: aggregate 'fas::static_check<0> test4obj' has incomplete type and cannot be defined
  // static_check< 2 > test5obj; // error: aggregate 'fas::static_check<2> test5obj' has incomplete type and cannot be defined
  enum {
    test3 = static_check< true >::value,
    test4 = static_check< 1 >::value
    // test5 = static_check< 0 >::value, // error: incomplete type 'fas::static_check<0>' used in nested name specifier
    // test6 = static_check< 2 >::value, // error: incomplete type 'fas::static_check<2>' used in nested name specifier
  };
  return 0;
}
