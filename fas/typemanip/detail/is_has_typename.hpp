//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_DETAIL_IS_HAS_TYPENAME_HPP
#define FAS_TYPEMANIP_DETAIL_IS_HAS_TYPENAME_HPP

#include <fas/typemanip/same_type.hpp>

namespace fas{ namespace detail{


template<typename T, typename D, typename DT,  int>
struct is_has_typename_impl1;

template<typename T, int>
struct is_has_typename_impl2;

template<typename T, typename D, template<typename> class F>
struct is_has_typename_impl
  : is_has_typename_impl1<T, D, typename F<T>::type, F<T>::value >
{
};

template<typename T, typename D, typename DT, int>
struct is_has_typename_impl1
  : is_has_typename_impl2< T, same_type< D, DT >::value >
{
};

template<typename T, typename D, typename DT>
struct is_has_typename_impl1<T, D, DT, false>
{
  enum { value = 0};
};

template<typename T, int>
struct is_has_typename_impl2
{
  enum { value = 1};
};

template<typename T>
struct is_has_typename_impl2<T, false>
{
  enum { value = 0};
};

}}

#endif
