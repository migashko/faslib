//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_MP_DETAIL_PS_HPP
#define FAS_MP_DETAIL_PS_HPP

#include <fas/integral/dec.hpp>
#include <fas/type_list/type_at_c.hpp>
#include <fas/type_list/is_type_list.hpp>
#include <fas/mp/is_placeholder.hpp>
#include <fas/mp/placeholders.hpp>
#include <fas/mp/private/arg.hpp>

namespace fas{ namespace detail{

template<typename PH, typename PL, int PD, int>
struct ps_impl1;

template<typename PH, typename PL, int PD>
struct ps_impl2;

  
template<typename PH, typename PL, int PD>
struct ps_impl
 : ps_impl1<PH, PL, PD, is_placeholder<PH>::value >
{
};

template<typename PH, typename PL, int PD, int>
struct ps_impl1
  : ps_impl2<PH, PL, PD>
{
};

template<typename PH, typename PL, int PD>
struct ps_impl1<PH, PL, PD, false>
{
  typedef PH type;
  enum { value = 0 };
};

template<int P, typename PL, int isTL>
struct ps_impl3
{
  typedef typename type_at_c< P, PL>::type type;
};

// если PL не список и требуется 0-я позиция...
template<typename PL>
struct ps_impl3<0, PL, false>
{
  typedef PL type;
};

template<typename PH, typename PL, int PD>
struct ps_impl2
{
  typedef typename ps_impl3< PH::value - 1, PL, is_type_list<PL>::value >::type wtype;
  typedef typename arg_extract<wtype>::type type;
  enum { value = 0 };
};

template<typename PL, int PD>
struct ps_impl2<_, PL, PD>
{
  typedef typename ps_impl3< PD, PL, is_type_list<PL>::value >::type wtype;
  typedef typename arg_extract<wtype>::type type;
  enum { value = 1 };
};

}}

#endif
