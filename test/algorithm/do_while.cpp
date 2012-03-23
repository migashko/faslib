#include <fas/type_list.hpp>
#include <fas/type_list/intrinsic.hpp>
#include <fas/mp/apply.hpp>
#include <fas/mp/lambda.hpp>
#include <fas/algorithm/do_while.hpp>
#include <fas/integral.hpp>
#include <fas/integral/make_int.hpp>
#include <fas/static_check.hpp>
#include <fas/integral/less_equal.hpp>
#include <fas/integral/less.hpp>
#include <fas/integral/rand.hpp>
#include <fas/integral/inc.hpp>
#include <fas/integral/plus.hpp>
#include <fas/typemanip/first.hpp>
#include <fas/typemanip/second.hpp>

using namespace ::fas;


void test1()
{
  using namespace ::fas;

  typedef do_while<
    int_<1>,
    inc< _1 >,
    less_equal<_1, int_<10> >
  >::type test;

  typedef do_while_t<
    int_<1>,
    inc,
    lambda< less_equal<_1, int_<10> > >::apply
  >::type test1;

  enum { result = static_check<test::value == 11>::value,
         result1 = static_check<test1::value == 11>::value
  };

  
  typedef pair<
    do_while<
      int_<1>,
      a< plus< p<_1>, _1 > >,
      a< less/*_equal*/< p<_1>, int_<10> > >
    >,
    _2
  > pair_test;

  typedef apply<pair_test, int_<2>, int_<15> >::type test2;

  enum { result2 = static_check< test2::second::value == 15 >::value
                  + static_check< test2::first::value == 11 >::value};

  typedef apply<
      do_while< 
        int_<1>,
        a< inc< p<_1> > >, 
        a< less/*_equal*/< p<_1>, int_<10> > >
      >
    >::type test3;
  enum { result4 = static_check<test3::value == 10>::value };
  
}


void test2()
{
  // TODO: сделать протект
  using namespace ::fas;
  
  typedef do_while<
    int_<1>, 
    plus< _1, int_<2> > , 
    less_equal< _1, int_<10> > 
  >::type test;
  enum { result = static_check<test::value == 11>::value };
}


void test3()
{
  using namespace ::fas;

  //static_check< 1 == placeholders_extract< type_at<dec<length<fas::pattern::_1> >, fas::pattern::_1> >::value > x;


  typedef type_list< int_<2> > initial;
  typedef push_back<
    make_int<
      inc<
        type_at< 
          dec< length<_1> > ,
        _1 >
      >
    >
    ,
  _1 >  doit;
  typedef less< length< _1 > , int_<9> > cond;
  typedef do_while< initial, doit, cond > wh;
  typedef wh::type test;
  typedef type_list_n< int_<2>, int_<3>, int_<4>, 
                       int_<5>, int_<6>, int_<7>,
                       int_<8>, int_<9>, int_<10>
  >::type check_list;
  
  
  //static_check< length<test>::value - length<check_list>::value  > zz;

  enum 
  {
    /*test_type_list = static_check< 
        bind<
          less< length< _1 >, int_<10> >
        >::apply<
            type_list<int>
        >::type::value == 1
     >::value,*/
    // test0 = static_check< length_< placeholders_extract< doit >::type >::value == 1 >::value,
    //test1 = static_check< bind<cond>::apply< type_list<int> >::type::value == 1>::value,
    //test2 = static_check< length< bind< doit >::apply< type_list< int_<2> > >::type >::value == 2 >::value,
    test_lenght = static_check< length<test>::value - length<check_list>::value == 0 >::value,
    test_list_0 = static_check< some_type< type_at_c<0, test>::type, int_<2> >::value  >::value 
  };
  
}

void test4()
{
  using namespace ::fas;

  typedef type_list< make_int< rand<>::type > > initial;
  typedef less< length<_1>, int_<10> > cond;
  typedef push_back< make_int< rand< type_at< dec< length<_1> >, _1 > > > , _1 > doit;

  
  typedef do_while< initial, doit, cond >::type test;
  
  // 11837123 8949370 9722709 4858052 5065847 12997982 235177 12762824 13664875 11895682 760893
  enum {
    test_length = static_check< length< test >::value == 10>::value,
    test0 = static_check< some_type< int_<11837123>, type_at_c<0, test>::type >::value >::value,
    test1 = static_check< some_type< int_<8949370>,  type_at_c<1, test>::type >::value >::value,
    test2 = static_check< some_type< int_<9722709>,  type_at_c<2, test>::type >::value >::value,
    test3 = static_check< some_type< int_<4858052>,  type_at_c<3, test>::type >::value >::value,
    test4 = static_check< some_type< int_<5065847>,  type_at_c<4, test>::type >::value >::value,
    test5 = static_check< some_type< int_<12997982>, type_at_c<5, test>::type >::value >::value,
    test6 = static_check< some_type< int_<235177>,   type_at_c<6, test>::type >::value >::value,
    test7 = static_check< some_type< int_<12762824>, type_at_c<7, test>::type >::value >::value,
    test8 = static_check< some_type< int_<13664875>, type_at_c<8, test>::type >::value >::value,
    test9 = static_check< some_type< int_<11895682>, type_at_c<9, test>::type >::value >::value,
    // test10 = static_check< some_type< int_<760893>,   type_at_c<9, test>::type >::value >::value,
  };
  
}

template<typename I>
struct my_do_while
{
  typedef less_equal< length< _1 >, int_<10> > cond;
  typedef push_back< make_int< rand< type_at< dec< length<_1> >, _1 > > > , _1 > doit;
  typedef do_while< I, doit, cond > test1;
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
    length< second<_1> >,
    int_<10>
  > cond;

  typedef do_while< initial, doit, cond > dw;
  typedef dw::type test;
}

void test6()
{
  using namespace ::fas;

  typedef do_while<
    type_list< make_int< rand< first<_1> > > > ,
    a< push_back< make_int< rand< type_at< dec< length< p<_1> > >, p<_1> > > > , p<_1> > > ,
    a< less_equal< length< p<_1> >, int_<3> > >
  > randsequence_generator;

  typedef apply< randsequence_generator, pair< int_<0>, empty_list > >::type test1; 

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
  typedef less_equal< length< second< _1> >, int_<3> > cond;
  typedef do_while< initial, doit, cond> dw;
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

