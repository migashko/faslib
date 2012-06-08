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

struct say
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

struct aspect_dredd: fas::aspect< fas::type_list_n<
  fas::advice<_one_, say_one>,
  fas::advice<_two_, say_two>,
  fas::advice<_three_, say_three>,
  fas::advice<_strike_, say_strike>,
  fas::advice<_say_, say>
>::type >
{};

template< typename A = fas::aspect<> >
class judge_dredd:
  public fas::aspect_class<A, aspect_dredd>
{
public:
  void say()
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

struct aspect_jon: fas::aspect< fas::type_list_n<
  fas::advice<_one_, say_ONE>,
  aspect_dredd
>::type >
{};

/// /////////////////////////////////////////////////

struct _three1_;
struct _three2_;
struct _three3_;

struct say_three1
{
  template<typename T>
  void operator()(T&) {  std::cout<<"three and 0.5, "; }
};

struct say_three2
{
  template<typename T>
  void operator()(T&) {  std::cout<<"three and 0.75, "; }
};

struct say_three3
{
  template<typename T>
  void operator()(T&) {  std::cout<<"three and 0.99, "; }
};

struct say_soft_three
{
  template<typename T>
  void operator()(T& t)
  {
    std::cout<<"three, ";
    t.get_aspect().template get<_three1_>()(t);
    t.get_aspect().template get<_three2_>()(t);
    t.get_aspect().template get<_three3_>()(t);
  }
};

struct aspect_three: fas::aspect< fas::type_list_n<
  fas::advice<_three1_, say_three1>,
  fas::advice<_three2_, say_three2>,
  fas::advice<_three3_, say_three3>,
  fas::advice<_three_, say_soft_three >
>::type >
{};

struct aspect_bob: fas::aspect< fas::type_list_n<
  aspect_three,
  aspect_dredd
>::type >
{};

struct aspect_sam: fas::aspect< fas::type_list_n<
  fas::advice<_one_, say_ONE>,
  aspect_three,
  aspect_dredd
>::type >
{};

int main()
{
  judge_dredd<> dredd;
  std::cout << "Dredd: ";
  dredd.say();
  std::cout << std::endl;

  judge_dredd<aspect_jon> jon;
  std::cout << "Jon: ";
  jon.say();
  std::cout << std::endl;

  judge_dredd<aspect_bob> bob;
  std::cout << "Bob: ";
  bob.say();
  std::cout << std::endl;

  judge_dredd<aspect_sam> sam;
  std::cout << "Sam: ";
  sam.say();
  std::cout << std::endl;
  return 0;
}
