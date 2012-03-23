#include <fas/type_list/type_list.hpp>
#include <fas/static_check.hpp>
#include <fas/typemanip/some_type.hpp>
#include <fas/type_list/merge.hpp>

#include <string>

using namespace ::fas;

struct list_1 : type_list<char, type_list<long> > {};
struct list_2 : type_list<float, type_list<int> > {};

typedef type_list<char, type_list<long, list_2 > > check_1;
typedef type_list<float, type_list<int, list_1 > > check_2;

int main()
{
  enum {
    test1 = static_check< some_type<merge<list_1, list_2>::type, check_1>::value >::value,
    test2 = static_check< some_type<merge<list_2, list_1>::type, check_2>::value >::value,
    test3 = static_check< some_type<merge<empty_list, list_1>::type, list_1>::value >::value,
    test4 = static_check< some_type<merge<list_1, empty_list>::type, list_1>::value >::value,
    test5 = static_check< some_type<merge<empty_list, empty_list>::type, empty_list>::value >::value,
    test6 = static_check< some_type<merge<empty_list, int>::type, type_list<int> >::value >::value,
    test7 = static_check< some_type<merge<int, empty_list>::type, type_list<int> >::value >::value,
  };
  return 1;
}


