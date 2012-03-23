#ifndef HELLO_WORLD_HPP
#define HELLO_WORLD_HPP

#include "helloworld_aspect.hpp"
#include <fas/aop/aspect_class.hpp>

using namespace ::fas;

template<typename A = aspect<> >
class helloworld
  : public aspect_class< A, helloworld_aspect>
{
  typedef aspect_class< A, helloworld_aspect> super;
public:
  void say()
  {
    super::get_aspect().template get<_hello_>()(*this);
    super::get_aspect().template get<_world_>()(*this);
  }
};

#endif
