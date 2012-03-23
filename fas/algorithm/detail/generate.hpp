//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_DETAIL_GENERATE_HPP
#define FAS_ALGORITHM_DETAIL_GENERATE_HPP

#include <fas/type_list/type_list.hpp>

namespace fas{ namespace detail{

template<int I, typename G, typename P>
struct generate_helper
{
  typedef typename P::template rebind<
    typename G::type,
    typename generate_helper<
      I-1,
      typename G::next,
      P
    >::type
  >::type type;
};

template<typename G, typename P>
struct generate_helper<0, G, P>
{
  typedef typename P::final_type type;
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<int I, typename G>
struct generate_helper<I, G, empty_list>
{
  typedef type_list<
    typename G::type,
    typename generate_helper<
      I-1,
      typename G::next,
      empty_list
    >::type
  > type;
};

template<typename G>
struct generate_helper<0, G, empty_list>
{
  typedef empty_list type;
};

#endif

}}

#endif
