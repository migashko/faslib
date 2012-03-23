#ifndef HELLO_WORLD2_ASPECT_HPP
#define HELLO_WORLD2_ASPECT_HPP

#include "helloworld_aspect.hpp"

struct ad_World
{
  template<typename T>
  void operator()(T&)
  {
    std::cout<<" World!"<<std::endl;
  }
};

/*
struct World_advice: advice<_world_, ad_World> {};

typedef type_list_n<
    World_advice
>::type helloworld2_advice_list;*/

struct helloworld2_aspect: aspect< /*helloworld2_advice_list*/ advice<_world_, ad_World>  > {};

#endif
