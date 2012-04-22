//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_DETAIL_FIND_IF_HPP
#define FAS_ALGORITHM_DETAIL_FIND_IF_HPP

#include <fas/algorithm/index_of_if.hpp>
#include <fas/type_list/type_at_c.hpp>
#include <fas/typemanip/empty_type.hpp>

namespace fas{ namespace detail{

template<typename L, template<typename> class F, int I>
struct find_if_impl_t;

template<typename L, template<typename> class F>
struct find_if_helper_t
  : find_if_impl_t<L, F, index_of_if_t<L, F>::value >
{
};

template<typename L, template<typename> class F, int I>
struct find_if_impl_t
{
  typedef typename type_at_c< I, L >::type type;
  typedef typename type_at_c< I, L >::tail tail;
};

template<typename L, template<typename> class F>
struct find_if_impl_t<L, F, -1>
{
  typedef empty_type type;
  typedef empty_type tail;
};

}}


#endif
