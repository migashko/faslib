#include <fas/type_list.hpp>
#include <fas/algorithm.hpp>
#include <fas/mp.hpp>
#include <fas/integral.hpp>

#include <iostream>

template<int i>
struct foo;

template<int i>
struct bar;


namespace std
{
  template<typename L, typename R>
  ostream& operator << ( ostream& os, fas::type_list<L,R> )  { os << L::value  << ", " << R(); return os;}

  template<int i, typename R>
  ostream& operator << ( ostream& os, fas::type_list< foo<i>, R> )  { os << "foo-" << i << ", " << R(); return os;}

  template<int i, typename R>
  ostream& operator << ( ostream& os, fas::type_list< bar<i>, R> )  { os << "bar-" << i << ", " << R(); return os;}

  
  template<typename L>
  ostream& operator << ( ostream& os, fas::type_list<L, fas::empty_list> )  { os << L::value; return os; }

  template<int i>
  ostream& operator << ( ostream& os, fas::type_list<foo<i>, fas::empty_list> )  { os << "foo-" << i; return os; }

  template<int i>
  ostream& operator << ( ostream& os, fas::type_list<bar<i>, fas::empty_list> )  { os << "bar-" << i; return os; }

  ostream& operator << ( ostream& os, fas::empty_list )  { return os; }
}

template<int i>
struct foo
{
  enum { foo_value = i};
};

template<int i>
struct bar
{
  enum { bar_value = i};
};

template<typename T>
struct make_foo
{
  typedef foo<T::value> type;
};

template<typename T>
struct make_bar
{
  typedef bar<T::value> type;
};

template<typename T>
struct is_int
{
  enum {value=0};
};

template<int i>
struct is_int< fas::int_<i> >
{
  enum {value=1};
};


int main()
{
  using fas::_;
  using fas::_1;
  using fas::a;
  using fas::p;
  using fas::int_;
  
  typedef fas::generate<
    fas::int_<10>, 
    fas::generator< 
      fas::rand<int_<111> >, 
      fas::make_int< fas::rand<_> >
    > 
  >::type randlist;
  
  std::cout << "randlist: " << randlist() << std::endl;
  
  typedef fas::transform<randlist, fas::make_int< fas::modulus<_, int_<3> > > >::type randlist_012;
  
  std::cout << "randlist_012: " << randlist_012() << std::endl;
  
  typedef fas::transform_if< 
    randlist_012, 
    make_foo<_1>,
    fas::or_< 
      fas::equal_to< int_<0>, _1 >, 
      fas::equal_to< int_<2>, _1 > 
    >
  >::type foo_1_list;
  
  std::cout << "foo_1_list: " << foo_1_list() << std::endl;
  
  typedef fas::transform_if< 
    foo_1_list, 
    make_bar<_1>,
    is_int<_1>
  >::type foo_bar_list;
  
  std::cout << "foo_bar_list: " << foo_bar_list() << std::endl;
  /*
  typedef fas::generate< int_<10>, fas::generator< int_<1>, fas::inc<_> > >::type genlist;
  std::cout << "genlist: " << genlist() << std::endl;
  std::cout << "count_if<genlist, x%2==0>: " 
            << fas::count_if< genlist, fas::equal_to< int_<0>, fas::modulus< _, int_<2> > > >::value
            << std::endl;
  std::cout << "select<genlist, x%2!=0>: " 
            << fas::select< genlist, fas::modulus< _, int_<2> > >::type() 
            << std::endl;
  std::cout << "erase_if<genlist, x%2!=0>: " 
            << fas::erase_if< genlist, fas::modulus< _, int_<2> > >::type() 
            << std::endl;
  std::cout << "sort<genlist, greater>: " 
            << fas::sort<genlist, fas::greater<_, _> >::type() 
            << std::endl;
  std::cout << "random_shuffle<1,genlist>: " << fas::random_shuffle<int_<1>, genlist>::type() << std::endl;
  std::cout << "random_shuffle<2,genlist>: " << fas::random_shuffle<int_<2>, genlist>::type() << std::endl;
  std::cout << "random_shuffle<3,genlist>: " << fas::random_shuffle<int_<3>, genlist>::type() << std::endl;
  */
  return 0;
}