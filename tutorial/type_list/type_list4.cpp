#include "../out_type_list.hpp"
#include <fas/type_list.hpp>
#include <fas/integral.hpp>


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
  std::cout << "type_count<int_<-1>>: " << static_cast<int>(fas::type_count<fas::int_<-1>, list >::value) << std::endl;
  std::cout << "unique<list>: " << fas::unique<list>::type() << std::endl;
  std::cout << "unique_first<list>: " << fas::unique_first<list>::type() << std::endl;

  return 0;
}
