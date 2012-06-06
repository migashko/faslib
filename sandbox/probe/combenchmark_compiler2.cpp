#include <fas/type_list.hpp>
//#include <fas/type_list_n.hpp>
#include <fas/type_traits.hpp>
#include <fas/utility.hpp>
#include <fas/algorithm.hpp>
#include <fas/type_list_intrinsic.hpp>

using namespace ::fas;

namespace vm{

          template< typename L, typename R >
          struct tl;
          struct el { typedef metalist::empty_list metatype;
                      typedef el final_type;
            template<typename LL, typename RR>
            struct rebind
            {
              typedef tl<LL, RR> type;
            };

          };

          template< typename L, typename R >
          struct tl
          {
            typedef metalist::type_list metatype;
            typedef L left_type;
            typedef R right_type;
            typedef el final_type;
            template<typename LL=L, typename RR=R>
            struct rebind
            {
              typedef tl<LL, RR> type;
            };
          };
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

namespace v = vm;

typedef gen<v::tl, v::el>::type list;
typedef apply< 
  sort< 
  reverse<
    sort< 
      generate< 
        int_<3/*0*/>,
        a< generator< int_<0>, rand< p<_1> > > > ,
        v::el
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




/*
template<typename L1, typename L2, bool B>
struct aaa_helper
{
  typedef 
};

template<typename L1, typename L2>
struct aaa_helper<L1, L2, false>
{
};




template<typename L1, typename L2>
struct aaa
{
  typedef typename aaa_helper<L1, L2, some_type<L1::left_type, L2::left_type>::value >::type type;
};


template<int Offset, typename D, typename S, typename F, typename Q1, typename Q2,  L1,  L2>
static inline int _to_searchcontext_basic(D &d, const S &s, const ap::type_list<F, Q1> &, const ap::type_list<F, Q2> &) {


template<int Offset, typename D, typename S, ap::type_list<typename F1, typename Q1> L1, typename L2>
static inline int _to_searchcontext_basic(D &d, const S &s, const L1 &, const L2 &) {



*/











