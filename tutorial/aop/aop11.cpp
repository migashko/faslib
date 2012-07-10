#include <fas/aop.hpp>
#include <fas/type_list.hpp>

#include <iostream>

namespace dredd {

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

struct say_123s
{
  template<typename T>
  void operator()(T& t)
  {
    t.get_aspect().template get<_one_>()(t);
    t.get_aspect().template get<_two_>()(t);
    t.get_aspect().template get<_three_>()(t);
    t.get_aspect().template get<_strike_>()(t);
  }
};

struct aspect_123s: fas::aspect< fas::type_list_n<
  fas::advice<_one_, say_one>,
  fas::advice<_two_, say_two>,
  fas::advice<_three_, say_three>,
  fas::advice<_strike_, say_strike>,
  fas::advice<_say_, say_123s>
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

} // namespace dredd

/// /////////////////////////////////////////////////

namespace jon {

struct _one_;
struct _say_;

struct say_ONE
{
  template<typename T>
  void operator()(T&) {  std::cout<<"ONE, "; };
};


struct aspect_ONE: fas::aspect< fas::type_list_n<
  fas::advice< _one_, say_ONE>,
  fas::alias< dredd::_one_, _one_ >,
  fas::alias< _say_, dredd::_say_ >
>::type > {};

struct aspect_ONE23s:
  fas::aspect_merge<aspect_ONE, dredd::aspect_123s >::type
{};

template< typename A = fas::aspect<> >
class jon:
  public fas::aspect_class<A, aspect_ONE23s >
{
  // ...
public:
  void jon_say()
  {
    this->get_aspect().template get< _say_ >()(*this);
  }
};

} // namespace jon

/// /////////////////////////////////////////////////

namespace bob {

struct _say_;
struct _say123_;

struct _four_;
struct _five_;
struct _six_;
struct _seven_;


struct say_four
{
  template<typename T>
  void operator()(T&) {  std::cout<<"four, "; }
};

struct say_five
{
  template<typename T>
  void operator()(T&) {  std::cout<<"five, "; }
};

struct say_six
{
  template<typename T>
  void operator()(T&) {  std::cout<<"six, "; }
};

struct say_seven
{
  template<typename T>
  void operator()(T&) {  std::cout<<"seven!"; }
};

struct say_1234567
{
  template<typename T>
  void operator()(T& t)
  {
    t.get_aspect().template get<_say123_>()(t);
    t.get_aspect().template get<_four_>()(t);
    t.get_aspect().template get<_five_>()(t);
    t.get_aspect().template get<_six_>()(t);
    t.get_aspect().template get<_seven_>()(t);
  }
};

struct aspect_4567: fas::aspect< fas::type_list_n<
  fas::stub<dredd::_strike_>,
  fas::advice<_four_,  say_four>,
  fas::advice<_five_,  say_five>,
  fas::advice<_six_,   say_six>,
  fas::advice<_seven_, say_seven>,
  fas::advice<_say_,   say_1234567>,
  fas::forward<_say123_, dredd::_say_>
>::type >
{};


struct aspect_1234567:
  fas::aspect_merge< aspect_4567, dredd::aspect_123s>::type
{};

/// /////////////////////////////////////////////////

template< typename A = fas::aspect<> >
class bob:
  public fas::aspect_class<A, aspect_1234567 >
{
  // ...
public:
  void bob_say()
  {
    this->get_aspect().template get<_say_>()(*this);
  }
};

} // namespace bob

/// /////////////////////////////////////////////////

namespace sam
{

struct _say_;

struct aspect_ONE234567:
  fas::aspect_merge<
    fas::aspect< fas::alias<_say_, bob::_say_> >,
    jon::aspect_ONE,
    bob::aspect_1234567
  >::type
{};

template< typename A = fas::aspect<> >
class sam:
  public fas::aspect_class<A, aspect_ONE234567 >
{
public:
  void sam_say()
  {
    this->get_aspect().template get<_say_>()(*this);
  }
};

} //namespace sam

int main()
{
  dredd::dredd<> d;
  std::cout << "Dredd: ";
  d.dredd_say();
  std::cout << std::endl;

  jon::jon<> j;
  std::cout << "Jon: ";
  j.jon_say();
  std::cout << std::endl;

  bob::bob<> b;
  std::cout << "Bob: ";
  b.bob_say();
  std::cout << std::endl;

  sam::sam<> s;
  std::cout << "Sam: ";
  s.sam_say();
  std::cout << std::endl;

  std::cout << "sizeof(d): " << sizeof(d) << std::endl;
  std::cout << "sizeof(j): " << sizeof(j) << std::endl;
  std::cout << "sizeof(b): " << sizeof(b) << std::endl;
  std::cout << "sizeof(s): " << sizeof(s) << std::endl;
  return 0;
}
