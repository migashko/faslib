#include <fas/type_list/type_list.hpp>
#include <fas/static_check.hpp>
#include <fas/type_list/split.hpp>


using namespace ::fas;

struct list_1 : type_list<char, type_list<long> > {};
struct list_2 : type_list<float, type_list<int, list_1> > {};

typedef empty_list check_0_left;
typedef list_2 check_0_right;

typedef type_list<float> check_1_left;
typedef type_list<int, list_1> check_1_right;


typedef list_2 check_4_left;
typedef empty_list check_4_right;


int main()
{
  
  enum {
    test1 = static_check< some_type< split< int_<0>, list_2>::left_list, check_0_left>::value >::value,
    test2 = static_check< some_type< split< int_<0>, list_2>::right_list, check_0_right>::value >::value,
    test3 = static_check< some_type< split< int_<1>, list_2>::left_list, check_1_left>::value >::value,
    test4 = static_check< some_type< split< int_<1>, list_2>::right_list, check_1_right>::value >::value,
    
    test5 = static_check< some_type< split< int_<4>, list_2>::left_list, check_4_left>::value >::value,
    test6 = static_check< some_type< split< int_<4>, list_2>::right_list, check_4_right>::value >::value,
    

  };
  return 0;
}


