#include <fas/type_list/type_list_n.hpp>
//#include <fas/type_list_n.hpp>
#include <fas/static_check.hpp>
#include <fas/algorithm/unique_first_if.hpp>
#include <fas/type_list/type_at.hpp>
#include <fas/mp/f.hpp>


using namespace ::fas;

struct list_1 : type_list_n<char, int, long>::type {};
struct list_2 : type_list_n<char, int, double, list_1>::type {};
struct list_3 : type_list_n<list_1, char, int, double>::type {};
struct list_4 : type_list_n<char, int, int>::type {};
typedef type_list_n<
    char, int, double, long
    >::type check_list1;

typedef type_list_n<
    char, int, long, double
>::type check_list2;

typedef type_list_n<
    char, int
>::type check_list3;

typedef unique_first_if<list_2>::type result_list1;
typedef unique_first_if<list_3>::type result_list2;
typedef unique_first_if<list_4>::type result_list3;

template<typename L>
struct some_type_class
{
  template<typename R>
  struct apply
  {
    typedef typename some_type<L, R>::type type;
  };
  
  typedef some_type_class<L> type;
};

struct some_type_metaclass
{
  template<typename L, typename R>
  struct apply
  {
    typedef typename f< some_type<L, R> >::type type;
    /*
    struct type
    {
      template<typename R>
      struct apply
      {
        typedef typename some_type<L, R>::type type;
      };
    };
    */
  };
};

typedef unique_first_if_t<list_4, lambda< some_type<_,_> >::apply >::type result_list3t;
typedef unique_first_if<list_4, some_type_metaclass >::type result_list3tm;
typedef unique_first_if<list_4, some_type<_1, _2 > >::type result_list3mp;

int main()
{
  // static_check< lambda< some_type<_,_>, 2 >::apply<int, char>::type::value > value;
  enum {
	  value = static_check< apply2< some_type<_,_>, int, int>::type::value >::value
			+ static_check<
    some_type<
      some_type<int,char>,
      bind<
        some_type<_,_>,
        type_list_n<int, char>::type
      >::type
    >::value
			>::value
  };
  
  enum {
    test_lenght = static_check< length<result_list1>::value == 4 >::value,
    test0 = static_check< some_type< type_at< int_<0>, result_list1>::type, char>::value >::value,
    test0_1 = static_check< some_type< type_at< int_<0>, result_list3>::type, char>::value >::value,
    test0_2 = static_check< some_type< type_at< int_<1>, result_list3>::type, int>::value >::value,
    test1 = static_check< some_type< result_list1, check_list1>::value >::value,
    test2 = static_check< some_type< result_list2, check_list2>::value >::value,
    test3 = static_check< some_type< result_list3, check_list3>::value >::value,
    test3t = static_check< some_type< result_list3t, check_list3>::value >::value,
    test3tm = static_check< some_type< result_list3tm, check_list3>::value >::value,
    test3mp = static_check< some_type< result_list3mp, check_list3>::value >::value,

  };
  return 0;
}


