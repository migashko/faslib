#ifndef HELLO_WORLD4_ASPECT_HPP
#define HELLO_WORLD4_ASPECT_HPP

#include "helloworld3_aspect.hpp"
#include <fas/aop/alias.hpp>

struct _mega_;
struct _mega_next_;

struct ad_Mega
{
  template<typename T>
  void operator()(T& t)
  {
    std::cout<<" Mega";
    t.get_aspect().template get<_mega_next_>()(t);
  }
};

//struct Mega_advice: fas::advice<_mega_, ad_Mega> {};


typedef fas::type_list_n<
    fas::alias<_super_, _mega_>,
    fas::advice<_mega_, ad_Mega>,
    fas::alias<_mega_next_, _super_>
>::type helloworld4_advice_list;

struct helloworld4_aspect_: fas::aspect< helloworld4_advice_list > {};

struct helloworld4_aspect: fas::aspect_merge<helloworld4_aspect_, helloworld3_aspect>::type {};


#endif
