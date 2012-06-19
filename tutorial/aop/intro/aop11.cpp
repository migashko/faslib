#include <fas/aop.hpp>
#include <fas/type_list.hpp>

#include <iostream>

struct _one_;
struct _two_;
struct _three_;
struct _strike_;
struct _say_;

struct say_one
{
  template<typename T>
  void operator()(T&) {  std::cout<<"one, "; };
};

struct say_two
{
  template<typename T>
  void operator()(T&) {  std::cout<<"two, "; }
};

struct say_three
{
  template<typename T>
  void operator()(T&) {  std::cout<<"three, "; }
};

struct say_strike
{
  template<typename T>
  void operator()(T&) {  std::cout<<"strike!"; }
};


namespace foo {
  
struct _foo1_;
struct _foo2_;
struct _foo3_;
struct _foo4_;
  
struct foo1234
{
  template<typename T>
  void operator()(T& t)
  {
    t.get_aspect().template get<_foo1_>()(t);
    t.get_aspect().template get<_foo2_>()(t);
    t.get_aspect().template get<_foo3_>()(t);
    t.get_aspect().template get<_foo4_>()(t);
  }
};
}

struct aspect_123s: fas::aspect< fas::type_list_n<
  fas::advice<_one_, say_one>,
  fas::advice<_two_, say_two>,
  fas::advice<_three_, say_three>,
  fas::advice<_strike_, say_strike>,
  fas::advice<_say_, foo::foo1234>,
  fas::alias<foo::_foo1_, _one_>,
  fas::alias<foo::_foo2_, _two_>,
  fas::alias<foo::_foo3_, _three_>,
  fas::alias<foo::_foo4_, _strike_>
>::type >
{};

template< typename A = fas::aspect<> >
class dredd:
  public fas::aspect_class<A, aspect_123s>
{
  // ...
public:
  void dredd_say()
  {
    this->get_aspect().template get<_say_>()(*this);
  }
};

/// /////////////////////////////////////////////////

struct say_ONE
{
  template<typename T>
  void operator()(T&) {  std::cout<<"ONE, "; };
};

struct aspect_ONE: fas::aspect< fas::advice<_one_, say_ONE > > {};

int main()
{
  dredd< aspect_ONE > d;
  std::cout << "Dredd: ";
  d.dredd_say();
  std::cout << std::endl;
  return 0;
}
