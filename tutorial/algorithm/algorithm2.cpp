#include "../out_type_list.hpp"
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
  template<int i, typename R>
  ostream& operator << ( ostream& os, fas::type_list< foo<i>, R> );
  
  template<int i, typename R>
  ostream& operator << ( ostream& os, fas::type_list< bar<i>, R> );

  template<int i>
  ostream& operator << ( ostream& os, fas::type_list<foo<i>, fas::empty_list> );

  template<int i>
  ostream& operator << ( ostream& os, fas::type_list<bar<i>, fas::empty_list> );

  template<int i, typename R>
  ostream& operator << ( ostream& os, fas::type_list< foo<i>, R> )  { os << "foo-" << i << ", " << R(); return os;}

  template<int i, typename R>
  ostream& operator << ( ostream& os, fas::type_list< bar<i>, R> )  { os << "bar-" << i << ", " << R(); return os;}

  template<int i>
  ostream& operator << ( ostream& os, fas::type_list<foo<i>, fas::empty_list> )  { os << "foo-" << i; return os; }

  template<int i>
  ostream& operator << ( ostream& os, fas::type_list<bar<i>, fas::empty_list> )  { os << "bar-" << i; return os; }

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

  const int init = fas::rand<int_<111> >::value;
  typedef fas::generate<
    fas::int_<10>,
    fas::generator<
      int_<init>,
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
  return 0;
}
