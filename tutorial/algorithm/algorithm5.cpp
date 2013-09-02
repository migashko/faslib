#include <fas/type_list.hpp>
#include <fas/algorithm.hpp>
#include <fas/mp.hpp>
#include <fas/integral.hpp>
#include <fas/typemanip.hpp>

#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>

/// For example only

size_t factorial(size_t n)
{
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

std::vector< std::vector<int> > fbrute_combinations(std::vector<int> v)
{
  size_t size = factorial(v.size());
  std::vector< std::vector<int> > result;
  result.push_back(v);
  int i = 0;
  while ( result.size() < size )
  {
    ++i;
    std::random_shuffle(v.begin(), v.end());
    result.push_back(v);
    std::sort(result.begin(), result.end());
    std::vector< std::vector<int> >::iterator itr = std::unique(result.begin(), result.end() );
    result.resize( std::distance(result.begin(), itr) );
  }
  return result;
}

using fas::_1;
using fas::wrapper;
using fas::int_;
using fas::type_list_n;

namespace std
{
  template<typename L, typename R>
  ostream& operator << ( ostream& os, fas::type_list<L,R> )  { os << L::value  << ", " << R(); return os;}

  template<typename L>
  ostream& operator << ( ostream& os, fas::type_list<L, fas::empty_list> )  { os << L::value; return os;}

  template<typename L, typename R>
  ostream& operator << ( ostream& os, fas::type_list< wrapper<L>, R> )  { os << std::endl << L() << R(); return os;}

  template<typename L>
  ostream& operator << ( ostream& os, fas::type_list< wrapper<L>, fas::empty_list> )  { os << std::endl <<L(); return os; }

  ostream& operator << ( ostream& os, fas::empty_list )  { return os; }
}

typedef fas::type_list_n<
  wrapper< type_list_n< int_<1>, int_<2>, int_<3> >::type >,
  wrapper< type_list_n< int_<1>, int_<3>, int_<2> >::type >,
  wrapper< type_list_n< int_<2>, int_<1>, int_<3> >::type >,
  wrapper< type_list_n< int_<2>, int_<3>, int_<1> >::type >,
  wrapper< type_list_n< int_<3>, int_<1>, int_<2> >::type >,
  wrapper< type_list_n< int_<3>, int_<2>, int_<1> >::type >
>::type list_of_list;

template<typename L>
struct brute_combinations
{
  enum { count = fas::factorial< int_<fas::length<L>::value> >::value };

  typedef typename fas::for_<

    // initial and result
    fas::pair<
      int_<1>,
      fas::type_list< wrapper< L> >
    >,

    // condition
    fas::less<
      fas::length< fas::second<_1> >,
      int_<count>
    >,

    // update
    fas::pair<
      // next rand number
      fas::inc< fas::first<_1> >,
      // remove dublicates
      fas::unique<
        // add to the top of the list shuffled and wrapped incoming list
        fas::push_front<
          fas::second<_1>,
          fas::wrap<
            fas::random_shuffle< fas::rand< fas::first<_1> >, L >
          > // wrap
        > // push_front
      > // unique
    > // pair
  >::type result;
  typedef typename result::second type;
  typedef typename result::first  iterations;
};

typedef type_list_n< int_<1>, int_<2>, int_<3> >::type list;
typedef type_list_n< int_<1>, int_<2>, int_<3>, int_<4>, int_<5> >::type list2;

int main()
{
  std::cout << "list_of_list():" << std::endl;
  std::cout << list_of_list() << std::endl;
  
  std::cout << "fbrute_combinations():" << std::endl;
  typedef std::vector<int> v_type;
  typedef std::vector< v_type > vv_type;
  v_type v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  vv_type vv = fbrute_combinations(v);
  for (vv_type::iterator vvitr=vv.begin(); vvitr!=vv.end(); ++vvitr)
  {
    for (v_type::iterator vitr=vvitr->begin(); vitr!=vvitr->end(); ++vitr)
      std::cout << *vitr << ", ";
    std::cout << std::endl;
  }
  std::cout << "brute_combinations<list>::type():" << std::endl;
  std::cout << brute_combinations<list>::type() << std::endl;
  std::cout << "brute_combinations<list>::iterations::value:" << std::endl;
  std::cout << brute_combinations<list>::iterations::value << std::endl;
  // gcc-4.6 allocated over 14GB!!!
  // std::cout << brute_combinations<list2>::type() << std::endl;
  return 0;
}
