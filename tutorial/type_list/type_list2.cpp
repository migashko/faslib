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

int main()
{
  std::cout << "int_list: " << list () << std::endl;
  std::cout << "length<list>: " << static_cast<int>( fas::length< list >::value ) << std::endl;
  std::cout << "head<list>: " << static_cast<int>( fas::head< list >::type::value ) << std::endl;
  std::cout << "tail<list>: " << fas::tail< list >::type() << std::endl;
  std::cout << "type_at_c<3,list>: " << static_cast<int>( fas::type_at_c< 3, list >::type::value ) << std::endl;
  std::cout << "index_of<int_<4>,list>: " << static_cast<int>(fas::index_of< fas::int_<4>, list >::value) << std::endl;

  return 0;
}
