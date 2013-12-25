#include <iostream>
#include <fas/aop.hpp>

class foo1
{
public:
  void method1() { std::cout << "method-1.1" << std::endl; }
  void method2() { std::cout << "method-1.2" << std::endl; }
  void method3() { std::cout << "method-1.3" << std::endl; }
};

/// /////////////////////////////////////////////////////

struct _method1_;
struct _method2_;
struct _method3_;

struct ad_method1
{
  template<typename T>
  void operator()(T&) { std::cout << "method-2.1" << std::endl; }
};

struct ad_method2
{
  template<typename T>
  void operator()(T&) { std::cout << "method-2.2" << std::endl; }
};

struct ad_method3
{
  template<typename T>
  void operator()(T&) { std::cout << "method-2.3" << std::endl; }
};

typedef fas::advice<_method1_, ad_method1> method1_advice;
typedef fas::advice<_method2_, ad_method2> method2_advice;
typedef fas::advice<_method3_, ad_method3> method3_advice;

typedef fas::type_list_n<
  method1_advice,
  method2_advice,
  method3_advice
>::type advice_list;

struct foo2_aspect: fas::aspect< advice_list >{};

  template<typename A = fas::aspect<> >
  class foo2
    : public fas::aspect_class< typename fas::merge_aspect<A, foo2_aspect>::type >
  {
  public:
    void method1() { this->get_aspect().template get<_method1_>()(*this); }
    void method2() { this->get_aspect().template get<_method2_>()(*this); }
    void method3() { this->get_aspect().template get<_method3_>()(*this); }

  };

/// /////////////////////////////////////////////////////

struct ad_method3_2
{
  template<typename T>
  void operator()(T&) { std::cout << "method-3.2" << std::endl; }
};

struct ad_method3_3
{
  template<typename T>
  void operator()(T&) { std::cout << "method-3.3" << std::endl; }
};

struct foo3_aspect: fas::aspect< fas::type_list_n<
  fas::advice<_method2_, ad_method3_2>,
  fas::advice<_method3_, ad_method3_3>
>::type >{};



int main()
{
  foo1 f1;
  f1.method1();
  f1.method2();
  f1.method3();
  std::cout << std::endl;

  foo2<> f2;
  f2.method1();
  f2.method2();
  f2.method3();
  std::cout << std::endl;

  foo2<foo3_aspect> f3;
  f3.method1();
  f3.method2();
  f3.method3();

  return 0;
}
