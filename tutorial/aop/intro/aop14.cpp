#include <fas/aop.hpp>
#include <fas/type_list.hpp>

//#include <iostream>
#include <stdio.h>

struct _stateA_;
struct _stateB_;
struct _stateC_;
struct _state_;
struct _state_context_;

struct stateA
{
  template<typename T>
  void operator()(T& t, int value )
  {
    printf("A%d ", value);
    // std::cout << "A" << value << " ";
    if (value > 1)
      t.get_aspect().template get<_state_context_>()
                    .template set_state<_stateB_>(t);
  }
};

struct stateB
{
  template<typename T>
  void operator()(T& t, int value )
  {
    printf("B%d ", value);
    //std::cout << "B" << value << " ";
    if ( value == 2)
      t.template set_state<_stateA_>();
    else if (value > 6)
      t.template set_state<_stateC_>();
  }
};

struct stateC
{
  template<typename T>
  void operator()(T& t, int value )
  {
    printf("C%d ", value);
    //std::cout << "C" << value << " ";
  }
};

struct f_state
{
  f_state(int state, int value): _counter(0), _state(state), _value(value) {}
  
  template<typename T, typename Tg>
  void operator()(T& t, fas::tag<Tg> )
  {
    if ( _counter++ == _state )
      t.get_aspect().template get<Tg>()(t, _value);
  }
  
private:
  int _counter;
  int _state;
  int _value;
};

class state
{
public:
  state(): _state(0) {};
  
  template<typename T>
  void clear(T&) { _state = 0;}
  
  template<typename Tg, typename T>
  void set_state(T& t)
  {
    typedef typename T::aspect::template select_group<_state_>::type state_list; 
    _state = fas::index_of<Tg, state_list>::value;
  }
  
  template<typename T>
  void operator()(T& t, int value )
  {
    t.get_aspect().template getg<_state_>().for_each( t, f_state(_state, value) );
  }
  
private:
  int _state; 
};


struct aspect_state: fas::aspect< fas::type_list_n<
  fas::advice<_state_context_, state >,
  fas::advice<_stateA_, stateA >,
  fas::advice<_stateB_, stateB >,
  fas::advice<_stateC_, stateC >,
  fas::group<_state_, _stateA_>, 
  fas::group<_state_, fas::type_list_n<_stateB_, _stateC_>::type >
>::type > {};

template<typename A = fas::empty_type >
class test_state:
  public fas::aspect_class<A, aspect_state>
{
public:
  void test(int value)
  {
    this->get_aspect().template get<_state_context_>()(*this, value);
  }

// typedef fas::aspect_class<A, aspect_state> super;
// friend class super::aspect::template advice_cast<_stateA_>::type;
// friend class super::aspect::template advice_cast<_stateB_>::type;
// friend class super::aspect::template advice_cast<_stateC_>::type;
// protected:

  template<typename Tg>
  void set_state()
  {
    this->get_aspect().template get<_state_context_>().set_state<Tg>(*this);
  }
};

int main()
{
  test_state<> ts;
  for (int i = 0; i < 10; ++i)
    ts.test(i);
  //std::cout << std::endl;
  printf("\n");
  return 0;
}
