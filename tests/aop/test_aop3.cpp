//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/alias.hpp>
#include <fas/aop/has_tag.hpp>
#include <fas/aop/private/aspect_select.hpp>
#include <fas/aop/aspect_class.hpp>

#include <fas/type_list.hpp>
#include <fas/integral/int_.hpp>
#include <fas/static_check/static_check.hpp>
#include <fas/algorithm/find_if.hpp>
#include <fas/typemanip/type2type.hpp>
#include <iostream>

using namespace fas;


struct _tag1_;
struct _tag2_;
struct _tag3_;

struct ad_advice1
{
  template<typename T>
  int operator()(T& t, int value)
  {
    std::cout << "ad_advice1" << std::endl;
    t.private_method();
    return t.get_aspect().template get<_tag2_>()(t, value) + 1;
  }
};

struct ad_advice2
{
  template<typename T>
  int operator()(T&, int value)
  {
    std::cout << "ad_advice2" << std::endl;
    return value*2;
  }
};

struct advice1_advice: advice<_tag1_, ad_advice1> {};
struct advice2_advice: advice<_tag2_, ad_advice2> {};

struct advice_list1: type_list_n<advice1_advice, advice2_advice>::type {};
struct aspect1: aspect<advice_list1> {};

template<typename A = aspect<> >
class test
  : public aspect_class<A, aspect1>
{
  typedef aspect_class<A, aspect1> super;
public:
  int method(int v)
  {
    return this->get_aspect().template get<_tag1_>()(*this, v);
  };
#ifdef __GXX_EXPERIMENTAL_CXX0X__
private:

  friend class super::aspect::template advice_cast< _tag1_ >::type;
#endif

  void private_method()
  {

  };
};

///
struct ad_advice3
{
  template<typename T>
  int operator()(T& t, int value)
  {
    std::cout << "ad_advice3" << std::endl;
    return t.get_aspect().template get<_tag3_>()(t, value) * 3;
  }
};

struct advice3_advice: advice<_tag2_, ad_advice3> {};

struct advice_list2: type_list_n<
    advice3_advice,
    forward<_tag3_, _tag2_>
>::type {};

struct aspect2: aspect<advice_list2> {};

int main()
{
  test<> t;
  std::cout << t.method(2) << std::endl;
  if (t.method(2) != 5 ) return 1;
  test<aspect2> t2;
  std::cout << t2.method(2) << std::endl;
  return 0;
}


