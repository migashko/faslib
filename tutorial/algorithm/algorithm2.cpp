#include <fas/type_list.hpp>
#include <fas/algorithm.hpp>
#include <fas/mp.hpp>
#include <fas/integral.hpp>

#include <iostream>

namespace std
{
  template<typename L, typename R>
  ostream& operator << ( ostream& os, fas::type_list<L,R> )  { os << L::value << ", " << R(); return os;}
  
  template<typename L>
  ostream& operator << ( ostream& os, fas::type_list<L,fas::empty_list> )  { os << L::value; return os; }
  
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

template<typename T, template <int> class Fi >
struct make
{
  typedef Fi<T::value> type;
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
  using fas::int_;
  
  typedef fas::tail<
    fas::generate<
      fas::int_<11>, 
      fas::generator< 
        int_<42>, 
        fas::modulus< fas::rand<_>, int_<3> >
      > 
    >::type 
  >::type randlist;
  
  std::cout << "randlist: " << randlist() << std::endl;
  
  typedef fas::transform_if< 
    randlist, 
    make<_, foo>
    fas::or_< 
      fas::equal_to< int_<0>, _1 >, 
      fas::equal_to< int_<2>, _1 > 
    >  
  >::type list1;
  
  
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