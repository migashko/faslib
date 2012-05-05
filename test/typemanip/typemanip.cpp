#include <fas/typemanip.hpp>
#include <fas/static_check.hpp>

#include <fas/integral/int2type.hpp>
#include <fas/integral/int_.hpp>
#include <fas/integral/bool_.hpp>
#include <fas/integral/char_.hpp>
#include <fas/integral/bool2type.hpp>
#include <fas/typemanip/type2type.hpp>
#include <fas/typemanip/remove_cvrp.hpp>
#include <fas/typemanip/if_c.hpp>

using namespace ::fas;

struct A: int2type<10> {};
struct B: bool2type<false> {};
struct C: type2type<volatile const char *> {};

typedef pair<long, char> long_char;

int main()
{
  enum {
    test1_int2type = static_check< some_type<A::value_type, int>::value >::value,
    test2_int2type = static_check< A::value == 10 >::value,
    test1_bool2type = static_check< some_type<B::value_type, bool>::value >::value,
    test2_bool2type = static_check< B::value == false >::value,
    test1_type2type = static_check< some_type<C::original_type, volatile const char *>::value >::value,
    test2_type2type = static_check< !some_type<C, const char *>::value >::value,
    test1_pair = static_check< some_type< first<long_char>::type, long>::value >::value,
    test2_pair = static_check< some_type< second<long_char>::type, char>::value >::value,
    test1_if_c = static_check< some_type< if_c<1, long, char>::type, long>::value >::value,
    test2_if_c = static_check< some_type< if_c<0, long, char>::type, char>::value >::value,
    test1_if_ = static_check< some_type< if_c< 1, long, char>::type, long>::value >::value,
    test2_if_ = static_check< some_type< if_c< 0, long, char>::type, char>::value >::value,
//#warning !!
    /// TODO: Не логично! 
    test2_max_sizeof = static_check< some_type< max_sizeof< int_<1>, char_<'x'> >::type, int >::value >::value,
    
    remove_cvrp_ = static_check< some_type<  remove_cvrp<const int>::type, int >::value >::value
                   + static_check< some_type<  remove_cvrp<volatile int const * const&>::type, int >::value >::value,
  };
  return 0;
}



