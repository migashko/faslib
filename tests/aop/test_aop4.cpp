//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/alias.hpp>
#include <fas/aop/private/has_tag.hpp>
#include <fas/aop/private/aspect_select.hpp>
#include <fas/aop/aspect_class.hpp>
#include <fas/aop/advice_cast.hpp>
#include <fas/type_list/type_list_n.hpp>
#include <fas/type_list/length.hpp>
#include <fas/integral.hpp>
#include <fas/static_check/static_check.hpp>
#include <fas/algorithm/find_if.hpp>
#include <fas/algorithm/select.hpp>
#include <fas/typemanip/type2type.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace fas;

struct _counters_;

struct ad_counters
{
  int c0;
  int c1;
  int c2;
  int c3;
  int c4;
  int c5;

  std::vector<int> ids;

  ad_counters() : c0(0), c1(0), c2(0)
                , c3(0), c4(0), c5(0)
  {
  }
};

struct _test1_;
struct _test2_;
struct _test3_;
struct _test4_;
struct _test5_;

struct _group0_;
struct _group1_;
struct _group3_;
struct _group5_;
struct _group6_;

struct _overlapped_;
struct _overlapped2_;

struct ad_overlapped
{
  enum { value = 1};
};

template<int ID>
struct ad_test
{
  enum { id = ID };
  template<typename T>
  void operator()(T& t) const
  {
    t.get_aspect().template get< _counters_ >().c0++ ;
    t.get_aspect().template get< _counters_ >().ids.push_back(ID) ;
  }

  template<typename T>
  void operator()(T& t, int ) const
  {
    t.get_aspect().template get< _counters_ >().c1++ ;
    t.get_aspect().template get< _counters_ >().ids.push_back(ID) ;
  }

  template<typename T>
  void operator()(T& t, int, int ) const
  {
    t.get_aspect().template get< _counters_ >().c2++;
    t.get_aspect().template get< _counters_ >().ids.push_back(ID) ;
  }

  template<typename T>
  void operator()(T& t, int, int, int ) const
  {
    t.get_aspect().template get< _counters_ >().c3++;
    t.get_aspect().template get< _counters_ >().ids.push_back(ID) ;
  }

  template<typename T>
  void operator()(T& t, int, int, int, int ) const
  {
    t.get_aspect().template get< _counters_ >().c4++ ;
    t.get_aspect().template get< _counters_ >().ids.push_back(ID) ;
  }

  template<typename T>
  void operator()(T& t, int, int, int, int, int ) const
  {
    t.get_aspect().template get< _counters_ >().c5++ ;
    t.get_aspect().template get< _counters_ >().ids.push_back(ID);
  }
};

typedef type_list_n<
  advice< _overlapped_, ad_overlapped>,
  advice< _counters_, ad_counters>,
  advice< _test1_, ad_test<1> >,
  advice< _test2_, ad_test<2> >,
  advice< _test3_, ad_test<3> >,
  advice< _test4_, ad_test<4> >,
  advice< _test5_, ad_test<5> >,

  group< _group1_, _test1_ >,

  group< _group3_, type_list_n<_test2_, _test3_>::type >,
  group< _group3_, _test1_ >,

  group< _group5_, _test5_ >,
  group< _group5_, type_list_n<_test2_, _test3_>::type >,
  group< _group5_, type_list_n<_test4_, _test5_>::type >,
  group< _group5_, _test2_ >,
  group< _overlapped_, _test2_ >,

  group< _overlapped2_, _test2_ >,
  advice< _overlapped2_, ad_overlapped>,
  group< _overlapped2_, _test3_ >,
  advice< _group6_, ad_test<6> >

>::type test_advice_list;

struct test_aspect: aspect<test_advice_list> {};

struct test_class: aspect_class<test_aspect>
{
  const ::ad_counters& get_counters() const { return this->get_aspect().get< _counters_ >();}
  ::ad_counters& get_counters() { return this->get_aspect().get< _counters_ >();}
};

bool test_c( const std::string& text, ad_counters c, int c0, int c1, int c2, int c3, int c4, int c5);
std::vector<int> ids( int c0 = -1, int c1= -1, int c2= -1, int c3= -1, int c4= -1, int c5= -1);
bool test_ids( const std::string& text, const std::vector<int>& ids1, const std::vector<int>& ids2);

