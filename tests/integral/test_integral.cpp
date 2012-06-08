//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/integral/types.hpp>
#include <fas/static_check.hpp>

using namespace ::fas;


struct A: int_<10> {};
struct B: bool_<false> {};
struct C: integral_c<char, 'z'> {};
struct D: char_<'z'> {};
struct E: long_<10L> {};


int main()
{
  enum {
    test1 = static_check< A::value == 10 >::value,
    test2 = static_check< B::value == false >::value,
    test3 = static_check< C::value == 'z' >::value,
  };
  return 0;
}
