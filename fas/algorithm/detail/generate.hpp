//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_DETAIL_GENERATE_HPP
#define FAS_ALGORITHM_DETAIL_GENERATE_HPP

#include <fas/algorithm/errorlist.hpp>
#include <fas/algorithm/has_next.hpp>
#include <fas/typemanip/if_c.hpp>

#include <fas/type_list/type_list.hpp>
#include <fas/type_list/empty_list.hpp>

#include <fas/static_check/static_error.hpp>

namespace fas{ namespace detail{
  
template<int I, typename G>
struct generate_impl1
{
  typedef type_list<
    typename G::type,
    typename generate_impl1<
      I-1,
      typename G::next
    >::type
  > type;
};

template<typename G>
struct generate_impl1<0, G>
{
  typedef empty_list type;
};


template<int I, typename G>
struct generate_impl
  : static_error< errorlist::generator_required, has_next<G>::value >::type
{
  typedef typename generate_impl1< I, G>::type type;
};


}}

#endif
