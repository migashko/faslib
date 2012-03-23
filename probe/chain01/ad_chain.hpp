#ifndef CHAIN_AD_CHAIN_HPP
#define CHAIN_AD_CHAIN_HPP

#include <iostream>

template<char C, int I, typename Tg>
struct ad_chain
{
  template<typename T, typename P>
  void operator()(T& t, P p)
  {
    std::cout<<"Chain"<<C<<I<<"->";
    
    t.get_aspect().template get<Tg>()(t, p);
    t.get_aspect().template get<Tg>()(t, p);
    t.get_aspect().template get<Tg>()(t, p);
    t.get_aspect().template get<Tg>()(t, p);
    t.get_aspect().template get<Tg>()(t, p);
    t.get_aspect().template get<Tg>()(t, p);
  }
};

#endif
