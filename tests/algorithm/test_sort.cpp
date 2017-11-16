//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/type_list/type_list_n.hpp>
#include <fas/algorithm/sort.hpp>
#include <fas/mp/f.hpp>
#include <fas/typemanip.hpp>
#include <fas/static_check.hpp>
#include <fas/integral/less.hpp>
#include <fas/integral/greater.hpp>
#include <fas/integral/less_equal.hpp>

using namespace ::fas;

template<typename L, typename F = less<_1, _2> >
struct test
{
  enum
  {
    result = static_check< is_sorted< typename sort<L, F>::type, F >::value >::value
  };
};

typedef type_list_n< int_<3>, int_<2>, int_<3>, int_<1> >::type list1;
typedef type_list_n< int_<1>, int_<2>, int_<3>, int_<3> >::type check1_1;
typedef type_list_n< int_<3>, int_<3>, int_<2>, int_<1> >::type check1_2;

struct A{};
struct B:A{};
struct C:B{};
struct D:C{};

typedef type_list_n< C, B, A, A, D >::type list2;
typedef type_list_n< A, A, B, C, D >::type check2_1;
typedef type_list_n< D, C, B, A, A >::type check2_2;


int main()
{
  enum 
  {
    result = test<int>::result
             + test< int_<4> >::result
             + test< empty_list >::result
             + test< type_list_n< int_<1>, int_<2> >::type >::result
             + test< type_list_n< int_<2>, int_<1> >::type >::result
             + test< type_list_n< int_<1>, int_<1> >::type >::result
             + test< type_list_n< int_<2>, int_<1> >::type, greater<_1, _2> >::result
             + test< type_list_n< int_<2>, int_<1> >::type, less<_2, _1> >::result
             + test< type_list_n< int_<2>, int_<1> >::type, less_equal<_2, _1> >::result
             + test< type_list_n< int_<3>, int_<2>, int_<1> >::type, less_equal<_2, _1> >::result
             + test< type_list_n< int_<3>, int_<2>, int_<2> >::type, less_equal<_2, _1> >::result
             + test< type_list_n< int_<3>, int_<2>, int_<3> >::type, less_equal<_2, _1> >::result
             + static_check< same_type<check1_1, sort<list1>::type >::value  >::value
             + static_check< same_type<check1_2, sort<list1, greater<_1, _2> >::type >::value  >::value
             + static_check< same_type<check1_1, sort<list1, greater<_2, _1> >::type >::value  >::value
             + static_check< same_type<check1_2, sort_t<list1, greater >::type >::value  >::value
             + static_check< same_type<check1_2, sort<list1, less<_2, _1> >::type >::value  >::value
             + static_check< same_type<check2_1, sort<list2, f< super_subclass<_1, _2> > >::type >::value  >::value
             + static_check< same_type<check2_1, sort_t<list2, lambda< super_subclass<_1, _2> >::apply  >::type >::value  >::value
             + static_check< same_type<check2_2, sort<list2, f< super_subclass<_2, _1> > >::type >::value  >::value
  };
  return 0;
}
