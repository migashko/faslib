//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_TUPLE_HPP
#define FAS_TYPEMANIP_TUPLE_HPP

#include <fas/typemanip/first.hpp>
#include <fas/typemanip/second.hpp>
#include <fas/typemanip/third.hpp>
#include <fas/typemanip/fourth.hpp>
#include <fas/typemanip/fifth.hpp>

#include <fas/typemanip/empty_type.hpp>

namespace fas{

template<typename T1 = empty_type, typename T2 = empty_type, typename T3 = empty_type, typename T4 = empty_type, typename T5 = empty_type>
struct tuple
{
  typedef T1 first;
  typedef T2 second;
  typedef T3 third;
  typedef T4 fourth;
  typedef T5 fifth;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5>
struct first< tuple<T1, T2, T3, T4, T5> >
{
  typedef T1 type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5>
struct second< tuple<T1, T2, T3, T4, T5> >
{
  typedef T2 type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5>
struct third< tuple<T1, T2, T3, T4, T5> >
{
  typedef T3 type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5>
struct fourth< tuple<T1, T2, T3, T4, T5> >
{
  typedef T4 type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5>
struct fifth< tuple<T1, T2, T3, T4, T5> >
{
  typedef T5 type;
};

}

#endif
