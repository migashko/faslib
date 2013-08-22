//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_MP_DETAIL_PH_MAX_HPP
#define FAS_MP_DETAIL_PH_MAX_HPP

#include <fas/mp/p.hpp>
#include <fas/mp/w.hpp>
#include <fas/mp/private/ph_num.hpp>
#include <fas/integral/max_c.hpp>

namespace fas{ namespace detail{

template<typename F, int _C>
struct ph_max_impl1;

template<typename F>
struct ph_max_impl
{
  enum
  {
    value = max_c<
      ph_max_impl1<F, 0>::value,
      ph_max_impl1<F, 0>::count
    >::value
  };
};

template<typename F, int _C>
struct ph_max_impl2;

template<typename F, int _C>
struct ph_max_impl3;

template<typename F, int _C>
struct ph_max_impl4;

template<typename F, int _C>
struct ph_max_impl5;

template<typename F, int _C>
struct ph_max_impl1
  : ph_max_impl5< F, _C>
{};

template< typename P1, int _C>
struct ph_max_impl1< p<P1>, _C >
{
  enum { value = 0, count = _C };
};

template<typename F, int _C>
struct ph_max_impl2
{
  enum
  {
    value = max_c<
      ph_num<F, _C>::value,
      _C
    >::value,
    count = ph_num<F, _C>::next
  };
};

template<typename F, int _C>
struct ph_max_impl2< w<F>, _C >
{
  enum
  {
    value = 0,
    count = _C
  };
};


template<
  template<typename> class F,
  typename P1, int _C
>
struct ph_max_impl2< F<P1>, _C >
{
  enum
  {
    count = ph_max_impl1< P1, _C>::count,

    value = max_c<
      ph_max_impl1< P1, _C>::value,
      _C
    >::value
  };
};

template<typename F, int _C>
struct ph_max_impl3
  : ph_max_impl2< F, _C>
{};

template<
  template<typename, typename> class F,
  typename P1, typename P2,
  int _C
>
struct ph_max_impl3< F<P1, P2>, _C >
{
  enum
  {
    count = ph_max_impl1< P2, ph_max_impl1<P1, _C>::count>::count,
    p1 = ph_max_impl1< P1, _C>::value,
    p2 = ph_max_impl1< P2, _C>::value,
    value = max_c< p1, p2>::value
  };
};

template<typename F, int _C>
struct ph_max_impl4
  : ph_max_impl3< F, _C>
{};

template<
  template<typename, typename, typename> class F,
  typename P1, typename P2, typename P3,
  int _C
>
struct ph_max_impl4< F<P1, P2, P3>, _C >
{
  enum
  {
    count = ph_max_impl1< P3,
            ph_max_impl1< P2,
            ph_max_impl1< P1,
            _C >::count >::count >::count,

    p1 = ph_max_impl1< P1, _C>::value,
    p2 = ph_max_impl1< P2, _C>::value,
    p3 = ph_max_impl1< P3, _C>::value,

    value = max_c< p1, max_c<p2, p3>::value >::value
  };
};

template<typename F, int _C>
struct ph_max_impl5
  : ph_max_impl4< F, _C>
{};

template<
  template<typename, typename, typename, typename> class F,
  typename P1,
  typename P2,
  typename P3,
  typename P4,
  int _C
>
struct ph_max_impl5< F<P1, P2, P3, P4>, _C >
{
  enum
  {
    count = ph_max_impl1< P4,
            ph_max_impl1< P3,
            ph_max_impl1< P2,
            ph_max_impl1< P1,
            _C >::count >::count >::count >::count,

    p1 = ph_max_impl1< P1, _C>::value,
    p2 = ph_max_impl1< P2, _C>::value,
    p3 = ph_max_impl1< P3, _C>::value,
    p4 = ph_max_impl1< P4, _C>::value,

    value = max_c< p1, max_c< p2, max_c< p3, p4 >::value >::value >::value
  };
};

template<
  template<typename, typename, typename, typename, typename> class F,
  typename P1, typename P2, typename P3, typename P4, typename P5,
  int _C
>
struct ph_max_impl1< F<P1, P2, P3, P4, P5>, _C >
{
  enum
  {
    count = ph_max_impl1< P5,
            ph_max_impl1< P4,
            ph_max_impl1< P3,
            ph_max_impl1< P2,
            ph_max_impl1< P1,
            _C >::count >::count >::count >::count>::count,

    p1 = ph_max_impl1< P1, _C>::value,
    p2 = ph_max_impl1< P2, _C>::value,
    p3 = ph_max_impl1< P3, _C>::value,
    p4 = ph_max_impl1< P4, _C>::value,
    p5 = ph_max_impl1< P5, _C>::value,

    value = max_c< p1, max_c<p2, max_c<p3, max_c<p4, p5>::value>::value>::value >::value
  };
};

}}

#endif
