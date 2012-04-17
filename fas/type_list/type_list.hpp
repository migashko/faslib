//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_TYPE_LIST_HPP
#define FAS_TYPE_LIST_TYPE_LIST_HPP

#include <fas/type_list/metalist.hpp>
#include <fas/type_list/empty_list.hpp>

namespace fas{

template< typename L, typename R = empty_list >
struct type_list
{
  typedef metalist::type_list metatype;
  typedef L left_type;
  typedef R right_type;
};

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

template<typename L>
struct tail
{
  typedef typename L::left_type head;
  typedef typename L::right_type type;
};

template<>
struct tail<empty_list>
{
  typedef empty_list head;
  typedef empty_list type;
  
};

template< typename L, typename R >
struct tail<type_list<L, R> >
{
  typedef L head;
  typedef R type;
};



}

#endif
