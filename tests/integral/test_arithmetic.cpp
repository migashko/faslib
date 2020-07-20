//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/integral/types.hpp>
#include <fas/integral/arithmetic.hpp>
#include <fas/static_check.hpp>

using namespace ::fas;

int main()
{
  enum
  {
    test_plus_0 = static_check< plus< int_<0>, int_<0> >::value == 0 >::value,
    test_plus_1 = static_check< plus< int_<0>, int_<1> >::value == 1 >::value,
    test_plus_2 = static_check< plus< int_<2>, int_<-1> >::value == 1 >::value,

    test_minus_0 = static_check< minus< int_<0>, int_<0> >::value == 0 >::value,
    test_minus_1 = static_check< minus< int_<0>, int_<1> >::value == -1 >::value,
    test_minus_2 = static_check< minus< int_<2>, int_<-1> >::value == 3 >::value,

    test_times_0 = static_check< times< int_<0>, int_<0> >::value == 0 >::value,
    test_times_1 = static_check< times< int_<0>, int_<1> >::value == 0 >::value,
    test_times_2 = static_check< times< int_<2>, int_<-1> >::value == -2 >::value,
    test_times_3 = static_check< times< int_<3>, int_<3> >::value == 9 >::value,

    // test_divides_0 = static_check< divides< int_<0>, int_<0> >::value == 0 >::value,
    test_divides_1 = static_check< divides< int_<0>, int_<1> >::value == 0 >::value,
    test_divides_2 = static_check< divides< int_<2>, int_<-1> >::value == -2 >::value,
    test_divides_3 = static_check< divides< int_<3>, int_<3> >::value == 1 >::value,
    test_divides_4 = static_check< divides< int_<5>, int_<2> >::value == 2 >::value,

    // test_modulus_0 = static_check< modulus< int_<0>, int_<0> >::value == 0 >::value,
    test_modulus_1 = static_check< modulus< int_<0>, int_<1> >::value == 0 >::value,
    test_modulus_2 = static_check< modulus< int_<2>, int_<-1> >::value == 0 >::value,
    test_modulus_3 = static_check< modulus< int_<3>, int_<3> >::value == 0 >::value,
    test_modulus_4 = static_check< modulus< int_<5>, int_<2> >::value == 1 >::value,

    test_inc_1 = static_check< inc< int_<0> >::value == 1 >::value,
    test_dec_1 = static_check< dec< int_<0> >::value == -1 >::value,
    test_negate_0 = static_check< negate< int_<0> >::value == 0 >::value,
    test_negate_1 = static_check< negate< int_<1> >::value == -1 >::value,
    test_negate_2 = static_check< negate< int_<-2> >::value == 2 >::value,

    // 8949370 9722709 4858052 5065847 12997982 235177 12762824 13664875 11895682 760893
    test_rand_0 = static_check< rand< >::value == 11837123 >::value,
    test_rand_1 = static_check< rand< int_<11837123> >::value == 8949370 >::value,
    test_rand_2 = static_check< rand< int_<8949370> >::value == 9722709 >::value,
    test_rand_3 = static_check< rand< int_<9722709> >::value == 4858052 >::value,

    test_pow_1 = static_check< pow< int_<2>, int_<0> >::value == 1 >::value,
    test_pow_2 = static_check< pow< int_<2>, int_<1> >::value == 2 >::value,
    test_pow_3 = static_check< pow< int_<2>, int_<2> >::value == 4 >::value,

    test_fact_0 = static_check< factorial< int_<0> >::value == 1 >::value,
    test_fact_1 = static_check< factorial< int_<1> >::value == 1 >::value,
    test_fact_2 = static_check< factorial< int_<2> >::value == 2 >::value,
    test_fact_3 = static_check< factorial< int_<3> >::value == 6 >::value
  };
  return 0;
}

