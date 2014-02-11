//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/integral/comparisons.hpp>
#include <fas/mp/apply.hpp>
#include <fas/typemanip.hpp>
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
    test = static_check<
            same_type<
              apply< std::vector<_1>, int >::type,
              std::vector<int>
            >::value == 1
          >::value

        + static_check<
            apply<
              if_<
                less<_1, _2>,
                _3,
                if_< less<_3, int_<10> >, _1, _2 >
              >,
              int_<20>, int_<10>,
              int_<3>, int_<4>
            >::type::value == 20
          >::value
    
        + static_check< same_type< apply<int>::type, int >::value  >::value
  
        + static_check< same_type< apply< type2type<_1>, int >::type, type2type<int> >::value  >::value
  
        + static_check< same_type< apply< type2type<_1>, int >::type, type2type<int> >::value  >::value
  
        + static_check< same_type< apply< p<int> >::type, int >::value  >::value

        + static_check< same_type< apply< p< a< p<int> > > >::type, p<int> >::value  >::value

        + static_check< same_type< apply< std::pair< _1, p<_1> >, int >::type, std::pair<int, _1> >::value  >::value
  
        + static_check< same_type< apply< test_type<_1>, int >::type, std::vector<int> >::value  >::value
  
        + static_check< same_type< apply< a< test_type<_1> >, int >::type, test_type<int> >::value  >::value
  };
  
  return 0;
}


