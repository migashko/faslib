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

typedef fas::type_list<
  fas::int_<1>, fas::type_list<
  fas::int_<2>, fas::type_list<
  fas::int_<3>
> > > int_list;

int main()
{
  std::cout << int_list () << std::endl;
  return 0;
}