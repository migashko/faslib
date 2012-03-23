//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_NORMALIZE_HPP
#define FAS_TYPE_LIST_NORMALIZE_HPP

#include <fas/type_list/type_list.hpp>
#include <fas/type_list/is_type_list.hpp>
#include <fas/type_list/organize.hpp>
#include <fas/type_list/detail/normalize.hpp>

namespace fas{

template<typename L>
struct normalize
{
  typedef typename detail::normalize_helper<L, is_type_list<L>::value >::type type;
};

template<>
struct normalize<empty_type>
{
  typedef empty_list type;
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<>
struct normalize<empty_list>
{
  typedef empty_list type;
};

template<typename L, typename R>
struct normalize< type_list<L, R> >
{
  typedef typename organize< type_list<L, R> >::type type;
};

#endif

}

#endif
