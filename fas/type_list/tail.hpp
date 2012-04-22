//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_TAIL_HPP
#define FAS_TYPE_LIST_TAIL_HPP

#include <fas/type_list/metalist.hpp>
#include <fas/type_list/empty_list.hpp>

namespace fas{

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
