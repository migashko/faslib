#include <fas/type_list.hpp>
#include <fas/algorithm.hpp>
#include <fas/mp.hpp>
#include <fas/integral.hpp>
#include <fas/typemanip.hpp>

#include <iostream>
#include <numeric>

using fas::int_;
using fas::_1;
using fas::a;
using fas::p;
int fgcd(int a, int b);
int flcm(int a, int b);
int flcm_n(int* , size_t);

int fgcd(int a, int b)
{
  while (a != b)
  {
    if (a > b)
      a -= b;
    else
      b -= a;
  }
  return a;
}

int flcm(int a, int b)
{
  return a * b / fgcd (a, b);
}

int flcm_n(int* a, size_t count)
{
  return std::accumulate(a, a+count, 1, flcm);
}


// greatest common divisor
template<typename A, typename B>
struct gcd
{
  // for ( [A,B]; A!=B; A>B ? [A-B, B]:[A, B-A] );
  typedef typename fas::for_<
    fas::pair<A, B>,
    fas::not_equal_to< fas::first<_1>, fas::second<_1> >,
    fas::if_<
      fas::greater< fas::first<_1>, fas::second<_1> >, // if A > B
      fas::pair< fas::minus<fas::first<_1>, fas::second<_1> >, fas::second<_1> >, // then [A-B, B]
      fas::pair< fas::first<_1>,  fas::minus<fas::second<_1>, fas::first<_1> > > // else [A, B-A]
    >
  >::type result;

  typedef typename result::first type;
  enum { value = type::value };
};

// least common multiple
template<typename A, typename B>
struct lcm:
  fas::divides< typename fas::times<A, B>::type, typename gcd<A, B>::type >
{};

template<typename L>
struct lcm_n
{
  typedef typename fas::for_<
    fas::pair< int_<1>, L >,
    fas::length< fas::second<_1> >,
    fas::pair<
      lcm< fas::first<_1>, fas::head<fas::second<_1> > >,
      fas::tail<fas::second<_1> >
    >
  >::type result;

  typedef typename result::first type;
  enum { value = type::value };
};

int main()
{
  int arr[] = { 5, 7, 9, 12 };
  
  std::cout << "flcm_n(5,7,9,12):" << flcm_n(arr, 4) << std::endl;

  typedef fas::type_list_n< int_<5>, int_<7>, int_<9>, int_<12> >::type numlist;
  std::cout << " lcm_n<5,7,9,12>:" << static_cast<int>( lcm_n<numlist>::value ) << std::endl;
  return 0;
}
