//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_EMPTY_LIST_HPP
#define FAS_TYPE_LIST_EMPTY_LIST_HPP

#include <fas/type_list/metalist.hpp>

namespace fas{

template<typename LL, typename RR>
struct type_list;

/**
 * Пустой тип.
 * Используется в качестве завершающего типа в списке типов.
 */
struct empty_list
{
  /** Метатип.
   * Значение metalist::
   */
  typedef metalist::empty_list metatype;

  typedef empty_list final_type;
  
  template<typename LL, typename RR>
  struct rebind
  {
    typedef type_list<LL, RR> type;
  };

};

}

#endif
