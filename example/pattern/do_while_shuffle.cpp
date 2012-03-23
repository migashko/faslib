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
//#include <fas/utility.hpp>


using namespace ::fas;

typedef type_list_n<
  foo1, foo2, foo3/*, foo4*//*, foo5,
  foo7, foo8, foo9, foo10, foo11*/
>::type list_type;



typedef list_type list;

//struct list: list_type {};
//struct list: merge<list_type, type_list<wrap<list_type>::type> >::type {};


int main()
{
  
  typedef pair< pair<int_<0>, list>, empty_list> initial;
  typedef less< length< second<_1> >, int_<1*2*3/**4*/> >  cond;
  typedef pair<
    pair<
      inc< first< first<_1> > >,
      list
    >,
    unique<
      push_back<
        wrap<
          random_shuffle< first< first<_1> >, second< first<_1> > >
        >,
        second<_1>
      >
    >
  > doit;

  
  typedef do_while<initial, doit, cond>::type::second result;
  show<result>();
  /*show<foo1>();
  show<list>();
  show< shuffle<int_<0>,list>::type >();
  show< shuffle<int_<1>,list>::type >();
  show< shuffle<int_<2>,list>::type >();
        */
  return 0;
}
