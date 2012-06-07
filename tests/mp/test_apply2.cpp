//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/mp/apply.hpp>
#include <fas/algorithm.hpp>
#include <fas/integral.hpp>
#include <fas/static_check.hpp>
#include <fas/type_list.hpp>
#include <vector>

using namespace ::fas;

typedef type_list_n< int_<1>, int_<2>, int_<3>, int_<4> >::type list;

namespace test1
{
  typedef 
      transform<
        transform<_1, a< pair<int, p<_1> > > >,
        a< second< p<_1> > >
      > list2func;
  typedef apply< list2func, list>::type list2;
  enum { test = static_check< some_type< list2, list>::value == 1 >::value };
}

namespace test2
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

  enum { test = static_check< equal_to< result1, result2>::value == 1 >::value };
}

int main()
{
  enum { value = static_check< apply2< some_type<_,_>, int, int>::type::value >::value };
  return 0;
}


