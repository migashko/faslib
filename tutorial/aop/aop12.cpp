#include <fas/aop.hpp>
#include <fas/type_list.hpp>

#include <iostream>

struct _one_;
struct _two_;
struct _three_;
struct _strike_;
struct _say_;

struct _before_say_;
struct _after_say_;


struct say_one
{
  template<typename T>
  void operator()(T&) const {  std::cout<<"one, "; }
};

struct say_two
{
  template<typename T>
  void operator()(T&) const {  std::cout<<"two, "; }
};

struct say_three
{
  template<typename T>
  void operator()(T&) const {  std::cout<<"three, "; }
};

struct say_strike
{
  template<typename T>
  void operator()(T&) const {  std::cout<<"strike!"; }
};

struct say_123s
{
  template<typename T>
  void operator()(T& t) const
  {
    t.get_aspect().template getg<_before_say_>()(t);

    t.get_aspect().template get<_one_>()(t);
    t.get_aspect().template get<_two_>()(t);
    t.get_aspect().template get<_three_>()(t);
    t.get_aspect().template get<_strike_>()(t);

    t.get_aspect().template getg<_after_say_>()(t);
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
  public fas::aspect_class< typename fas::merge_aspect<A, aspect_123s>::type >
{
  // ...
public:
  void dredd_say() const
  {
    this->get_aspect().template get<_say_>()(*this);
  }
};

/// /////////////////////////////////////////////////

struct left_bracket
{
  template<typename T>
  void operator()(T&) const { std::cout<<"["; }
};

struct right_bracket
{
  template<typename T>
  void operator()(T&) const { std::cout<<"]"; }
};

struct _before1_;
struct _before2_;

struct _after1_;
struct _after2_;

struct aspect_in_brackets: fas::aspect< fas::type_list_n<
  fas::advice<_before1_, left_bracket >,
  fas::advice<_before2_, left_bracket >,
  fas::advice<_after1_, right_bracket >,
  fas::advice<_after2_, right_bracket >,
  fas::group<_before_say_, fas::type_list_n<_before1_, _before2_>::type >,
  fas::group<_after_say_, _after1_>,
  fas::group<_after_say_, _after2_>
>::type > {};

int main()
{
  dredd<aspect_in_brackets> d;
  std::cout << "Dredd: ";
  d.dredd_say();
  std::cout << std::endl;
  return 0;
}
