#include <fas/type_list/type_list.hpp>
#include <fas/algorithm/count.hpp>
#include <fas/typemanip.hpp>
#include <fas/static_check.hpp>
#include <fas/mp/lambda.hpp>
#include <string>

using namespace ::fas;

struct good_list: type_list<char, type_list< int, type_list< long, type_list<char> > > > {};
struct void_list: empty_list {};
struct one_list: type_list<char[12]> {};

struct A{};
struct B:A{};
struct C{};
struct D:C,B{};

struct abc_list: type_list<A, type_list<B, type_list<C, type_list<D> > > > {};

int main()
{
  enum 
  {
    value = static_check< count<char, good_list>::value == 2 >::value
            + static_check< count<int, good_list>::value == 1 >::value
            + static_check< count<long, good_list>::value == 1 >::value
            + static_check< count<short, good_list>::value == 0 >::value
            + static_check< count<empty_list, good_list>::value == 0 >::value
            + static_check< count<empty_list, void_list>::value == 0 >::value
            + static_check< count<empty_list, one_list>::value == 0 >::value
            + static_check< count<char[12], one_list>::value == 1 >::value
            + static_check< count<A, abc_list>::value == 1 >::value
            + static_check< count<B, abc_list>::value == 1 >::value
            + static_check< count<C, abc_list>::value == 1 >::value
            + static_check< count<D, abc_list>::value == 1 >::value
            
            + static_check< count_if<abc_list, super_subclass<A, _1> >::value == 3 >::value
            + static_check< count_if<abc_list, super_subclass_strict<A, _1> >::value == 2 >::value
            
            + static_check< count_if_t<abc_list, lambda< super_subclass<A, _1> >::apply >::value == 3 >::value
            + static_check< count_if_t<abc_list, lambda< super_subclass_strict<A, _1> >::apply >::value == 2 >::value
            
  };
	
  return 0;
}


