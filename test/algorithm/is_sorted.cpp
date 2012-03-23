#include <fas/type_list/type_list_n.hpp>
#include <fas/algorithm/is_sorted.hpp>
#include <fas/static_check.hpp>
#include <fas/integral/less.hpp>
#include <fas/integral/greater.hpp>
#include <fas/integral/less_equal.hpp>


int main()
{
  using namespace ::fas;
  enum 
  {
    result = static_check< is_sorted< int >::value >::value
             + static_check< is_sorted< int_<4> >::value >::value
             + static_check< is_sorted< empty_list >::value >::value
             + static_check< is_sorted< type_list_n< int_<1>, int_<2> >::type >::value >::value
             + static_check< is_sorted_t< type_list_n< int_<1>, int_<2> >::type >::value >::value
             + static_check< !is_sorted< type_list_n< int_<2>, int_<1> >::type >::value >::value
             + static_check< is_sorted< type_list_n< int_<1>, int_<1> >::type >::value >::value
             + static_check< is_sorted< type_list_n< int_<2>, int_<1> >::type, greater<_1, _2> >::value >::value
             + static_check< is_sorted_t< type_list_n< int_<2>, int_<1> >::type, greater >::value >::value
             + static_check< is_sorted< type_list_n< int_<2>, int_<1> >::type, less<_2, _1> >::value >::value
             + static_check< is_sorted< type_list_n< int_<2>, int_<1> >::type, less_equal<_2, _1> >::value >::value
             + static_check< is_sorted< type_list_n< int_<3>, int_<2>, int_<1> >::type, less_equal<_2, _1> >::value >::value
             + static_check< is_sorted< type_list_n< int_<3>, int_<2>, int_<2> >::type, less_equal<_2, _1> >::value >::value
             + static_check< !is_sorted< type_list_n< int_<3>, int_<2>, int_<3> >::type, less_equal<_2, _1> >::value >::value
  };
  return 0;
}


