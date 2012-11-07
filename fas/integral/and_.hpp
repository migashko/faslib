//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_AND__HPP
#define FAS_INTEGRAL_AND__HPP

#include <fas/integral/bool_.hpp>

namespace fas{

namespace detail{

template<typename A, typename B>
struct and_helper;


template<typename A>
struct and_helper<false_, A>
{
  enum { value = 0 };
  typedef false_ type;
};

template<typename A>
struct and_helper<true_, A>
{
  enum { value = A::value };
  typedef bool_< value > type;
};

/*
template<typename A>
struct and_helper<A, false_>
{
  enum { value = 0 };
  typedef false_ type;
};

template<typename A>
struct and_helper<A, true_>
{
  enum { value = A::value };
  typedef bool_< value > type;
};

template<>
struct and_helper<true_, true_>
{
  enum { value = 1 };
  typedef true_ type;
};
*/
}


template<typename A, typename B>
struct and_
  : and_< bool_< A::value!=0 >, B >
{
};

template<typename B>
struct and_<false_, B>
{
  enum { value = 0 };
  typedef false_ type;
};

template<typename B>
struct and_<true_, B>
{
  enum { value = (B::value!=0) };
  typedef bool_< value > type;
};


}

#endif
