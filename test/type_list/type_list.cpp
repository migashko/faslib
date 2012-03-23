#include <fas/type_list/type_list.hpp>
#include <string>

using namespace ::fas;

struct A{};
struct B:A{};
struct C{ B b;};

typedef type_list< A, 
  type_list< B, 
  type_list< C, 
  type_list< int,
  type_list< double,
  type_list< std::string,
  type_list< const char*,
  type_list< wchar_t[10]
  > > > > > > > > type_list1;

int main()
{
  type_list1 t1;
  type_list1 t2;
  t1 = t2;
  return 0;
}


