//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_STATIC_CHECK_STATIC_ERROR_HPP
#define FAS_STATIC_CHECK_STATIC_ERROR_HPP

#include <fas/static_check/errorlist.hpp>

namespace fas{

template<typename E, int V>
struct static_error
  //: errorlist::noerror<E>
{
  /*enum { value = V };*/
  typedef errorlist::noerror<E> type;
  
};

template<typename E>
struct static_error<E, false> /*: E*/
{
  /*enum { value = 0 };*/
  typedef E type;
};
  
}

#endif

