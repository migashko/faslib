#include <fas/type_list/type_list_n.hpp>
//#include <fas/type_list_n.hpp>
#include <fas/static_check.hpp>
#include <fas/algorithm/unique_if.hpp>
#include <fas/type_list/type_at.hpp>

using namespace ::fas;


struct list_1 : type_list_n<char, int, long>::type {};
struct list_2 : type_list_n<char, int, double, list_1>::type {};
struct list_3 : type_list_n<list_1, char, int, double>::type {};
struct list_4 : type_list_n<char, int, int>::type {};
typedef type_list_n<
    double,
    list_1
    >::type check_list1;

typedef type_list_n<
    long, char, int, double
>::type check_list2;

typedef type_list_n<
    char, int
>::type check_list3;

typedef unique_if<list_2>::type result_list1;
typedef unique_if<list_3>::type result_list2;
typedef unique_if<list_4>::type result_list3;


int main()
{
  
  enum {
    
    test_lenght = static_check< length<result_list1>::value == 4 >::value,
    test0 = static_check< some_type< type_at< int_<0>, result_list1>::type, double>::value >::value,
    test0_1 = static_check< some_type< type_at< int_<0>, result_list3>::type, char>::value >::value,
    test0_2 = static_check< some_type< type_at< int_<1>, result_list3>::type, int>::value >::value,
    test1 = static_check< some_type< result_list1, check_list1>::value >::value,
    test2 = static_check< some_type< result_list2, check_list2>::value >::value,
    test3 = static_check< some_type< result_list3, check_list3>::value >::value,
    // test2 = static_check< some_type< erase<3, list_2>::type, check_3>::value >::value,
  };
  return 0;
}


