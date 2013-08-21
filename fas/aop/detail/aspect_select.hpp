//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011, 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_DETAIL_ASPECT_SELECT_T_HPP
#define FAS_AOP_DETAIL_ASPECT_SELECT_T_HPP

#include <fas/aop/private/is_aspect.hpp>
#include <fas/algorithm/transform_if.hpp>
#include <fas/algorithm/select.hpp>
#include <fas/type_list/normalize.hpp>

namespace fas{ namespace detail{

template<typename T>
struct advice_list_cast
{
  typedef typename T::advice_list type;
};

template<typename T>
struct aspect_transform
{
  typedef typename transform_if<
    T,
    aspect_transform< advice_list_cast<_1> >,
    is_aspect<_1>
  >::type type;
};

template<typename L, template<typename> class F>
struct aspect_select_t
{
  typedef typename aspect_transform< typename advice_list_cast<L>::type >::type raw_list;
  typedef typename normalize<raw_list>::type flat_list;
  typedef typename select_t<flat_list, F>::type type;
};

}}

#endif
