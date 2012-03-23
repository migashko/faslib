//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_IS_TYPE_LIST_HPP
#define FAS_TYPE_LIST_IS_TYPE_LIST_HPP

#include <fas/typemanip/is_has_metatype.hpp>
#include <fas/type_list/metalist.hpp>
#include <fas/type_list/errorlist.hpp>
#include <fas/integral/bool_.hpp>
#include <fas/typemanip/if_c.hpp>

#include <fas/type_list/type_list.hpp>
//#include <fas/type_list/tl.hpp>
#include <fas/type_list/empty_list.hpp>
//#include <fas/type_list/el.hpp>

namespace fas{

template<typename L>
struct is_type_list
{
  enum
  {
    value = is_has_metatype<L, metalist::type_list>::value
            || is_has_metatype<L, metalist::empty_list>::value
  };

  typedef bool_<value> type;

  typedef typename if_c<
      value,
      errorlist::noerror,
      errorlist::not_type_list
  >::type error;
};

#ifndef DISABLE_TYPE_LIST_SPEC
template<typename L, typename R >
struct is_type_list< type_list<L, R> >
{
  enum { value = 1};
  typedef bool_<true> type;
  typedef errorlist::noerror error;
};

/*
template<typename L, typename R >
struct is_type_list< tl<L, R> >
{
  enum { value = 1};
  typedef bool_<true> type;
  typedef errorlist::noerror error;
};
*/

template<>
struct is_type_list< empty_list >
{
  enum { value = 1};
  typedef bool_<true> type;
  typedef errorlist::noerror error;
};

/*
template<>
struct is_type_list< el >
{
  enum { value = 1};
  typedef bool_<true> type;
  typedef errorlist::noerror error;
};*/

#endif //DISABLE_TYPE_LIST_SPEC


}

#endif
