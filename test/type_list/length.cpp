#include <fas/type_list/type_list.hpp>
#include <fas/type_list/empty_list.hpp>
#include <fas/static_check.hpp>
#include <fas/type_list/length.hpp>
#include <string>

using namespace ::fas;

struct good_list: type_list<char, type_list< int, type_list< long > > > {};
struct void_list: empty_list {};
struct one_list: type_list<char[12]> {};


int main()
{
  enum {
    test1_1 = static_check< length<good_list>::value == 3 >::value,
    test1_2 = static_check< length<void_list>::value == 0 >::value,
    test1_3 = static_check< length<one_list>::value == 1 >::value,
    /*test1_4 = static_check< length<int>::value == 1 >::value,
    test1_5 = static_check< length< type_list<int, char>  >::value == 2 >::value
    */
    
  };
  return 0;
}


