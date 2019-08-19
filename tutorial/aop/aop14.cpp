#include <fas/aop.hpp>
#include <fas/type_list.hpp>
#include <cstdio>

struct _stateA_;
struct _stateB_;
struct _stateC_;
struct _state_;
struct _state_context_;
struct _change_state_;

struct stateA
{
  template<typename T>
  void operator()(T& t, int value ) const
  {
    printf("A%d ", value);
    if (value > 1)
      t.get_aspect().template get<_state_context_>()
                    .template set_state<_stateB_>(t);
  }
};

struct stateB
{
  template<typename T>
  void operator()(T& t, int value ) const
  {
    printf("B%d ", value);
    if ( value == 3)
      t.template set_state<_stateA_>();
    else if (value > 6)
      t.template set_state<_stateC_>();
  }
};

struct stateC
{
  template<typename T>
  void operator()(T&, int value ) const
  {
    printf("C%d ", value);
  }
};

struct f_state
{
  f_state(int state, int value)
    : _counter(0)
    , _state(state)
    , _value(value)
  {}

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


class state_context
{
public:
  state_context(): _state(0) {}

  template<typename Tg, typename T>
  void set_state(T& t)
  {
    typedef typename T::aspect::template select_group<_state_>::type state_list;
    _state = fas::index_of<Tg, state_list>::value;
    t.get_aspect().template getg<_change_state_>()(t, fas::tag<Tg>() );
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
  fas::advice<_state_context_, state_context >,
  fas::advice<_stateA_, stateA >, fas::group<_state_, _stateA_>,
  fas::advice<_stateB_, stateB >, fas::group<_state_, _stateB_>,
  fas::advice<_stateC_, stateC >, fas::group<_state_, _stateC_>
>::type > {};

template<typename A = fas::empty_type >
class test_state:
  public fas::aspect_class< typename fas::merge_aspect<A, aspect_state>::type >
{
public:
  void test(int value)
  {
    this->get_aspect().template get<_state_context_>()(*this, value);
  }

//typedef fas::aspect_class<A, aspect_state> super;
//friend class super::aspect::template advice_cast<_stateA_>::type;
//friend class super::aspect::template advice_cast<_stateB_>::type;
//friend class super::aspect::template advice_cast<_stateC_>::type;
//protected:

  template<typename Tg>
  void set_state()
  {
    this->get_aspect().template get<_state_context_>().template set_state<Tg>(*this);
  }
};

/// /////////////////////////////////

struct _show_change_state_;

struct ad_change_state
{
  template<typename T, typename Tg>
  void operator()(T& , fas::tag<Tg>) const
  {
    printf("| ");
  }
};

struct aspect_change_state: fas::aspect< fas::type_list_n<
  fas::advice<_show_change_state_, ad_change_state>,
  fas::group<_change_state_, _show_change_state_>
>::type > {};

int main()
{
  test_state<> ts;
  for (int i = 0; i < 10; ++i)
    ts.test(i);
  printf("\n");

  test_state<aspect_change_state> ts2;
  for (int i = 0; i < 10; ++i)
    ts2.test(i);
  printf("\n");

  return 0;
}
