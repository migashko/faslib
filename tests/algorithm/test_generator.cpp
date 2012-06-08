//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/algorithm/generator.hpp>
#include <fas/static_check.hpp>
#include <fas/integral.hpp>

int main()
{
  using namespace ::fas;
  typedef generator< int_<0>, inc<_1> > gen_inc;
  typedef generator< int_<10>, dec<_1> > gen_dec;
  typedef generator< rand<>::initial, rand<_1> > gen_rand;
  
  enum {
    test = static_check< gen_inc::type::value == 1  >::value
         + static_check< gen_inc::next::type::value == 2  >::value
         + static_check< gen_inc::next::next::type::value == 3  >::value

         + static_check< gen_dec::type::value == 9  >::value
         + static_check< gen_dec::next::type::value == 8  >::value
         + static_check< gen_dec::next::next::type::value == 7  >::value

    // 11837123 8949370 9722709 4858052 5065847 12997982 235177 12762824 13664875 11895682 760893
         + static_check< gen_rand::type::value == 11837123  >::value
         + static_check< gen_rand::next::type::value == 8949370  >::value
         + static_check< gen_rand::next::next::type::value == 9722709  >::value
  };
  
  return 0;
}
