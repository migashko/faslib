#include <fas/type_list/type_list_n.hpp>
#include <fas/algorithm/transform.hpp>
#include <fas/typemanip.hpp>
#include <fas/static_check.hpp>
/*#include <fas/integral/less.hpp>
#include <fas/integral/greater.hpp>
#include <fas/integral/less_equal.hpp>
*/

#include <string>

using namespace ::fas;

typedef type_list_n<
	char, 
	int,
	long,
	double
>::type list1;

typedef type_list_n<
  type2type<char>,
  type2type<int>,
  type2type<long>,
  type2type<double>
>::type list2;

void test1()
{
  using namespace ::fas;
  typedef transform<list1, type2type<_1> >::type result_type;
  enum { result = some_type<result_type, list2>::value };
}

void test2()
{
  /*
  using namespace ::fas;
  typedef generate< int_<4>, generator< int_<0>, make_int< rand<_1> > > >::type genlist;
  typedef transform<list1, type2type<_1> >::type wraplist;
  typedef transform2<genlist, wraplist, pair<_1, _2> >::type pairlist;
  */
}

int main()
{
  test1();
  test2();
  return 0;
}


