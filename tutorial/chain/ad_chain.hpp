#ifndef CHAIN_AD_CHAIN_HPP
#define CHAIN_AD_CHAIN_HPP

#include <iostream>
#include <cmath>

struct ichain
{
  virtual void vmethod1(int i) = 0;
  virtual void vmethodn(int i) = 0;
};

template<char C, int I, typename Tg>
struct ad_chain
  : ichain
{
  int v;
  double v2;
  ad_chain():v(0), v2(0),next(0){}
  
  void show()
  {
    std::cout<<"Chain"<<C<<I<<std::endl;
  }

  template<typename T>
  void operator()(T)
  {
    show();
  }

  template<typename T, typename V>
  void operator()(T t, V v)
  {
    std::cout<<"Chain"<<C<<I<<"->";
    t->get_aspect().template get<Tg>()(t, v);
    t->inc_count();
  }

  template<typename T, typename V>
  void operator()(T t, V p, V)
  {
    this->v2 = std::cos(double(p));
    t->get_aspect().template get<Tg>()(t, p+1, 0);
  }

  template<typename T, typename V>
  void operator() (T& t, V p, V, V)
  {
    //std::cout << C << int(I) << std::endl;
    this->v2 = std::cos(double(p));
    //for (int i = 0 ; i < 3; i++)
      t->get_aspect().template get<Tg>()(t, p+1, 0, 0);
    //t.get_aspect().template get<Tg>()(t, v+1, 0, 0);
    /*t.get_aspect().template get<Tg>()(t, v+1, 0, 0);
    t.get_aspect().template get<Tg>()(t, v+1, 0, 0);
    t.get_aspect().template get<Tg>()(t, v+1, 0, 0);*/
  }

  ichain* next;

  virtual void vmethod1(int i)
  {
    this->v = (int)std::cos(double(i));
    if (next)
      next->vmethod1(i+1);
  }

  virtual void vmethodn(int i)
  {
    this->v = (int)std::cos(double(i) );
    if (next)
    {
      for (int i = 0 ; i < 10; i++)
        next->vmethod1(i+1);
    }
  }
};

#endif
