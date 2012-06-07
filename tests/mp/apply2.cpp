//#include <fas/utility.hpp>

//#include <fas/comparisons.hpp>
#include <fas/mp/apply.hpp>
#include <fas/algorithm.hpp>
//#include <fas/lambda.hpp>
#include <fas/integral/logical_op.hpp>
#include <fas/integral/comparisons.hpp>
#include <fas/static_check.hpp>
#include <fas/type_list.hpp>
#include <vector>

using namespace ::fas;

typedef type_list_n< int_<1>, int_<2>, int_<3>, int_<4> >::type list;

int test1()
{
  typedef 
      transform<
        transform<_1, a< pair<int, p<_1> > > >,
        a< second< p<_1> > >
      > list2func;
  typedef apply< list2func, list>::type list2;
  enum { result = static_check< some_type< list2, list>::value == 1 >::value };
  return 0;
};

int test2()
{
  typedef for_<
        int_<10>,
        a< greater< p<_1>, int_<0> > >,
        a< dec< p<_1> > >
      > func;
  typedef apply<func>::type result1;

  typedef for_<
        _1,
        a< greater< p<_1>, int_<0> > >,
        a< dec< p<_1> > >
      > func2;
  typedef apply<func, int_<10> >::type result2;

  enum { result = static_check< equal_to< result1, result2>::value == 1 >::value };
  return 0;
}


int main()
{
  test1();
  test2();
  
  enum { value = static_check< apply2< some_type<_,_>, int, int>::type::value >::value };
  return 0;
}


