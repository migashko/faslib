#include <fas/type_list/type_list.hpp>
#include <fas/type_list/empty_list.hpp>
#include <fas/static_check.hpp>
#include <fas/type_list/check_list.hpp>
#include <fas/typemanip/some_type.hpp>
#include <string>

using namespace ::fas;

struct no_typelist{};
struct bad_metatype{ typedef int metatype;};
struct void_list: empty_list{};
struct good_list: type_list<char, type_list< int, type_list< long > > > {};
struct bad_list: type_list< type_list< int, type_list< long > >, char > {};


int main()
{
  enum {
    test1_1 = static_check< !check_list<no_typelist>::value >::value,
    test1_2 = static_check<
        some_type<
          check_list<no_typelist>::error,
          errorlist::type_without_metatype 
        >::value
    >::value,
    test2_1 = static_check< !check_list<bad_metatype>::value >::value,
    test2_2 = static_check<
        some_type<
          check_list<bad_metatype>::error,
          errorlist::bad_metatype
        >::value
    >::value,
    test3_1 = static_check< check_list<void_list>::value >::value,
    test3_2 = static_check<
        some_type<
          check_list<void_list>::error,
          errorlist::noerror
        >::value
    >::value,
    test4_1 = static_check< !check_list<bad_list>::value >::value,
    test4_2 = static_check<
        some_type<
          check_list<bad_list>::error,
          errorlist::not_organized
        >::value
    >::value,
  };
  return 0;
}


