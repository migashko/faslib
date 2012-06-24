//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/integral/comparisons.hpp>
#include <fas/mp/lambda.hpp>
#include <fas/typemanip.hpp>
#include <fas/integral/logical_op.hpp>
#include <fas/static_check.hpp>
#include <vector>

template<typename T>
struct test_type
{
  typedef std::vector<T> type;
};

int main()
{
  using namespace ::fas;

  enum
  {
    test =  static_check<
              some_type<
                lambda< std::vector<_1> >::apply<int>::type,
                std::vector<int>
              >::value == 1
            >::value

        + static_check<
            lambda<
              if_<
                less<_1, _2>,
                _3,
                if_< less<_3, int_<10> >, _1, _2 >
              > 
            >::apply< int_<20>,  int_<10>, int_<3> >::type::value == 20
        >::value

        + static_check< some_type< lambda<int>::apply<>::type, int >::value  >::value
  
        + static_check< some_type< lambda< type2type<_1> >::apply< int >::type, type2type<int> >::value  >::value
  
        + static_check< some_type< lambda< p<int> >::apply<>::type, int >::value  >::value

        + static_check< some_type< lambda< p< a< p<int> > > >::apply<>::type, p<int> >::value  >::value

        + static_check< some_type< lambda< std::pair< _1, p<_1> > >::apply< int >::type, std::pair<int, _1> >::value  >::value
  
        + static_check< some_type< lambda< test_type<_1> >::apply< int >::type, std::vector<int> >::value  >::value
  
        + static_check< some_type< lambda< a< test_type<_1> > >::apply< int >::type, test_type<int> >::value  >::value
  };
  
  return 0;
}


