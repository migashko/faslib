//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_UNIQUE_FIRST_HPP
#define FAS_TYPE_LIST_UNIQUE_FIRST_HPP

#include <fas/type_list/unique.hpp>
#include <fas/type_list/reverse.hpp>

namespace fas{

template<typename L>
struct unique_first
{
  typedef typename reverse< 
    typename unique< 
      typename reverse<L>::type 
    >::type 
  >::type type;
};

}

#endif
