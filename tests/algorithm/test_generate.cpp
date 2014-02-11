//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/type_list.hpp>
#include <fas/algorithm/generate.hpp>
#include <fas/algorithm/generator.hpp>
#include <fas/integral.hpp>
#include <fas/static_check.hpp>

int main()
{
  using namespace ::fas;
  
  typedef generate< 
    int_<10>,
    generator<
      rand<>::type,
      rand<_1>
    > 
  >::type list;
 
  //static_check< type_at_c<0, list>::type::value >::value x,
  enum {
    test = static_check< length< organize<list>::type >::value == 10>::value
    // 11837123 8949370 9722709 4858052 5065847 12997982 235177 12762824 13664875 11895682 760893
         + static_check< 11837123 == type_at_c<0, list>::type::value >::value
         + static_check< 8949370 == type_at_c<1, list>::type::value >::value
         + static_check< 9722709 == type_at_c<2, list>::type::value >::value
         + static_check< 4858052 == type_at_c<3, list>::type::value >::value
         + static_check< 5065847 == type_at_c<4, list>::type::value >::value
         + static_check< 12997982 == type_at_c<5, list>::type::value >::value
         + static_check< 235177 == type_at_c<6, list>::type::value >::value
         + static_check< 12762824 == type_at_c<7, list>::type::value >::value
         + static_check< 13664875 == type_at_c<8, list>::type::value >::value
         + static_check< 11895682 == type_at_c<9, list>::type::value >::value
         //+ static_check< 760893 == type_at_c<9, list>::type::value >::value
  };

  typedef generate< 
    int_<10>,
    generator<
      rand<>::type,
      make_int< rand<_1> >
    > 
  >::type list1;

   enum {
    test2 = static_check< length< organize<list>::type >::value == 10>::value
         //+ static_check< same_type< int_<11837123>,  type_at_c<0, list1>::type >::value >::value
         + static_check< same_type< int_<8949370>,  type_at_c<1, list1>::type >::value >::value
         + static_check< same_type< int_<9722709>,  type_at_c<2, list1>::type >::value >::value
         + static_check< same_type< int_<4858052>,  type_at_c<3, list1>::type >::value >::value
         + static_check< same_type< int_<5065847>,  type_at_c<4, list1>::type >::value >::value
         + static_check< same_type< int_<12997982>, type_at_c<5, list1>::type >::value >::value
         + static_check< same_type< int_<235177>,   type_at_c<6, list1>::type >::value >::value
         + static_check< same_type< int_<12762824>, type_at_c<7, list1>::type >::value >::value
         + static_check< same_type< int_<13664875>, type_at_c<8, list1>::type >::value >::value
         + static_check< same_type< int_<11895682>, type_at_c<9, list1>::type >::value >::value
         // + static_check< same_type< int_<760893>,   type_at_c<10, list1>::type >::value >::value
  };

  return 0;
}
