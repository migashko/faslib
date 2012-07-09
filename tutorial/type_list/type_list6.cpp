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
  fas::int_<3>
>::type list_a;

typedef fas::int_<4> notlist;

typedef fas::type_list_n<
  fas::int_<5>, 
  fas::int_<6>, 
  fas::int_<7>
>::type list_b;

typedef fas::type_list<
  fas::type_list<list_a, notlist>,
  list_b
> bad_list;

typedef fas::type_list_n<
  fas::type_list<list_a, notlist>,
  list_b
>::type good_list;

int main()
{
  std::cout << "is_organized<list_a>  : " << fas::is_organized<list_a>::value << std::endl;
  std::cout << "is_organized<notlist> : " << fas::is_organized<notlist>::value << std::endl;
  std::cout << "is_organized<list_b>  : " << fas::is_organized<list_b>::value << std::endl;
  std::cout << "is_organized<bad_list>: " << fas::is_organized<bad_list>::value << std::endl;
  std::cout << std::endl;
  std::cout << "is_type_list<list_a>  : " << fas::is_type_list<list_a>::value << std::endl;
  std::cout << "is_type_list<notlist> : " << fas::is_type_list<notlist>::value << std::endl;
  std::cout << "is_type_list<list_b>  : " << fas::is_type_list<list_b>::value << std::endl;
  std::cout << "is_type_list<bad_list>: " << fas::is_type_list<bad_list>::value << std::endl;
  std::cout << std::endl;
  std::cout << "is_type_list<normalize<notlist>>    : " << fas::is_type_list< fas::normalize<notlist>::type >::value << std::endl;
  std::cout << "is_organized<organize<bad_list>>    : " << fas::is_organized< fas::organize<bad_list>::type >::value << std::endl;
  std::cout << "is_organized<type_list_n<bad_list>> : " << fas::is_organized< fas::type_list_n<bad_list>::type >::value << std::endl;
  std::cout << std::endl;
  std::cout << "good_list             : " << good_list() << std::endl;
  std::cout << "organize<bad_list>    : " << fas::organize<bad_list>::type() << std::endl;
  std::cout << "type_list_n<bad_list> : " << fas::type_list_n<bad_list>::type()  << std::endl;
  
  
return 0;
}