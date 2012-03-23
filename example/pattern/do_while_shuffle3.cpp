#include "foo.hpp"
#include "show.hpp"
#include <fas/algorithm/do_while.hpp>
#include <fas/algorithm/random_shuffle.hpp>
#include <fas/type_list/type_list_n.hpp>
#include <fas/type_list/intrinsic.hpp>
#include <fas/typemanip/wrapper.hpp>
#include <fas/typemanip/wrap.hpp>
#include <fas/integral/less_equal.hpp>
#include <fas/integral/inc.hpp>
#include <fas/integral/factorial.hpp>
//#include <fas/utility.hpp>
#include <fas/typemanip/if_.hpp>


using namespace ::fas;

typedef type_list_n<
  foo1, foo2, foo3/*, foo4*/
>::type list_type;


struct list: list_type {};


template<typename I, typename L, typename LL>
struct push_back_shuffle
{
  typedef typename push_back<
        wrapper< typename random_shuffle< I, L >::type >,
        LL
  >::type type1;
  typedef typename unique<type1>::type type;
};

template<typename L, typename I = int_<0> >
struct generate_shuffle
{
  enum { list_length = factorial< int_<length<L>::value> >::value };
  typedef pair< I, empty_list > initial;
  typedef less< length< second< _1> >, int_<list_length> >  cond;

  typedef do_while<
    initial,
    pair<
      inc< first<_1> >,
      push_back_shuffle< first<_1>, L, second< _1> >
    >,
    cond
  > do_while_type;
    
  typedef typename second<typename do_while_type::type>::type type;
};




int main()
{
  typedef generate_shuffle<list>::type result;
  show<result>();
  
  //static_check< apply<factorial< length<list> > >::type::value == 6 > check;
  /*
  typedef pair< 
      pair<
        if_<
          some_type<_2, empty_type >,
          int_<0>,
          _2
        >,
        _1
      >,
      el
  > initial;
  
  typedef less< length< second< p<_1> > >, factorial< length<_1> > >  cond;
  typedef pair<
    pair<
      inc< first< first< p<_1> > > >,
      _1
    >,
    unique<
      push_back<
        wrap<
          random_shuffle< first< first< p<_1> > >, second< first< p<_1> > > >
        >,
        second< p<_1> >
      >
    >
  > doit;

  //typedef do_while<initial, a<doit>, a<cond> >::type::second result;
  typedef do_while<initial, a<doit>, a<cond> > do_while_shuffle;
  typedef apply< do_while_shuffle, list >::type::second result;
  show<result>();
  
  std::cout << "-------------------" << std::endl;
  typedef apply< do_while_shuffle, list, int_<33> >::type::second result2;
  show<result2>();
  */
  
  /*
  std::cout << "-----++++++-----" << std::endl;
  show< shuffle<int_<0>, list >::type >();
  show< shuffle<int_<1>, list >::type >();
  show< shuffle<int_<2>, list >::type >();
  show< shuffle<int_<3>, list >::type >();
  show< shuffle<int_<4>, list >::type >();
  show< shuffle<int_<5>, list >::type >();
  show< shuffle<int_<6>, list >::type >();
  show< shuffle<int_<7>, list >::type >();
  show< shuffle<int_<8>, list >::type >();
  show< shuffle<int_<9>, list >::type >();
  show< shuffle<int_<10>, list >::type >();
  */
  /*show<foo1>();
  show<list>();
  show< shuffle<int_<0>,list>::type >();
  show< shuffle<int_<1>,list>::type >();
  show< shuffle<int_<2>,list>::type >();
        */
  return 0;
}
