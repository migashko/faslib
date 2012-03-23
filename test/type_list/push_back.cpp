#include <fas/type_list/type_list.hpp>
#include <fas/static_check.hpp>
#include <fas/type_list/push_back.hpp>
#include <fas/type_list/length.hpp>
#include <fas/type_list/type_at.hpp>


using namespace ::fas;

struct list_1 : type_list<char, type_list<long> > {};
struct list_2 : type_list<float, type_list<int> > {};


typedef push_back<list_1, list_2>::type result_list;
typedef type_list<float, type_list<int, list_1 > > check_list1;

int main()
{
  /*
  result_list x;
  x.method();
  */
  enum 
  {
    test_length = static_check< length< result_list>::value == 4 >::value,
    test0 = static_check< some_type< type_at< int_<0>, result_list>::type, float>::value >::value,
    test1 = static_check< some_type< type_at< int_<1>, result_list>::type, int>::value >::value,
    test2 = static_check< some_type< type_at< int_<2>, result_list>::type, char>::value >::value,
    test3 = static_check< some_type< type_at< int_<3>, result_list>::type, long>::value >::value,
    test = static_check< some_type< check_list1, result_list>::value >::value,
    
  };
  
  return 0;
}


