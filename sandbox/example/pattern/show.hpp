#ifndef FASLIB_EXAMPLE_SHOW_HPP
#define FASLIB_EXAMPLE_SHOW_HPP

#include <fas/type_list/is_type_list.hpp>
#include <fas/typemanip/metalist.hpp>
#include <fas/typemanip/unwrap.hpp>
#include <iostream>
#include <cstdlib>

using namespace ::fas;


template<typename T>
void show();

template<bool, typename T>
struct show_impl;

template<typename M, typename T>
struct show_impl2;

template<bool, typename T>
struct show_impl3;

template<typename T>
struct showT
  : show_impl< is_type_list<T>::value, T >
{
};

template<typename T>
struct show_impl<false, T>
{
  void operator()()
  {
    T t;
    std::cout << t.name() << t.value() << std::endl;
  }
};

template<typename T>
struct show_impl<true, T>
  : show_impl2< typename T::metatype, T >
{
};

template<typename T>
struct show_impl2<metalist::type_list, T>
{
  void operator()()
  {
    typedef typename T::left_type head;
    typedef typename T::right_type tail;
    show_impl3<is_has_metatype<head, metalist::wrapper>::value, head >()();
    show<tail>();
    /*
    typename T::left_type t;
    std::cout << t.name() << t.value() << " ";
    show<typename T::right_type>();
    */
  }
};

template<typename T>
struct show_impl2<metalist::empty_list, T>
{
  void operator()()
  {
    std::cout << std::endl;
    //abort();
  }
};

template<typename T>
struct show_impl3<false, T>
{
  void operator()()
  {
    T t;
    std::cout << t.name() << t.value() << " ";
  }
};

template<typename T>
struct show_impl3<true, T>
{
  void operator()()
  {
    std::cout<<"wrapper:";
    showT< typename unwrap<T>::type >()();
  }
};


template<typename T>
void show()
{
  showT<T>()();
};

/*
template<bool B, typename T>
void show();

template<typename T>
void show_foo(T t)
{
  std::cout << t.name() << t.value() << std::endl;
};

template<typename L>
void show( fas::pattern::metalist::type_list )
{
  show(typename L::left_type());
  show<typename L::right_type>( typename L::right_type::metatype() );
};

template<typename L>
void show( fas::pattern::metalist:: )
{
  std::cout << std::endl;
}

template<bool B, typename T>
void show()
{
  if (B)
    ;
  else
    show_foo( T() );
};
*/

/*
template<typename T>
void show_foo(T t);

template<bool B, typename T>
void show(T t);


template<typename T>
void show_list()
{
  show1<fas::pattern::is_type_list<T>::value, T>();
};

template<bool B, typename T>
void show()
{
  if (B)
    ;
  else
    show_foo( T() );
};

template<typename T>
void show_foo(T t)
{
  std::cout << t.name() << t.value() << std::endl;
};
*/


#endif