bool test_c( const std::string& text, ad_counters c, int c0, int c1, int c2, int c3, int c4, int c5)
{
  if ( c.c0!=c0) { std::cout << text << ". invalid counter c0 "<< c.c0 << "!=" << c0 << std::endl;  return false;}
  if ( c.c1!=c1) { std::cout << text << ". invalid counter c1 "<< c.c1 << "!=" << c1 << std::endl;  return false;}
  if ( c.c2!=c2) { std::cout << text << ". invalid counter c2 "<< c.c2 << "!=" << c2 << std::endl;  return false;}
  if ( c.c3!=c3) { std::cout << text << ". invalid counter c3 "<< c.c3 << "!=" << c3 << std::endl;  return false;}
  if ( c.c4!=c4) { std::cout << text << ". invalid counter c4 "<< c.c4 << "!=" << c4 << std::endl;  return false;}
  if ( c.c5!=c5) { std::cout << text << ". invalid counter c5 "<< c.c5 << "!=" << c5 << std::endl;  return false;}
  return true;
}

std::vector<int> ids( int c0, int c1, int c2, int c3, int c4, int c5)
{
  std::vector<int> ids_test;
  if (c0!=-1) ids_test.push_back(c0);
  if (c1!=-1) ids_test.push_back(c1);
  if (c2!=-1) ids_test.push_back(c2);
  if (c3!=-1) ids_test.push_back(c3);
  if (c4!=-1) ids_test.push_back(c4);
  if (c5!=-1) ids_test.push_back(c5);
  return ids_test;
}


bool test_ids( const std::string& text, const std::vector<int>& ids1, const std::vector<int>& ids2)
{
  if ( ids1 == ids2)
    return true;
  std::cout << text << " fail" << std::endl;
  return false;
}

struct f_test
{
  std::vector<int> ids;

  template<typename T, typename Tg>
  void operator()(T&, ::fas::tag<Tg> )
  {
    typedef typename T::aspect::template advice_cast<Tg>::type advice_type;
    ids.push_back(advice_type::id);
  }

};

template<typename T>
struct ad_id
{
  typedef int_<T::id> type;
};


template<typename T>
struct t
{
  typedef typename equal_to< int_<0>, modulus< typename ad_id<T>::type , int_<2> > >::type type;
};



int main()
{
  enum { value = test_class::aspect::advice_cast<_overlapped_>::type::value };
  enum { value2 =
        static_check<
          same_type<
            test_class::aspect::advice_cast<_overlapped2_>::type,
            group_object<_overlapped2_>
          >::value
        >::value
  };
  ad_counters c;
  test_class test;

  test.get_aspect().getg<_group0_>()(test);
  c = test.get_counters();
  if ( !test_c( "test0", c, 0, 0, 0, 0, 0, 0 ) )
    return -1;

  test.get_aspect().getg<_group1_>()(test);
  test.get_aspect().getg<_group1_>()(test, 0);
  test.get_aspect().getg<_group1_>()(test, 0, 0);
  test.get_aspect().getg<_group1_>()(test, 0, 0, 0);
  test.get_aspect().getg<_group1_>()(test, 0, 0, 0, 0);
  test.get_aspect().getg<_group1_>()(test, 0, 0, 0, 0, 0);
  c = test.get_counters();
  if ( !test_c( "test1", c, 1, 1, 1, 1, 1, 1 ) )
    return -1;
  
  if ( !test_ids( "test1ids", c.ids, ids(1, 1, 1, 1, 1, 1) ))
    return -1;

  test = test_class();
  test.get_aspect().getg<_group3_>()(test, 0, 0, 0);
  c = test.get_counters();
  if ( !test_c( "test2", c, 0, 0, 0, 3, 0, 0 ) )
    return -1;
  if ( !test_ids( "test2ids", c.ids, ids(2, 3, 1) ))
    return -1;

  test = test_class();
  test.get_aspect().getg<_group5_>()(test, 0);
  c = test.get_counters();
  if ( !test_c( "test3", c, 0, 4, 0, 0, 0, 0 ) )
    return -1;
  if ( !test_ids( "test3ids", c.ids, ids(5, 2, 3, 4) ))
    return -1;

  f_test f = test.get_aspect().getg<_group5_>().for_each(test, f_test());
  if ( !test_ids( "test3foreach", f.ids, ids(5, 2, 3, 4) ))
    return -1;

  f = test.get_aspect().getg<_overlapped2_>().for_each(test, f_test());
  if ( !test_ids( "_overlapped2_ test3foreach", f.ids, ids(2, 3) ))
    return -1;

  typedef select_group<_group5_, test_class>::type group5_tags;
  typedef fas::select< group5_tags, t< fas::advice_cast<_1, test_class> > >::type group5_tags_selected;
  f_test f2 = test.get_aspect().getg<group5_tags_selected>().for_each(test, f_test());
  if ( !test_ids( "test3foreach", f2.ids, ids(2, 4) ))
    return -1;

  test = test_class();
  test.get_aspect().getg<_group6_>()(test);
  c = test.get_counters();
  if ( !test_c( "_group6_(advice)", c, 1, 0, 0, 0, 0, 0 ) )
    return -1;



  return 0;
}
