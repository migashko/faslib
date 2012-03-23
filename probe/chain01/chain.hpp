#ifndef CHAIN_CHAIN_HPP
#define CHAIN_CHAIN_HPP

#include <fas/aop/aspect.hpp>
#include "chain_a.hpp"

namespace aa = ::fas::aop;
namespace ap = ::fas::pattern;

template<typename A = fas::aspect<> >
class chain
  : public fas::aspect_class<chain_a::aspect, A >
{
  typedef fas::aspect_class<chain_a::aspect, A> super;
public:
  template<typename V>
  void doit(V v )
  {
    super::get_aspect().template get<chain_a::_input_>()(*this, v);
    std::cout<<std::endl;
  }

};

#endif
