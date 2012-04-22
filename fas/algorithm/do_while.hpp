//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_DO_WHILE_HPP
#define FAS_ALGORITHM_DO_WHILE_HPP

#include <fas/algorithm/detail/do_while.hpp>
#include <fas/algorithm/algomacro.hpp>
#include <fas/mp/lambda.hpp>

namespace fas{

template<typename I, typename F, typename P >
struct do_while
{
  typedef typename detail::do_while_helper_t<
    FAS_T_SIMPLIFY(I),
    lambda< FAS_T_SIMPLIFY(F) >::template apply,
    lambda< FAS_T_SIMPLIFY(P) >::template apply
  >::type type;
};

template<typename I, template<typename> class F, template<typename> class  P >
struct do_while_t
{
  typedef typename detail::do_while_helper_t<
    I, F, P
  >::type type;
};

}

#endif
