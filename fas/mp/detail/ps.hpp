// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_MP_DETAIL_PS_HPP
#define FAS_MP_DETAIL_PS_HPP

#include <fas/mp/is_placeholder.hpp>
#include <fas/mp/w.hpp>
#include <fas/type_list/type_at.hpp>
#include <fas/type_list/type_at_c.hpp>
#include <fas/integral/dec.hpp>


namespace fas{ namespace detail{

template<typename PH, typename PL, int PD, int>
struct ps_impl;

template<typename PH, typename PL, int PD>
struct ps_impl2;

  
template<typename PH, typename PL, int PD>
struct ps_helper
 : ps_impl<PH, PL, PD, is_placeholder<PH>::value >
{
  //typedef typename ps_impl<PH, PL, PD, is_placeholder<PH>::value >::type type;
};

template<typename PH, typename PL, int PD, int>
struct ps_impl
  : ps_impl2<PH, PL, PD>
{
};

template<typename PH, typename PL, int PD>
struct ps_impl<PH, PL, PD, false>
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
  // typedef typename type_at< dec<PH>, PL>::type wtype;
  typedef typename ps_impl3< PH::value - 1, PL, is_type_list<PL>::value >::type wtype;
  typedef typename unw<wtype>::type type;
  enum { value = 0 };
};

template<typename PL, int PD>
struct ps_impl2<_, PL, PD>
{
  // typedef typename type_at_c< PD, PL>::type wtype;
  typedef typename ps_impl3< PD, PL, is_type_list<PL>::value >::type wtype;
  typedef typename unw<wtype>::type type;
  enum { value = 1 };
};



  /*
template<typename PH, typename PL, int>
struct ps_impl;

template<typename PH, typename PL>
struct ps
{
  typedef typename ps_impl< PH, PL, _is_placeholder<PH>::value >::type type; 
};


template<typename PH, typename PL, int>
struct ps_impl
{
  typedef typename type_at< dec<PH>, PL>::type wrapped_type;
  typedef typename _unwrap<wrapped_type>::type type;
};

template<typename P, typename PL>
struct ps_impl<P, PL, false>
{
  typedef P type;
};
*/


}}

#endif
