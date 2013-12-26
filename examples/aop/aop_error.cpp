#include <iostream>
#include <fas/aop.hpp>

struct _method1_;
struct _method2_;
struct _method3_;
struct _methodX_;

struct ad_method1
{
  template<typename T>
  void operator()(T&) { std::cout << "method1" << std::endl; }
};

struct ad_method2
{
  template<typename T>
  void operator()(T&) { std::cout << "method2" << std::endl; }
};

struct ad_method3
{
  template<typename T>
  void operator()(T&) { std::cout << "method3" << std::endl; }
};

typedef fas::type_list_n<
  fas::advice<_method1_, ad_method1>,
  fas::advice<_method2_, ad_method2>,
  fas::advice<_method3_, ad_method3>
>::type advice_list;

struct foo_aspect: fas::aspect< advice_list >{};

template<typename A = fas::aspect<> >
class foo
  : public fas::aspect_class< typename fas::merge_aspect<A, foo_aspect>::type >
{
public:
  void method1() { this->get_aspect().template get<_method1_>()(*this); }
  void method2() { this->get_aspect().template get<_method2_>()(*this); }
  void method3() { this->get_aspect().template get<_method3_>()(*this); }
};

/// /////////////////////////////////////////////////////

struct _method3_orig_;
struct ad_method3a
{
  template<typename T>
  void operator()(T& t)
  {
    std::cout << "method3a" << std::endl;
    t.get_aspect().template get<_method3_orig_>()(t);
  }
};

/// раскомментируйте одну из строк, чтобы увидеть ошибку вашего компилятора
struct error_aspect: fas::aspect< fas::type_list_n<
  fas::advice<_method3_, ad_method3a>,
  fas::forward<_method3_orig_, _method3_>
  //,fas::remover<_method3_> // error: invalid use of incomplete type ‘fas::static_error<fas::errorlist::advice_has_been_removed<_method3_>, 0>::type ...
  //, fas::alias<_method3_, _method3_orig_> // error: invalid use of incomplete type ‘fas::static_error<fas::errorlist::recursive_alias<fas::type_list<_method3_orig_, fas::empty_list> >, 0>::type ...

>::type >{};


int main()
{
  foo<error_aspect> f1;
  f1.method1();
  f1.method2();
  f1.method3();
  // f1.get_aspect().get<_methodX_>(); // error: error: invalid use of incomplete type ‘fas::static_error<fas::errorlist::advice_not_found<_methodX_>, 0>::type ...
  std::cout << std::endl;

  return 0;
}
