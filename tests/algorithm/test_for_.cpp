//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/algorithm/for_.hpp>
#include <fas/type_list.hpp>
#include <fas/mp.hpp>
#include <fas/integral.hpp>
#include <fas/static_check.hpp>
#include <fas/typemanip.hpp>

using namespace ::fas;

void test1()
{
  using namespace ::fas;

  typedef for_<
    int_<1>,
    less_equal<_1, int_<10> >,
    inc< _1 >
  >::type test;

  typedef for_t<
    int_<1>,
    lambda< less_equal<_1, int_<10> > >::apply,
    inc
  >::type test1;

  enum { result = static_check<test::value == 11>::value
                + static_check<test1::value == 11>::value
  };

  
  typedef pair<
    for_<
      int_<1>,
      a< less< p<_1>, int_<10> > >,
      a< plus< p<_1>, _1 > >
    >,
    _2
  > pair_test;

  typedef apply<pair_test, int_<2>, int_<15> >::type test2;

  enum { result2 = static_check< test2::second::value == 15 >::value
                 + static_check< test2::first::value == 11 >::value
  };

  typedef apply<
      for_< 
        int_<1>,
        a< less< p<_1>, int_<10> > >,
        a< inc< p<_1> > >
      >
    >::type test3;
  enum { result4 = static_check<test3::value == 10>::value };
}


void test2()
{
  
  using namespace ::fas;
  
  typedef for_<
    int_<1>, 
    less_equal< _1, int_<10> >,
    plus< _1, int_<2> >
  >::type test;
  enum { result = static_check<test::value == 11>::value };
}


void test3()
{
  using namespace ::fas;

  typedef type_list< int_<2> > initial;
  typedef push_back<
    make_int<
      inc<
        type_at< 
          dec< f< length<_1> > > ,
        _1 >
      >
    >
    ,
  _1
  >  doit;
  
  typedef less< f< length< _1 > > , int_<9> > cond;
  typedef for_< initial, cond, doit > wh;
  typedef wh::type result;
  typedef type_list_n< int_<2>, int_<3>, int_<4>, 
                       int_<5>, int_<6>, int_<7>,
                       int_<8>, int_<9>, int_<10>
  >::type check_list;
  
  enum 
  {
    test = static_check< lambda< cond >::apply< type_list<int> >::type::value == 1>::value
         + static_check< length< lambda< doit >::apply< type_list< int_<2> > >::type >::value == 2 >::value
         + static_check< length<result>::value - length<check_list>::value == 0 >::value
         + static_check< some_type< type_at_c<0, result>::type, int_<2> >::value  >::value 
  };
  
}

void test4()
{
  using namespace ::fas;

  typedef type_list< make_int< rand<>::type > > initial;
  typedef less< f< length<_1> >, int_<10> > cond;
  typedef push_back< make_int< rand< type_at< dec< f< length<_1> > >, _1 > > > , _1 > doit;

  
  typedef for_< initial, cond, doit>::type result;
  
  // 11837123 8949370 9722709 4858052 5065847 12997982 235177 12762824 13664875 11895682 760893
  enum {
    test = static_check< length< result >::value == 10>::value
         + static_check< some_type< int_<11837123>, type_at_c<0, result>::type >::value >::value
         + static_check< some_type< int_<8949370>,  type_at_c<1, result>::type >::value >::value
         + static_check< some_type< int_<9722709>,  type_at_c<2, result>::type >::value >::value
         + static_check< some_type< int_<4858052>,  type_at_c<3, result>::type >::value >::value
         + static_check< some_type< int_<5065847>,  type_at_c<4, result>::type >::value >::value
         + static_check< some_type< int_<12997982>, type_at_c<5, result>::type >::value >::value
         + static_check< some_type< int_<235177>,   type_at_c<6, result>::type >::value >::value
         + static_check< some_type< int_<12762824>, type_at_c<7, result>::type >::value >::value
         + static_check< some_type< int_<13664875>, type_at_c<8, result>::type >::value >::value
         + static_check< some_type< int_<11895682>, type_at_c<9, result>::type >::value >::value
  };
  
}

template<typename I>
struct my_do_while
{
  typedef less_equal< f< length< _1 > >, int_<10> > cond;
  typedef push_back< make_int< rand< type_at< dec< f< length<_1> > >, _1 > > > , _1 > doit;
  typedef for_< I, cond, doit> test1;
  typedef typename test1::type monw_type;
  //typedef typename wrap<monw_type>::type type;
  typedef monw_type type;
};

void test5()
{

  
  typedef pair<
    int_<0>,
    empty_list
  > initial;

  typedef pair<
    inc< first<_1> >,
    unique<
      push_back<
        my_do_while<
          a< type_list< make_int< rand< first<_1> > > > >
        >,
        second<_1>
      >
    >
  > doit;

  typedef less_equal<
    f< length< second<_1> > >,
    int_<10>
  > cond;

  typedef for_< initial, cond, doit > dw;
  typedef dw::type test;
}

void test6()
{
  using namespace ::fas;

  typedef for_<
    type_list< make_int< rand< first<_1> > > > ,
    a< less_equal< f< length< p<_1> > >, int_<3> > >,
    a< push_back< make_int< rand< type_at< dec< f< length< p<_1> > > >, p<_1> > > > , p<_1> > >
  > randsequence_generator;

  //typedef apply< randsequence_generator, pair< int_<0>, empty_list > >::type test1; 

  typedef pair<
      inc< first<_1> >,
      unique<
        push_back<
          randsequence_generator,
          second<_1>
        >
      >
    > doit;

  typedef apply<doit, pair< int_<0>, empty_list> >::type test2;
  
  typedef pair<int_<0>, empty_list> initial;
  typedef less_equal< f< length< second< _1> > >, int_<3> > cond;
  typedef for_< initial, cond, doit> dw;
  typedef dw::type test3;
}

int main()
{
  test1();
  test2();
  test3();
  test4();
  return 0;
}

