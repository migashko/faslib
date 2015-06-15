//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_ERASE_IF_HPP
#define FAS_ALGORITHM_ERASE_IF_HPP

#include <fas/algorithm/select.hpp>

#include <fas/mp/lambda.hpp>
#include <fas/mp/placeholders.hpp>

#include <fas/integral/not_.hpp>

namespace fas{

template<typename L, typename F >
struct erase_if
  : select< L, not_<F> >
{
};

template<typename L, template<typename> class F >
struct erase_if_t
  : select_t< L, lambda< not_< F<_> >, 1 >::template apply >
{
  
};

}

#endif
