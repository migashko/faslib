//#include <fas/utility.hpp>

#include <fas/integral/comparisons.hpp>
#include <fas/mp/apply.hpp>
//#include <fas/bind.hpp>
//#include <fas/lambda.hpp>
#include <fas/typemanip/if_.hpp>
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
    test0 = static_check< 
        some_type<
          apply< std::vector<_1>, int >::type,
          std::vector<int>
        >::value == 1
    >::value,

    test1 = static_check<
        apply<
          if_<
            less<_1, _2>,
            _3,
            if_< less<_3, int_<10> >, _1, _2 >
          >,
          int_<20>, int_<10>,
          int_<3>, int_<4>
        >::type::value == 20
    >::value,
    
    

    /*
    test1_list = static_check<
        apply_list<
          if_<
            less<_1, _2>,
            _3,
            if_< less<_3, int_<10> >, _1, _2 >
          >,
          type_list_n< int_<20>, int_<10>, int_<3>, int_<4> >::type
        >::type::value == 20
    >::value,*/

/*
    test2 = static_check<
        bind<
        if_<
        less<_1, _2>,
        _3,
        if_< less<_3, int_<10> >, _4, _2 >
        > >::apply<
          int_<20>, int_<10>,
          int_<3>, int_<4>
          >::type::value == 4
      >::value,*/
      
  test3 = static_check< some_type< apply<int>::type, int >::value  >::value,
  
  test4 = static_check< some_type< apply< type2type<_1>, int >::type, type2type<int> >::value  >::value,
  
  test41 = static_check< some_type< apply< type2type<_1>, int >::type, type2type<int> >::value  >::value,
  
  test5 = static_check< some_type< apply< p<int> >::type, int >::value  >::value,

  test6 = static_check< some_type< apply< p< a< p<int> > > >::type, p<int> >::value  >::value,

  test7 = static_check< some_type< apply< std::pair< _1, p<_1> >, int >::type, std::pair<int, _1> >::value  >::value,
  
  test8 = static_check< some_type< apply< test_type<_1>, int >::type, std::vector<int> >::value  >::value,
  
  test9 = static_check< some_type< apply< a< test_type<_1> >, int >::type, test_type<int> >::value  >::value,

  //test6 = static_check< some_type< apply< p< p<int> > >::type, p<int> >::value  >::value,
  //typedef apply< lambda<type2type<_1> >, int > type;

  };
  
  return 0;
}


