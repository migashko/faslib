//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_HEAD_HPP
#define FAS_TYPE_LIST_HEAD_HPP

#include <fas/type_list/metalist.hpp>

#include <fas/type_list/empty_list.hpp>
#include <fas/type_list/type_list.hpp>

namespace fas{

template<typename L>
struct head
{
  typedef typename L::left_type type;
  typedef typename L::right_type tail;
};

template<>
struct head<empty_list>
{
  typedef empty_list type;
  typedef empty_list tail;
};

template< typename L, typename R >
struct head<type_list<L, R> >
{
  typedef L type;
  typedef R tail;
};

}

#endif
