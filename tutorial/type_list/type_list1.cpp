#include "../out_type_list.hpp"
#include <fas/type_list.hpp>
#include <fas/integral.hpp>

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
