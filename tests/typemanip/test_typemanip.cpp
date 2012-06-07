//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//


#include <fas/typemanip.hpp>
#include <fas/integral.hpp>
#include <fas/static_check.hpp>

using namespace ::fas;

struct A: int2type<10> {};
struct B: bool2type<false> {};
struct C: type2type<volatile const char *> {};

typedef pair<long, char> long_char;

int main()
{
  typedef char array_type[10];
  enum {
    test = static_check< some_type<A::value_type, int>::value >::value
           + static_check< A::value == 10 >::value
           + static_check< some_type<B::value_type, bool>::value >::value
           + static_check< B::value == false >::value
           + static_check< some_type<C::original_type, volatile const char *>::value >::value
           + static_check< !some_type<C, const char *>::value >::value
           + static_check< some_type< first<long_char>::type, long>::value >::value
           + static_check< some_type< second<long_char>::type, char>::value >::value
           + static_check< some_type< if_c<1, long, char>::type, long>::value >::value
           + static_check< some_type< if_c<0, long, char>::type, char>::value >::value
           + static_check< some_type< if_c< 1, long, char>::type, long>::value >::value
           + static_check< some_type< if_c< 0, long, char>::type, char>::value >::value
           + static_check< some_type< max_sizeof< int_<1>::value_type, char_<'x'>::value_type >::type, int >::value >::value
           + static_check< some_type<  remove_cvrp<const int>::type, int >::value >::value
           + static_check< some_type<  remove_cvrp<volatile int const * const&>::type, int >::value >::value
           + static_check< is_const<const int>::value >::value
           + static_check< !is_const<int>::value >::value
           + static_check< is_pointer<const char*>::value >::value
           + static_check< !is_pointer<array_type>::value >::value
           + static_check< !is_array<const char*>::value >::value
           + static_check< is_array<array_type>::value >::value
  };
  return 0;
}



