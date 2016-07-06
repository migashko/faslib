#include "../out_type_list.hpp"
#include <fas/type_list.hpp>
#include <fas/integral.hpp>


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
  std::cout << "is_organized<list_a>  : " << static_cast<int>(fas::is_organized<list_a>::value) << std::endl;
  std::cout << "is_organized<notlist> : " << static_cast<int>(fas::is_organized<notlist>::value) << std::endl;
  std::cout << "is_organized<list_b>  : " << static_cast<int>(fas::is_organized<list_b>::value) << std::endl;
  std::cout << "is_organized<bad_list>: " << static_cast<int>(fas::is_organized<bad_list>::value) << std::endl;
  std::cout << std::endl;
  std::cout << "is_type_list<list_a>  : " << static_cast<int>(fas::is_type_list<list_a>::value) << std::endl;
  std::cout << "is_type_list<notlist> : " << static_cast<int>(fas::is_type_list<notlist>::value) << std::endl;
  std::cout << "is_type_list<list_b>  : " << static_cast<int>(fas::is_type_list<list_b>::value) << std::endl;
  std::cout << "is_type_list<bad_list>: " << static_cast<int>(fas::is_type_list<bad_list>::value) << std::endl;
  std::cout << std::endl;
  std::cout << "is_type_list<normalize<notlist>>    : " << static_cast<int>(fas::is_type_list< fas::normalize<notlist>::type >::value) << std::endl;
  std::cout << "is_organized<organize<bad_list>>    : " << static_cast<int>(fas::is_organized< fas::organize<bad_list>::type >::value) << std::endl;
  std::cout << "is_organized<type_list_n<bad_list>> : " << static_cast<int>(fas::is_organized< fas::type_list_n<bad_list>::type >::value) << std::endl;
  std::cout << std::endl;
  std::cout << "good_list             : " << good_list() << std::endl;
  std::cout << "organize<bad_list>    : " << fas::organize<bad_list>::type() << std::endl;
  std::cout << "type_list_n<bad_list> : " << fas::type_list_n<bad_list>::type()  << std::endl;
  return 0;
}
