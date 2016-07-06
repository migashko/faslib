#include "../out_type_list.hpp"
#include <fas/type_list.hpp>
#include <fas/integral.hpp>

typedef fas::type_list_n<
  fas::int_<1>,
  fas::int_<2>,
  fas::int_<3>,
  fas::int_<4>,
  fas::int_<5>
>::type list;

typedef fas::push_front< fas::int_<0>, list>::type list1;
typedef fas::push_back< fas::int_<6>, list1>::type list2;

int main()
{
  std::cout << "list : " << list() << std::endl;
  std::cout << "list1: " << list1() << std::endl;
  std::cout << "list2: " << list2() << std::endl;
  std::cout << "erase_c<3,list2>: " << fas::erase_c<3,list2>::type() << std::endl;
  std::cout << "reverse<list2>: " << fas::reverse<list2>::type() << std::endl;

  return 0;
}
