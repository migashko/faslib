#ifndef CHAIN_CHAIN_HPP
#define CHAIN_CHAIN_HPP

#include <fas/aop/aspect_class.hpp>
#include "chain_a.hpp"


template<typename A = fas::aspect<> >
class chain
  : public fas::aspect_class<A, chain_a::aspect>
{
  typedef fas::aspect_class<A, chain_a::aspect> super;
public:
  template<typename V>
  void doit(V v )
  {
    super::get_aspect().template get<chain_a::_input_>()(this, v);
    std::cout<<std::endl;
  }

  void method1(int v)
  {
    super::get_aspect().template get<chain_a::_input_>()(this, v, v);
  }

  void methodn(int v)
  {
    super::get_aspect().template get<chain_a::_input_>()(this, v, v, v);
  }

  void inc_count()
  {
  }
};

#endif
