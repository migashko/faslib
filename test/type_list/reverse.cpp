#include <fas/type_list/type_list.hpp>
#include <fas/static_check.hpp>
#include <fas/type_list/reverse.hpp>
#include <fas/type_list/index_of.hpp>
#include <fas/type_list/length.hpp>

#include <string>

using namespace ::fas;

struct good_list: type_list<char, type_list< int, type_list< long > > > {};
struct void_list: empty_list {};
struct one_list: type_list<char[12]> {};

int main()
{
  typedef reverse<good_list>::type rgood_list;
  typedef reverse<empty_list>::type rempty_list;
  typedef reverse<one_list>::type rone_list;
  enum {
    test1 = static_check< length<rgood_list>::value == 3 >::value,
    test2 = static_check< length<rempty_list>::value == 0 >::value,
    test3 = static_check< length<rone_list>::value == 1 >::value,
    test4 = static_check< index_of<char, rgood_list>::value == 2 >::value,
    test5 = static_check< index_of<int, rgood_list>::value == 1 >::value,
    test6 = static_check< index_of<long, rgood_list>::value == 0 >::value
  };
  return 0;
}


