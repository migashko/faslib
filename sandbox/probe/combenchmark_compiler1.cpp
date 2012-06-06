#include <fas/type_list.hpp>
//#include <fas/type_list_n.hpp>
#include <fas/type_traits.hpp>
#include <fas/utility.hpp>
#include <fas/algorithm.hpp>
#include <fas/type_list_intrinsic.hpp>

using namespace ::fas;

namespace very_megalong_namespace{
  namespace very_megalong_namespace{
    namespace very_megalong_namespace{
      namespace very_megalong_namespace{
        namespace very_megalong_namespace{

          template< typename L, typename R >
          struct type_list1;
          
          struct empty_list1 { typedef metalist::empty_list metatype;
          typedef empty_list1 final_type;
            template<typename LL, typename RR>
            struct rebind
            {
              typedef type_list1<LL, RR> type;
            };
          };

          template< typename L, typename R >
          struct type_list1
          {
            typedef metalist::type_list metatype;
            typedef L left_type;
            typedef R right_type;
            typedef empty_list1 final_type;
            template<typename LL=L, typename RR=R>
            struct rebind
            {
              typedef type_list1<LL, RR> type;
            };
          };
        }
      }
    }
  }
}

template< template<typename, typename> class tl, typename el >
struct gen
{
  typedef 
  tl< int_<6>,
  tl< int_<7>,
  tl< int_<5>, 
  tl< int_<3>, 
  tl< int_<7>,
  tl< int_<2>,
  tl< int_<1>,
  tl< int_<8>,
  tl< int_<0>,
  tl< int_<9>, el
    > > > > > > > > > > type;
};

namespace v = very_megalong_namespace::very_megalong_namespace::very_megalong_namespace::very_megalong_namespace::very_megalong_namespace;

typedef gen<v::type_list1, v::empty_list1>::type list;
typedef apply< 
  sort< 
  reverse<
    sort< 
      generate< 
        int_<3/*0*/>,
        a< generator< int_<0>, rand< p<_1> > > > ,
        v::empty_list1
      >, 
      a< less< p<_1>, p<_2> > >
    >
  >,
  a< less< p<_1>, p<_2> > >
  >
>::type result;

int main()
{
  
  return length<result>::value;
};
