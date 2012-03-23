#include <fas/generators/generator.hpp>
#include <fas/static_check.hpp>
#include <fas/integral/inc.hpp>
#include <fas/integral/dec.hpp>
#include <fas/integral/rand.hpp>

int main()
{
  using namespace ::fas;
  typedef generator< int_<0>, inc<_1> > gen_inc;
  typedef generator< int_<10>, dec<_1> > gen_dec;
  typedef generator< rand<>::initial, rand<_1> > gen_rand;
  
  enum {
    test_inc0 = static_check< gen_inc::type::value == 1  >::value,
    test_inc1 = static_check< gen_inc::next::type::value == 2  >::value,
    test_inc2 = static_check< gen_inc::next::next::type::value == 3  >::value,

    test_dec0 = static_check< gen_dec::type::value == 9  >::value,
    test_dec1 = static_check< gen_dec::next::type::value == 8  >::value,
    test_dec2 = static_check< gen_dec::next::next::type::value == 7  >::value,

    // 11837123 8949370 9722709 4858052 5065847 12997982 235177 12762824 13664875 11895682 760893
    test_rand0 = static_check< gen_rand::type::value == 11837123  >::value,
    test_rand1 = static_check< gen_rand::next::type::value == 8949370  >::value,
    test_rand2 = static_check< gen_rand::next::next::type::value == 9722709  >::value,

  };
  
  return 0;
}


