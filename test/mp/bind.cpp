//#include <fas/utility.hpp>

#include <fas/mp/bind.hpp>
#include <fas/type_list/type_list_n.hpp>
#include <fas/static_check.hpp>
#include <vector>
#include <string>
#include <map>

using namespace ::fas;


template<typename>
struct test1{};

template<typename, typename>
struct test2{};

template<typename, typename, typename>
struct test3{};

template<typename, typename, typename, typename>
struct test4{};

template<typename, typename, typename, typename, typename>
struct test5{};

int main()
{
  enum {
   test0 = static_check< some_type< int, bind<int>::type >::value == 1 >::value
         + static_check< some_type< int, bind<_1, type_list_n<int>::type >::type >::value == 1 >::value
         + static_check< some_type< int, bind<_1, int >::type >::value == 1 >::value
         + static_check< some_type< std::vector<int>, bind<std::vector<_1>, int >::type >::value == 1 >::value
         + static_check< some_type< std::pair< int, char >, bind< std::pair<int, _2>, type_list_n<int, char>::type >::type >::value == 1 >::value
         
         + static_check< 
              some_type< 
                test2< int, char >, 
                bind< test2<_, _2>, type_list_n<int, char>::type >::type 
              >::value == 1
          >::value

         + static_check< 
              some_type< 
                test2< char, int >, 
                bind< test2<_2, _>, type_list_n<int, char, float>::type >::type 
              >::value == 1
          >::value

  };
  return 0;
}


