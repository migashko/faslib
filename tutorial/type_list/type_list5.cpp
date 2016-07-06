#include <fas/type_list.hpp>
#include <fas/integral.hpp>

#include <iostream>

namespace std
{
  template<typename L, typename R>
  ostream& operator << ( ostream& os, fas::type_list<L,R> );
  template<typename L>
  ostream& operator << ( ostream& os, fas::type_list<L,fas::empty_list> );
  ostream& operator << ( ostream& os, fas::empty_list );

  template<typename L, typename R>
  ostream& operator << ( ostream& os, fas::type_list<L,R> )  { os << static_cast<int>(L::value) << ", " << R(); return os;}

  template<typename L>
  ostream& operator << ( ostream& os, fas::type_list<L,fas::empty_list> )  { os << static_cast<int>(L::value); return os; }

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

typedef fas::split_c< fas::length<list>::value / 2, list>::type list_pair;

typedef fas::merge<
  fas::erase_c< fas::length< list_pair::first >::value-1, list_pair::first>::type,
  fas::erase_c< 0, list_pair::second>::type
>::type modified_list;

int main()
{
  std::cout << "list : " << list() << std::endl;
  std::cout << "modified list: " << modified_list() << std::endl;
  return 0;
}
