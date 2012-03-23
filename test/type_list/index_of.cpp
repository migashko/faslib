#include <fas/type_list/type_list.hpp>
#include <fas/static_check.hpp>
#include <fas/type_list/index_of.hpp>


using namespace ::fas;

struct good_list: type_list<char, type_list< int, type_list< long > > > {};
struct void_list: empty_list {};
struct one_list: type_list<char[12]> {};

struct A{};
struct B:A{};
struct C{};
struct D:C{};

struct abc_list: type_list<A, type_list<B, type_list<C, type_list<D> > > > {};

int main()
{
  enum {
    test1_1 = static_check< index_of<char, good_list>::value == 0 >::value,
    test1_1_1 = static_check< index_of<char, empty_list>::value == -1 >::value,
    test1_2 = static_check< index_of<int, good_list>::value == 1 >::value,
    test1_3 = static_check< index_of<long, good_list>::value == 2 >::value,
    test1_4 = static_check< index_of<unsigned char, good_list>::value == -1 >::value,
    test1_5 = static_check< index_of<char, void_list>::value == -1 >::value,
    test1_6 = static_check< index_of<char*, one_list>::value == -1 >::value,
    test1_7 = static_check< index_of<char[12], one_list>::value == 0 >::value,
    test2_1 = static_check< index_of<A, abc_list>::value == 0 >::value,
    test2_2 = static_check< index_of<B, abc_list>::value == 1 >::value,
    test2_3 = static_check< index_of<C, abc_list>::value == 2 >::value,
    test2_4 = static_check< index_of<D, abc_list>::value == 3 >::value,
  };
  return 0;
}


