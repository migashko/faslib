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
  fas::int_<5>,
  fas::int_<6>
>::type list;

typedef fas::split_c< fas::length<list>::value / 2, list>::type split_list;

typedef fas::merge<
  fas::erase_c< fas::length< split_list::first >::value-1, split_list::first>::type,
  fas::erase_c< 0, split_list::second>::type
>::type list1;

int main()
{
  std::cout << "list : " << list() << std::endl;
  std::cout << "list1: " << list1() << std::endl;
  return 0;
}
