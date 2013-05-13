//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_MP_DETAIL_BIND_HPP
#define FAS_MP_DETAIL_BIND_HPP

#include <fas/mp/p.hpp>
#include <fas/mp/w.hpp>
#include <fas/mp/private/ps_c.hpp>

namespace fas{ namespace detail{

template<typename F, typename PL, int IsP, int Counter_>
struct bind_impl1;

template<typename F, typename PL, int Counter_>
struct bind_impl2;

template<typename F, typename PL>
struct bind_helper
{
  typedef typename bind_impl1<F, PL, is_p<F>::value, 0 >::type type;
};

template<typename F, typename PL, int Counter_>
struct bind_impl1<F, PL, true, Counter_>
{
  typedef typename unp<F>::type type;
  enum { counter = Counter_ };
};

template<typename F, typename PL, int Counter_>
struct bind_impl1<F, PL, false, Counter_>
{
  typedef bind_impl2<F, PL, Counter_> F_bind;
  typedef typename F_bind::type type;
  enum { counter = F_bind::counter };
};

template<typename F, typename PL, int Counter_>
struct bind_impl2_1;

template<typename F, typename PL, int Counter_>
struct bind_impl2_2;

template<typename F, typename PL, int Counter_>
struct bind_impl2_3;

template<typename F, typename PL, int Counter_>
struct bind_impl2_4;


template<typename F, typename PL, int Counter_>
struct bind_impl2_1
{
  typedef ps_c< F, PL, Counter_ > placeholder_select;
  enum { counter = Counter_ + placeholder_select::value };
  typedef typename placeholder_select::type type;
};

template<typename F, typename PL, int Counter_>
struct bind_impl2_1< w<F>, PL, Counter_>
{
  enum { counter = Counter_ };
  typedef w<F> type;
};

template<
  template<typename> class F,
  typename P0,
  typename PL, int Counter_
>
struct bind_impl2_1< F<P0>, PL, Counter_>
{
  typedef P0 arg0;
  typedef bind_impl1< arg0, PL, is_p<arg0>::value, Counter_ > P0_bind;

  enum { counter = P0_bind::counter };

  typedef F<
    typename P0_bind::type
  > type;
};

template<typename F, typename PL, int Counter_>
struct bind_impl2_2
  : bind_impl2_1 < F, PL, Counter_ >
{};

template<
  template<typename, typename> class F,
  typename P0, typename P1,
  typename PL, int Counter_
>
struct bind_impl2_2< F<P0, P1>, PL, Counter_>
{
  typedef P0 arg0;
  typedef P1 arg1;

  typedef bind_impl1< arg0, PL, is_p<arg0>::value, Counter_ > P0_bind;
  enum { counter0 = P0_bind::counter };

  typedef bind_impl1< arg1, PL, is_p<arg1>::value, counter0 > P1_bind;
  enum { counter = P1_bind::counter };

  typedef F<
    typename P0_bind::type,
    typename P1_bind::type
  > type;
};


template<typename F, typename PL, int Counter_>
struct bind_impl2_3
  : bind_impl2_2 < F, PL, Counter_ >
{};


template<
  template<typename, typename, typename> class F,
  typename P0, typename P1, typename P2,
  typename PL, int Counter_
>
struct bind_impl2_3< F<P0, P1, P2>, PL, Counter_>
{
  typedef P0 arg0;
  typedef P1 arg1;
  typedef P2 arg2;

  typedef bind_impl1< arg0, PL, is_p<arg0>::value, Counter_ > P0_bind;
  enum { counter0 = P0_bind::counter };

  typedef bind_impl1< arg1, PL, is_p<arg1>::value, counter0 > P1_bind;
  enum { counter1 = P1_bind::counter };

  typedef bind_impl1< arg2, PL, is_p<arg2>::value, counter1 > P2_bind;
  enum { counter = P2_bind::counter };

  typedef F<
    typename P0_bind::type,
    typename P1_bind::type,
    typename P2_bind::type
  > type;
};

template<typename F, typename PL, int Counter_>
struct bind_impl2_4
  : bind_impl2_3 < F, PL, Counter_ >
{};

template<
  template<typename, typename, typename, typename> class F,
  typename P0, typename P1, typename P2, typename P3,
  typename PL, int Counter_
>
struct bind_impl2_4< F<P0, P1, P2, P3>, PL, Counter_>
{
  typedef P0 arg0;
  typedef P1 arg1;
  typedef P2 arg2;
  typedef P3 arg3;

  typedef bind_impl1< arg0, PL, is_p<arg0>::value, Counter_ > P0_bind;
  enum { counter0 = P0_bind::counter };

  typedef bind_impl1< arg1, PL, is_p<arg1>::value, counter0 > P1_bind;
  enum { counter1 = P1_bind::counter };

  typedef bind_impl1< arg2, PL, is_p<arg2>::value, counter1 > P2_bind;
  enum { counter2 = P2_bind::counter };

  typedef bind_impl1< arg3, PL, is_p<arg3>::value, counter2 > P3_bind;
  enum { counter = P3_bind::counter };

  typedef F<
    typename P0_bind::type,
    typename P1_bind::type,
    typename P2_bind::type,
    typename P3_bind::type
  > type;
};

template<typename F, typename PL, int Counter_>
struct bind_impl2
  : bind_impl2_4< F, PL, Counter_ >
{
};

template<
  template<typename, typename, typename, typename, typename> class F,
  typename P0, typename P1, typename P2, typename P3, typename P4,
  typename PL, int Counter_
>
struct bind_impl2< F<P0, P1, P2, P3, P4>, PL, Counter_>
{
  typedef P0 arg0;
  typedef P1 arg1;
  typedef P2 arg2;
  typedef P3 arg3;
  typedef P4 arg4;

  typedef bind_impl1< arg0, PL, is_p<arg0>::value, Counter_ > P0_bind;
  enum { counter0 = P0_bind::counter };

  typedef bind_impl1< arg1, PL, is_p<arg1>::value, counter0 > P1_bind;
  enum { counter1 = P1_bind::counter };

  typedef bind_impl1< arg2, PL, is_p<arg2>::value, counter1 > P2_bind;
  enum { counter2 = P2_bind::counter };

  typedef bind_impl1< arg3, PL, is_p<arg3>::value, counter2 > P3_bind;
  enum { counter3 = P3_bind::counter };

  typedef bind_impl1< arg4, PL, is_p<arg4>::value, counter3 > P4_bind;
  enum { counter = P4_bind::counter };

  typedef F<
    typename P0_bind::type,
    typename P1_bind::type,
    typename P2_bind::type,
    typename P3_bind::type,
    typename P4_bind::type
  > type;
};

}}

#endif
