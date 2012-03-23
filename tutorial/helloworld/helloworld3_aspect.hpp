#ifndef HELLO_WORLD3_ASPECT_HPP
#define HELLO_WORLD3_ASPECT_HPP

#include "helloworld_aspect.hpp"

struct _super_;

struct ad_Hello
{
  template<typename T>
  void operator()(T& t)
  {
    std::cout<<"Hello";
    t.get_aspect().template get<_super_>()(t);
  }
};

struct ad_Super
{
  template<typename T>
  void operator()(T&)
  {
    std::cout<<" Super";
  }
};

struct Hello_advice: advice<_hello_, ad_Hello> {};
struct Super_advice: advice<_super_, ad_Super> {};

typedef type_list_n<
    Hello_advice,
    Super_advice
>::type helloworld3_advice_list;

struct helloworld3_aspect: aspect< helloworld3_advice_list > {};

#endif
