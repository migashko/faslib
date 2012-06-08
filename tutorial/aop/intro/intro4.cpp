#include <fas/aop.hpp>
#include <fas/type_list.hpp>
#include <iostream>

struct say_one
{
  void one() {  std::cout<<"one, "; };
};

struct say_two
{
  void two() {  std::cout<<"two, "; }
};

struct say_three
{
  void three() {  std::cout<<"three, "; }
};

struct say_strike
{
  void strike() {  std::cout<<"strike!"; }
};

struct _one_;
struct _two_;
struct _three_;
struct _strike_;

struct aspect_dredd: fas::aspect< fas::type_list_n<
  fas::advice<_one_, say_one>,
  fas::advice<_two_, say_two>,
  fas::advice<_three_, say_three>,
  fas::advice<_strike_, say_strike>
>::type >
{};


template< typename A = fas::aspect<> >
class judge_dredd:
  public fas::aspect_class<A, aspect_dredd>
{
public:
  void say()
  {
    this->get_aspect().template get<_one_>().one();
    this->get_aspect().template get<_two_>().two();
    this->get_aspect().template get<_three_>().three();
    this->get_aspect().template get<_strike_>().strike();
  }
};

/// /////////////////////////////////////////////////

struct say_ONE
{
  void one() {  std::cout<<"ONE, "; };
};

struct aspect_jon: fas::aspect< fas::type_list_n<
  fas::advice<_one_, say_ONE>
>::type >
{};


/// /////////////////////////////////////////////////

struct say_three1
{
  void three1() {  std::cout<<"three and 0.5, "; }
};

struct say_three2
{
  void three2() {  std::cout<<"three and 0.75, "; }
};

struct say_three3
{
  void three3() {  std::cout<<"three and 0.99, "; }
};

struct _three1_;
struct _three2_;
struct _three3_;

struct aspect_three: fas::aspect< fas::type_list_n<
  fas::advice<_three1_, say_three1>,
  fas::advice<_three2_, say_three2>,
  fas::advice<_three3_, say_three3>
>::type >
{};


template< typename A = fas::aspect<> >
class say_soft_three:
  public fas::aspect_class<A, aspect_three>
{
public:
  void three()
  {
    std::cout<<"three, ";
    this->say();
  }
  void say()
  {
    this->get_aspect().template get<_three1_>().three1();
    this->get_aspect().template get<_three2_>().three2();
    this->get_aspect().template get<_three3_>().three3();
  }
};

struct aspect_bob: fas::aspect< fas::type_list_n<
  fas::advice<_three_, say_soft_three<> >
>::type >
{};


struct aspect_sam:
  fas::aspect_merge< aspect_jon, aspect_bob >::type 
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
