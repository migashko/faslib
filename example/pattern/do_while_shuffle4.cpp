#include "foo.hpp"
#include "show.hpp"
#include <fas/algorithm/do_while.hpp>
#include <fas/algorithm/random_shuffle.hpp>
#include <fas/type_list/type_list_n.hpp>
#include <fas/type_list/intrinsic.hpp>
#include <fas/typemanip/wrapper.hpp>
#include <fas/typemanip/wrap.hpp>
#include <fas/typemanip/tuple.hpp>
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

int main()
{
  typedef tuple<
      if_< some_type<_2, empty_type >, int_<0>, _2>,
      _1,
      empty_list
  > initial;

  typedef less< length< third< p<_1> > >, factorial< length<_1> > >  cond;

  typedef tuple<
    inc< first< p<_1> > >,
    _1,
    unique<
      push_back<
        wrap<
          random_shuffle< first< p<_1> >, second< p<_1> > >
        >,
        third< p<_1> >
      >
    >
  > doit;

  typedef do_while<initial, a<doit>, a<cond> > do_while_shuffle;
  typedef apply< do_while_shuffle, list_type >::type::third result;
  show<result>();

  return 0;
}
