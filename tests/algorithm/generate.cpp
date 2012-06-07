#include <fas/type_list/length.hpp>
#include <fas/type_list/organize.hpp>
#include <fas/algorithm/generate.hpp>
#include <fas/algorithm/generator.hpp>
#include <fas/integral/rand.hpp>
#include <fas/integral/int_.hpp>
#include <fas/integral/make_int.hpp>
#include <fas/static_check.hpp>

template<typename>
struct w1{};

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
    test_length = static_check< length< organize<list>::type >::value == 10>::value,
    // 11837123 8949370 9722709 4858052 5065847 12997982 235177 12762824 13664875 11895682 760893
    
    test0 = static_check< 8949370 == type_at_c<0, list>::type::value >::value,
    test1 = static_check< 9722709 == type_at_c<1, list>::type::value >::value,
    test2 = static_check< 4858052 == type_at_c<2, list>::type::value >::value,
    test3 = static_check< 5065847 == type_at_c<3, list>::type::value >::value,
    test4 = static_check< 12997982 == type_at_c<4, list>::type::value >::value,
    test5 = static_check< 235177 == type_at_c<5, list>::type::value >::value,
    test6 = static_check< 12762824 == type_at_c<6, list>::type::value >::value,
    test7 = static_check< 13664875 == type_at_c<7, list>::type::value >::value,
    test8 = static_check< 11895682 == type_at_c<8, list>::type::value >::value,
    test9 = static_check< 760893 == type_at_c<9, list>::type::value >::value,
  };

  typedef generate< 
    int_<10>,
    generator<
      rand<>::type,
      make_int< rand<_1> >
    > 
  >::type list1;

   enum {
    test1_length = static_check< length< organize<list>::type >::value == 10>::value,
    test10 = static_check< some_type< int_<8949370>,  type_at_c<0, list1>::type >::value >::value,
    test11 = static_check< some_type< int_<9722709>,  type_at_c<1, list1>::type >::value >::value,
    test12 = static_check< some_type< int_<4858052>,  type_at_c<2, list1>::type >::value >::value,
    test13 = static_check< some_type< int_<5065847>,  type_at_c<3, list1>::type >::value >::value,
    test14 = static_check< some_type< int_<12997982>, type_at_c<4, list1>::type >::value >::value,
    test15 = static_check< some_type< int_<235177>,   type_at_c<5, list1>::type >::value >::value,
    test16 = static_check< some_type< int_<12762824>, type_at_c<6, list1>::type >::value >::value,
    test17 = static_check< some_type< int_<13664875>, type_at_c<7, list1>::type >::value >::value,
    test18 = static_check< some_type< int_<11895682>, type_at_c<8, list1>::type >::value >::value,
    test19 = static_check< some_type< int_<760893>,   type_at_c<9, list1>::type >::value >::value,
  };


  
  return 0;
}
/*
namespace app = ::fas::pattern::probe;


typedef app::bind< 
    app::reval<int, int2type>::apply< app::rand< app::_1 > >
> genmaker2;

int main()
{

  typedef int2type<rand<>::value> initial;
  typedef turn<
        value2value ,
        turn<
          repredicate< rand >::apply,
          repredicate< int2type >::apply
        >::apply
      > genmaker;

  
  typedef generator<initial, genmaker::apply> randgenerator;

  typedef generate< 10, randgenerator >::type list;

  // 8949370 9722709 4858052 5065847 12997982 235177 12762824 13664875 11895682 760893
  enum {
    test_length = static_check< length< organize<list>::type >::value == 10>::value,
    test0 = static_check< some_type< int2type<8949370>,  type_at<0, list>::type >::value >::value,
    test1 = static_check< some_type< int2type<9722709>,  type_at<1, list>::type >::value >::value,
    test2 = static_check< some_type< int2type<4858052>,  type_at<2, list>::type >::value >::value,
    test3 = static_check< some_type< int2type<5065847>,  type_at<3, list>::type >::value >::value,
    test4 = static_check< some_type< int2type<12997982>, type_at<4, list>::type >::value >::value,
    test5 = static_check< some_type< int2type<235177>,   type_at<5, list>::type >::value >::value,
    test6 = static_check< some_type< int2type<12762824>, type_at<6, list>::type >::value >::value,
    test7 = static_check< some_type< int2type<13664875>, type_at<7, list>::type >::value >::value,
    test8 = static_check< some_type< int2type<11895682>, type_at<8, list>::type >::value >::value,
    test9 = static_check< some_type< int2type<760893>,   type_at<9, list>::type >::value >::value,
  };

  typedef generate< 11, ngenerator<rand<>::initial, rand, int2type > >::type list2;

  enum {
    test_length2 = static_check< length< organize<list2>::type >::value == 11>::value,
    test20 = static_check< some_type< int2type<8949370>,  type_at<0, list2>::type >::value >::value,
    test21 = static_check< some_type< int2type<9722709>,  type_at<1, list2>::type >::value >::value,
    test22 = static_check< some_type< int2type<4858052>,  type_at<2, list2>::type >::value >::value,
    test23 = static_check< some_type< int2type<5065847>,  type_at<3, list2>::type >::value >::value,
    test24 = static_check< some_type< int2type<12997982>, type_at<4, list2>::type >::value >::value,
    test25 = static_check< some_type< int2type<235177>,   type_at<5, list2>::type >::value >::value,
    test26 = static_check< some_type< int2type<12762824>, type_at<6, list2>::type >::value >::value,
    test27 = static_check< some_type< int2type<13664875>, type_at<7, list2>::type >::value >::value,
    test28 = static_check< some_type< int2type<11895682>, type_at<8, list2>::type >::value >::value,
    test29 = static_check< some_type< int2type<760893>,   type_at<9, list2>::type >::value >::value,
  };

  typedef turn_value<
    turn_value<
      value2value,
      rand
    >::apply,
    int2type
  > genmaker3;
  typedef generator<initial, genmaker3::apply> randgenerator3;
  typedef generate< 10, randgenerator3 >::type list3;

  enum {
    test_length3 = static_check< length< organize<list3>::type >::value == 10>::value,
    test30 = static_check< some_type< int2type<8949370>,  type_at<0, list3>::type >::value >::value,
    test31 = static_check< some_type< int2type<9722709>,  type_at<1, list3>::type >::value >::value,
    test32 = static_check< some_type< int2type<4858052>,  type_at<2, list3>::type >::value >::value,
    test33 = static_check< some_type< int2type<5065847>,  type_at<3, list3>::type >::value >::value,
    test34 = static_check< some_type< int2type<12997982>, type_at<4, list3>::type >::value >::value,
    test35 = static_check< some_type< int2type<235177>,   type_at<5, list3>::type >::value >::value,
    test36 = static_check< some_type< int2type<12762824>, type_at<6, list3>::type >::value >::value,
    test37 = static_check< some_type< int2type<13664875>, type_at<7, list3>::type >::value >::value,
    test38 = static_check< some_type< int2type<11895682>, type_at<8, list3>::type >::value >::value,
    test39 = static_check< some_type< int2type<760893>,   type_at<9, list3>::type >::value >::value,
  };

  
  return 0;
}


*/
