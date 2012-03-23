#include <fas/type_list/type_list_n.hpp>
#include <fas/algorithm/transform.hpp>
#include <fas/algorithm/transform2.hpp>
#include <fas/typemanip.hpp>
#include <fas/static_check.hpp>
#include <fas/typemanip/pair.hpp>
/*#include <fas/integral/less.hpp>
#include <fas/integral/greater.hpp>
#include <fas/integral/less_equal.hpp>
*/

#include <string>
using namespace ::fas;

typedef type_list_n< char, int, long, double>::type list1;
typedef type_list_n< int_<1>, int_<2>, int_<3>, int_<4> >::type list2;
typedef type_list_n< int_<1>, int_<2> >::type list3;
typedef type_list_n< int_<1>, int_<2>, int_<3>, int_<4>, int_<5> >::type list4;

typedef type_list_n< 
    pair< char, int_<1> >,
    pair< int, int_<2> >,
    pair< long, int_<3> >,
    pair< double, int_<4> >
>::type check12;

typedef type_list_n< 
    pair< char, int_<1> >,
    pair< int, int_<2> >,
    pair< long, empty_type >,
    pair< double, empty_type >
>::type check13;

typedef type_list_n< 
    pair< char, int_<1> >,
    pair< int, int_<2> >,
    pair< long, int_<3> >,
    pair< double, int_<4> >,
    pair< empty_type, int_<5> >
>::type check14;

typedef transform2< list1, list2, pair<_1, _2> >::type result12;
typedef transform2< list1, list3, pair<_1, _2> >::type result13;
typedef transform2< list1, list4, pair<_1, _2> >::type result14;

int main()
{
  enum {
    result = static_check< some_type< check12, result12 >::value >::value
            + static_check< some_type< check13, result13 >::value >::value
            + static_check< some_type< check14, result14 >::value >::value
  };
  return 0;
}


