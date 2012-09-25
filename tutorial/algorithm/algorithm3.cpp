#include <fas/type_list.hpp>
#include <fas/algorithm.hpp>
#include <fas/mp.hpp>
#include <fas/integral.hpp>
#include <fas/typemanip.hpp>

#include <iostream>

using fas::int_;
using fas::_1;
using fas::a;
using fas::p;

int ffactorial(int i)
{
  int result = 1;
  for ( ; i > 0; result*=i, --i);
  return result;
}

/*
  This is demonstrate for_ only as analogue ffactorial, really:

  template<int N>
  struct factorial { enum { value = N * factorial<N-1>::value }; };
  template<>
  struct factorial<1> { enum { value = 1 };};
*/
struct nan;
template<int I>
struct factorial:
  fas::static_error<nan, (I>=0) >::type
{
  typedef typename fas::for_<
    // initial and current result
    fas::pair<
      fas::int_<I>,
      fas::int_<1>
    >,
    // check current result _1
    fas::greater< fas::first< _1 >, int_<0> >,
    // update current result _1
    fas::pair<
      fas::dec< fas::first< _1 > >,
      fas::times< fas::second< _1 >, fas::first< _1 > >
    >
  >::type result;

  typedef typename result::first  first;  // always int_<0>
  typedef typename result::second second; // int_< I! >
  enum { value = second::value};
};



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

int flcm(int a, int b)
{
  return a * b / fgcd (a, b);
}

// least common multiple
template<typename A, typename B>
struct lcm:
  fas::divides< typename fas::times<A, B>::type, typename gcd<A, B>::type >
{};

// least common multiple
template<typename A, typename B>
struct lcm2:
  fas::apply< fas::divides< fas::times<A, B>, gcd<A, B> > >::type
{};


int main()
{
  std::cout << "ffactorial(4):" << ffactorial(4) << std::endl;
  std::cout << "factorial<4>:" << factorial<4>::value << std::endl;
  std::cout << "fgcd(5,15): " << fgcd(5,15) << std::endl;
  std::cout << "flcm(18,45): " << flcm(18,45) << std::endl;

  std::cout << "gcd<5,15>: " << gcd< int_<5>, int_<15> >::value << std::endl;
  std::cout << "lcm<18,45>: " << lcm< int_<45>, int_<18> >::value << std::endl;
  std::cout << "lcm2<18,45>: " << lcm2< int_<45>, int_<18> >::value << std::endl;
  return 0;
}