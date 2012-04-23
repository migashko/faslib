#include <fas/static_check/static_check.hpp>

#include <fas/typemanip/if_c.hpp>

using namespace ::fas;

struct foo_noerror;
struct foo_param_is_less_zero;
struct foo_param_is_zero;

template<int I>
struct check_foo
{
  typedef typename if_c<
      (I > 0),
      foo_noerror,
      typename if_c<
        (I == 0),
        foo_param_is_zero,
        foo_param_is_less_zero
      >::type
  >::type error;

  enum {value = (I > 0) };
};


template<int I>
struct foo_impl
{
  enum { value = 100 / I };
  int initial;
  foo_impl(): initial(I){}
};

template<int I>
struct foo: /*verifying <*/ foo_impl<I>/*, check_foo< I > >::type*/ {};


int main()
{
  typedef foo<1> foo1;
  typedef foo<2> foo2;
  typedef foo<-1> foo3;
  typedef foo<0> foo4;

  foo<4> foo5obj;
  // foo<-2> foo6obj; // invalid use of incomplete type 'struct foo_param_is_less_zero'
  // foo<0> foo7obj; // error: invalid use of incomplete type 'struct foo_param_is_zero'

  enum {
    test1 = static_check< foo1::value == 100 >::value,
    test2 = static_check< foo2::value == 50 >::value,
    // test3 = static_check< foo3::value == -100 >::value, // invalid use of incomplete type 'struct foo_param_is_less_zero'
    // test4 = static_check< foo4::value == -0 >::value, // error: invalid use of incomplete type 'struct foo_param_is_zero'
  };
  return !(foo5obj.initial == 4);
}
