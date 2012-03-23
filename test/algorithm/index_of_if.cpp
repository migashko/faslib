#include <fas/type_list/type_list.hpp>
#include <fas/static_check.hpp>
#include <fas/algorithm/index_of_if.hpp>
#include <fas/mp/lambda.hpp>


using namespace ::fas;

struct A{};
struct B:A{};
struct C{};
struct D:C{};

struct abc_list: type_list< A, type_list<B, type_list<C, type_list<D> > > > {};

int main()
{
  using namespace ::fas;

  enum 
  {
    test3_1 = static_check< index_of_if< abc_list, super_subclass<_1, D> >::value == 2 >::value
              + static_check< index_of_if_t< abc_list, lambda< super_subclass<_1, D> >::apply >::value == 2 >::value,
    test3_2 = static_check< index_of_if< abc_list, super_subclass<D, _1> >::value == 3 >::value,
    test3_3 = static_check< index_of_if< abc_list, super_subclass_strict<C, _1> >::value == 3 >::value,
    test3_4 = static_check< index_of_if< abc_list, super_subclass_strict<_1, C> >::value == -1 >::value,
    test3_5 = static_check< index_of_if< empty_list, super_subclass_strict<_1, C> >::value == -1 >::value,
  };

  return 0;
}
