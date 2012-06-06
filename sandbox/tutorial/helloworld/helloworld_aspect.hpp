#ifndef HELLO_WORLD_ASPECT_HPP
#define HELLO_WORLD_ASPECT_HPP

#include <fas/type_list/type_list_n.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/advice.hpp>

#include <iostream>

using namespace ::fas;

struct _hello_;
struct _world_;

struct ad_hello
{
  template<typename T>
  void operator()(T&)
  {
    std::cout<<"hello";
  }
};

struct ad_world
{
  template<typename T>
  void operator()(T&)
  {
    std::cout<<" world!"<<std::endl;
  }
};

typedef advice< _hello_, ad_hello> hello_advice;
typedef advice< _world_, ad_world> world_advice;

typedef type_list_n<
      hello_advice,
      world_advice
    >::type helloworld_advice_list;

typedef aspect<helloworld_advice_list> helloworld_aspect;

#endif
