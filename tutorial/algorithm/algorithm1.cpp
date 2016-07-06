#include "../out_type_list.hpp"
#include <fas/type_list.hpp>
#include <fas/algorithm.hpp>
#include <fas/integral.hpp>

int main()
{
  using fas::_;
  using fas::int_;
  typedef fas::generate< int_<10>, fas::generator< int_<1>, fas::inc<_> > >::type genlist;
  std::cout << "genlist: " << genlist() << std::endl;
  std::cout << "count_if<genlist, x%2==0>: "
            << static_cast< int >( fas::count_if< genlist, fas::equal_to< int_<0>, fas::modulus< _, int_<2> > > >::value )
            << std::endl;
  std::cout << "select<genlist, x%2!=0>: "
            << fas::select< genlist, fas::modulus< _, int_<2> > >::type()
            << std::endl;
  std::cout << "erase_if<genlist, x%2!=0>: "
            << fas::erase_if< genlist, fas::modulus< _, int_<2> > >::type()
            << std::endl;
  std::cout << "sort<genlist, greater>: "
            << fas::sort<genlist, fas::greater<_, _> >::type()
            << std::endl;
  std::cout << "random_shuffle<1,genlist>: " << fas::random_shuffle<int_<1>, genlist>::type() << std::endl;
  std::cout << "random_shuffle<2,genlist>: " << fas::random_shuffle<int_<2>, genlist>::type() << std::endl;
  std::cout << "random_shuffle<3,genlist>: " << fas::random_shuffle<int_<3>, genlist>::type() << std::endl;
  return 0;
}
