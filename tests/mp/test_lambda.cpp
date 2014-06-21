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

template< template<typename, typename> class F>
struct test12 
{
  typedef typename F< fas::int_<1>, fas::int_<2> >::type type;
};

int main()
{
  using namespace ::fas;

  enum
  {
    test =  static_check<
              same_type<
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

        + static_check< same_type< lambda<int>::apply<>::type, int >::value  >::value
  
        + static_check< same_type< lambda< type2type<_1> >::apply< int >::type, type2type<int> >::value  >::value
  
        + static_check< same_type< lambda< p<int> >::apply<>::type, int >::value  >::value

        + static_check< same_type< lambda< p< a< p<int> > > >::apply<>::type, p<int> >::value  >::value

        + static_check< same_type< lambda< std::pair< _1, p<_1> > >::apply< int >::type, std::pair<int, _1> >::value  >::value
  
        + static_check< same_type< lambda< test_type<_1> >::apply< int >::type, std::vector<int> >::value  >::value
  
        + static_check< same_type< lambda< a< test_type<_1> > >::apply< int >::type, test_type<int> >::value  >::value
  };
  
  typedef type_list_n< _1, _, _2, _>::type exp1;
  typedef fas::type_list_n< int_<1>, int_<1>, int_<2>, int_<2> >::type chk1;
  typedef test12< lambda<exp1>::apply >::type res1;
 
  enum
  {
    test1 = static_check< same_type< res1, chk1 >::value  >::value
  };
  
  
  return 0;
}


