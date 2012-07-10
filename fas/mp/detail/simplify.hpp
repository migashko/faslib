//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_MP_DETAIL_SIMPLIFY_HPP
#define FAS_MP_DETAIL_SIMPLIFY_HPP

#include <fas/mp/is_placeholder.hpp>
#include <fas/mp/has_type.hpp>
#include <fas/mp/a.hpp>
#include <fas/mp/w.hpp>

namespace fas{ namespace detail{

template<typename F, int>
struct simplify_impl;

template<typename F>
struct simplify_impl2;

template<typename F, int>
struct simplify_impl3;

template<typename F, int>
struct simplify_impl4;

template<typename F>
struct simplify_helper
{
  typedef typename simplify_impl<F, is_placeholder<F>::value || is_a<F>::value >::type type;
};

template<typename F>
struct simplify_impl<F, false>
{
  typedef simplify_impl2<F> simplify_type;
  typedef typename simplify_type::type type;
  enum { value = simplify_type::value};
};

template<typename F>
struct simplify_impl<F, true>
{
  typedef F type;
  enum { value = 1};
};

template<typename F>
struct simplify_impl2_1;

template<typename F>
struct simplify_impl2_2;

template<typename F>
struct simplify_impl2_3;

template<typename F>
struct simplify_impl2_4;

template<typename F>
struct simplify_impl2
  : simplify_impl2_4<F>
{};

template<typename F>
struct simplify_impl2_1
{
  enum { value = 0};
  typedef typename simplify_impl3<F, value >::type type;
};

template<typename F>
struct simplify_impl2_1< w<F> >
{
  enum { value = 0};
  typedef w<F> type;
};


template< template<typename> class F, typename P0 >
struct simplify_impl2_1 < F<P0> >
{
  typedef simplify_impl< P0, is_placeholder<P0>::value || is_a<P0>::value > si0;
  
  enum { value = si0::value };
  
  typedef F<
    typename si0::type
  > simplified;
  
  typedef typename simplify_impl3<simplified, value >::type type;
};

template<typename F>
struct simplify_impl2_2: simplify_impl2_1<F> {};

template< template<typename, typename> class F, typename P0, typename P1 >
struct simplify_impl2_2 < F<P0, P1> >
{
  typedef simplify_impl< P0, is_placeholder<P0>::value || is_a<P0>::value > si0;
  typedef simplify_impl< P1, is_placeholder<P1>::value || is_a<P1>::value > si1;
  
  enum { value = si0::value || si1::value };
  
  typedef F<
    typename si0::type,
    typename si1::type
  > simplified;
  
  typedef typename simplify_impl3<simplified, value >::type type;
};

template<typename F>
struct simplify_impl2_3
  : simplify_impl2_2<F>
{};


template< template<typename, typename, typename> class F, typename P0, typename P1, typename P2 >
struct simplify_impl2_3 < F<P0, P1, P2> >
{
  typedef simplify_impl< P0, is_placeholder<P0>::value || is_a<P0>::value > si0;
  typedef simplify_impl< P1, is_placeholder<P1>::value || is_a<P1>::value > si1;
  typedef simplify_impl< P2, is_placeholder<P2>::value || is_a<P2>::value > si2;
  
  enum { value = si0::value || si1::value || si2::value};
  
  typedef F<
    typename si0::type,
    typename si1::type,
    typename si2::type
  > simplified;
  
  typedef typename simplify_impl3<simplified, value >::type type;
};

template<typename F>
struct simplify_impl2_4
  : simplify_impl2_3<F> 
{};

template<
  template<typename, typename, typename, typename> class F, 
  typename P0, typename P1, typename P2, typename P3
>
struct simplify_impl2_4 < F<P0, P1, P2, P3> >
{
  typedef simplify_impl< P0, is_placeholder<P0>::value || is_a<P0>::value > si0;
  typedef simplify_impl< P1, is_placeholder<P1>::value || is_a<P1>::value > si1;
  typedef simplify_impl< P2, is_placeholder<P2>::value || is_a<P2>::value > si2;
  typedef simplify_impl< P3, is_placeholder<P3>::value || is_a<P3>::value > si3;
  
  enum { value = si0::value || si1::value || si2::value || si3::value};
  
  typedef F<
    typename si0::type,
    typename si1::type,
    typename si2::type,
    typename si3::type
  > simplified;
  
  typedef typename simplify_impl3<simplified, value >::type type;
};

template<
  template<typename, typename, typename, typename, typename> class F, 
  typename P0, typename P1, typename P2, typename P3, typename P4 
>
struct simplify_impl2 < F<P0, P1, P2, P3, P4> >
{
  typedef simplify_impl< P0, is_placeholder<P0>::value || is_a<P0>::value > si0;
  typedef simplify_impl< P1, is_placeholder<P1>::value || is_a<P1>::value > si1;
  typedef simplify_impl< P2, is_placeholder<P2>::value || is_a<P2>::value > si2;
  typedef simplify_impl< P3, is_placeholder<P3>::value || is_a<P2>::value > si3;
  typedef simplify_impl< P4, is_placeholder<P4>::value || is_a<P4>::value > si4;
  
  enum { value = si0::value || si1::value || si2::value || si3::value || si4::value};
  
  typedef F<
    typename si0::type,
    typename si1::type,
    typename si2::type,
    typename si3::type,
    typename si4::type
  > simplified;
  
  typedef typename simplify_impl3<simplified, value >::type type;
};


template<typename F>
struct simplify_impl3<F, false>
{
  typedef typename simplify_impl4<F, has_type<F>::value >::type type;
};

template<typename F>
struct simplify_impl3<F, true>
{
  typedef F type;
};

template<typename F, int>
struct simplify_impl4
{
  typedef typename F::type type;
};

template<typename F>
struct simplify_impl4<F, false>
{
  typedef F type;
};


}}

#endif
