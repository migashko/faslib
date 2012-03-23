//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_CHECK_TWO_LIST_HPP
#define FAS_TYPE_LIST_CHECK_TWO_LIST_HPP


#include <fas/typemanip/if_c.hpp>
#include <fas/type_list/check_list.hpp>

namespace fas{

template<typename L1, typename L2>
struct check_two_lists
{
  typedef check_list<L1> check_first;
  typedef check_list<L2> check_second;
  typedef typename if_c<
      !check_first::value,
      typename check_first::error,
      typename check_second::error
  >::type error;

  enum { value = check_first::value && check_second::value};
  typedef bool_<value> type;
};

}


#endif
