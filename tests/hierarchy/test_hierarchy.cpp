//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/type_list/type_list_n.hpp>
#include <fas/hierarchy/scatter_hierarchy.hpp>
#include <fas/hierarchy/field.hpp>
#include <fas/hierarchy/field_if.hpp>
#include <fas/algorithm/transform.hpp>
#include <fas/typemanip/type2type.hpp>
#include <fas/typemanip/super_subclass.hpp>

//
void test1();
int  test2();

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

  field< type2type<char> >::get(h) = type2type<char>();
  field< apply< type2type<_1>, char>::type >::get(h) = type2type<char>();
  field< C >::get(h) = C();
  field< B >::get(h) = B();
  field_if< same_type<B, _1> >::get(h) = B();
  field_if< super_subclass< A, _1 > >::get(h) = C();
  field_if< super_subclass< B, _1 > >::get(h) = C();
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
  return field< holder<T> >::get(h).value_;
}

inline int d2i100(double val)
{
  return static_cast<int>(val*100);
}

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
  return (get<char>(h) == 'A' && d2i100(get<double>(h)) == d2i100(3.14) && get<int>(h) == 0 ) ? 0 : -1;
}

int main()
{
  test1();
  return test2();
}
