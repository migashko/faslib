//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/type_list/type_list.hpp>
#include <fas/utility/ignore_args.hpp>
#include <string>

using namespace ::fas;

struct A{};
struct B:A{};
struct C{ B b;};

typedef wchar_t wc_array[10];
typedef type_list< A, 
  type_list< B, 
  type_list< C, 
  type_list< int,
  type_list< double,
  type_list< std::string,
  type_list< const char*,
  type_list< wc_array
  > > > > > > > > type_list1;

int main()
{
  type_list1 t1;
  type_list1 t2;
  t1 = t2;
  fas::ignore_args(t1, t2);
  return 0;
}
