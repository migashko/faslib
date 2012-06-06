#ifndef FASLIB_EXAMPLE_FOO_HPP
#define FASLIB_EXAMPLE_FOO_HPP

//#define TOSTR(P) '"'##P##'"'
//#define MERGE_STR(P1, P2) P1 ## '"'P2'"'

template<int V>
struct fooT
{
  enum { foo_value = V };
  const char* name() const { return "foo";}
  int value() const { return foo_value;}
};

struct foo1: fooT<1> {};
struct foo2: fooT<2> {};
struct foo3: fooT<3> {};
struct foo4: fooT<4> {};
struct foo5: fooT<5> {};
struct foo6: fooT<6> {};
struct foo7: fooT<7> {};
struct foo8: fooT<8> {};
struct foo9: fooT<9> {};
struct foo10: fooT<10> {};
struct foo11: fooT<11> {};

#endif
