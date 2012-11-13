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
  fas::int_<-1>,
  fas::int_<1>,
  fas::int_<-1>,
  fas::int_<2>,
  fas::int_<-1>
>::type list;

int main()
{
  std::cout << "list : " << list() << std::endl;
  std::cout << "type_count<int_<-1>>: " << fas::type_count<fas::int_<-1>, list >::value << std::endl;
  std::cout << "unique<list>: " << fas::unique<list>::type() << std::endl;
  std::cout << "unique_first<list>: " << fas::unique_first<list>::type() << std::endl;

  return 0;
}
