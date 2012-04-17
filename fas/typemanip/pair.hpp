//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_PAIR_HPP
#define FAS_TYPEMANIP_PAIR_HPP

#include <fas/typemanip/first.hpp>
#include <fas/typemanip/second.hpp>

namespace fas{

template<typename T1, typename T2>
struct pair
{
  typedef T1 first;
  typedef T2 second;
};

template<typename T1, typename T2>
struct first< pair<T1, T2> >
{
  typedef T1 type;
};

template<typename T1, typename T2>
struct second< pair<T1, T2> >
{
  typedef T2 type;
};

}

#endif
