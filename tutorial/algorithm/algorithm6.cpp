#include "../out_type_list.hpp"
#include <fas/type_list.hpp>
#include <fas/algorithm.hpp>
#include <fas/mp.hpp>
#include <fas/integral.hpp>
#include <fas/typemanip.hpp>

#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>

template<int I>
struct tag: fas::int_<I>{};

template<typename Tg, typename T>
struct tagged
{
  typedef Tg tag;
  typedef T type;
  typedef typename Tg::value_type value_type; 
};

namespace std
{
  template<int N, typename T, typename R>
  ostream& operator << ( ostream& os, fas::type_list< tagged< tag<N>, T >, R > )  
  { 
    os << N << "=" << sizeof( T ) << ", " << R(); 
    return os;
  }

}

template<typename T>
struct get_tag
{
  typedef typename T::value_type value_type;
  typedef typename T::tag type;
  enum { value = type::value};
};

typedef fas::type_list_n<
  tagged< tag<3>, short >,
  tagged< tag<4>, int >,
  tagged< tag<2>, char >,
  tagged< tag<1>, long >
>::type list;

typedef fas::sort< 
  list,
  fas::less<
    fas::a< get_tag< fas::_1 > >,
    fas::a< get_tag< fas::_2 > >
  > 
>::type sorted_list;


int main()
{
  std::cout << sorted_list() << std::endl;
  return 0;
}
