
#include <fas/type_list/type_list.hpp>
//#include <fas/type_list/empty_list.hpp>
#include <fas/static_check.hpp>
#include <fas/type_list/type_at.hpp>

#include <string>

using namespace ::fas;

struct A{};
struct B:A{};
struct C{};
struct D:C{};

struct abc_list: type_list<A, type_list<B, type_list<C, type_list<D> > > > {};

int main()
{
  
  enum {
    test1 = static_check< some_type<A, type_at< int_<0>, abc_list>::type >::value >::value,
    test2 = static_check< some_type<B, type_at< int_<1>, abc_list>::type >::value >::value,
    test3 = static_check< some_type<C, type_at< int_<2>, abc_list>::type >::value >::value,
    test4 = static_check< some_type<D, type_at< int_<3>, abc_list>::type >::value >::value,
/*#warning сделать static out_of_range если даже не определен FASLIB_TYPE_LIST_CHECK
  -- сделанно !  
    test5 = static_check< some_type<D, type_at< int_<5>, abc_list >::type >::value >::value,
    test6 = static_check< some_type<D, type_at< int_<-1>, abc_list >::type >::value >::value,
    */
    
  };
  return 0;
}


