#include <fas/type_list.hpp>
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

typedef fas::type_list_n<
  fas::int_<1>,
  fas::int_<2>,
  fas::int_<3>,
  fas::int_<4>,
  fas::int_<5>
>::type list;

int main()
{
  std::cout << "int_list: " << list () << std::endl;
  std::cout << "length<list>: " << fas::length< list >::value << std::endl;
  std::cout << "head<list>: " << fas::head< list >::type::value << std::endl;
  std::cout << "tail<list>: " << fas::tail< list >::type() << std::endl;
  std::cout << "type_at_c<3,list>: " << fas::type_at_c< 3, list >::type::value << std::endl;
  std::cout << "index_of<int_<4>,list>: " << fas::index_of< fas::int_<4>, list >::value << std::endl;

  return 0;
}
