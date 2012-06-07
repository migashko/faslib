#include <fas/type_list/type_list_n.hpp>
#include <fas/hierarchy/scatter_hierarchy.hpp>
#include <fas/hierarchy/field.hpp>
#include <fas/hierarchy/field_if.hpp>
#include <fas/algorithm/transform.hpp>
#include <fas/typemanip/type2type.hpp>
#include <fas/typemanip/super_subclass.hpp>

// 
struct A{};
struct B:A{};
struct C:B{};

void test1()
{
  using namespace ::fas;

  typedef type_list_n<
    type2type<char>, 
    type2type<int>,
    type2type<long>,
    type2type<double>,
    C,
    B
  >::type list;

  typedef scatter_hierarchy<list> hierarchy;
  hierarchy h;

  field< type2type<char> >(h) = type2type<char>();
//  field< char, type2type<_1> >(h) = type2type<char>();
  field< apply< type2type<_1>, char>::type >(h) = type2type<char>();
  field< C >(h) = C();
  field< B >(h) = B();
  field_if< some_type<B, _1> >(h) = B();
  field_if< super_subclass< A, _1 > >(h) = C();
  field_if< super_subclass< B, _1 > >(h) = C();

  /*
  typedef scatter_hierarchy< transform<list, holder<_1> >::type > hierarchy1;
  hierarchy1 h1;
  field< holder<type2type<char> > >(h1).value_ = type2type<char>();
  */
}

template<typename T>
struct holder
{
  T value_;
  holder():value_(){}
};

template<typename T, typename H>
T& get(H& h)
{
  using namespace ::fas;
  return field< holder<T> >(h).value_;
};

int test2()
{
  using namespace ::fas;
  typedef type_list_n<
    char,
    int,
    long,
    double
  >::type list;

  typedef scatter_hierarchy< transform<list, holder<_1> >::type > hierarchy;

  hierarchy h;
  get<char>(h) = 'A';
  get<double>(h) = 3.14;
  return (get<char>(h) == 'A' && get<double>(h) == 3.14 && get<int>(h) == 0 ) ? 0 : -1;
}



int main()
{
  test1();
  return test2();
}


