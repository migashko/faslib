#include <fas/type_list.hpp>
#include <fas/static_check.hpp>
#include <fas/type_list/erase.hpp>
#include <fas/integral/int_.hpp>



using namespace ::fas;

struct list_1 : type_list<char, type_list<long> > {};
struct list_2 : type_list<float, type_list<int, list_1> > {};

typedef type_list<int, list_1> check_0;
typedef type_list<float, type_list<int, type_list<char> > > check_3;


int main()
{
  enum {
    test1 = static_check< some_type< erase< int_<0>, list_2>::type, check_0>::value >::value,
    test2 = static_check< some_type< erase< int_<3>, list_2>::type, check_3>::value >::value/*,
    test3 = static_check< some_type< erase< int_<6>, list_2>::type, check_3>::value >::value,
    test4 = static_check< some_type< erase< int_<-6>, list_2>::type, check_3>::value >::value*/
  };
  return 0;
}


