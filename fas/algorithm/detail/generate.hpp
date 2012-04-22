//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_DETAIL_GENERATE_HPP
#define FAS_ALGORITHM_DETAIL_GENERATE_HPP

#include <fas/type_list/type_list.hpp>
#include <fas/type_list/empty_list.hpp>

namespace fas{ namespace detail{

template<int I, typename G>
struct generate_helper
{
  typedef type_list<
    typename G::type,
    typename generate_helper<
      I-1,
      typename G::next
    >::type
  > type;
};

template<typename G>
struct generate_helper<0, G>
{
  typedef empty_list type;
};

}}

#endif
