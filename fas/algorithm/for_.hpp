//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_FOR__HPP
#define FAS_ALGORITHM_FOR__HPP

#include <fas/algorithm/detail/for_.hpp>
#include <fas/algorithm/algomacro.hpp>
#include <fas/mp/lambda.hpp>

namespace fas{

template<typename I, typename C, typename F >
struct for_
{
  typedef typename detail::for_impl_t<
    FAS_T_SIMPLIFY(I),
    lambda< FAS_T_SIMPLIFY(C), 1 >::template apply,
    lambda< FAS_T_SIMPLIFY(F), 1 >::template apply
  >::type type;
};

template<typename I, template<typename> class  C, template<typename> class F >
struct for_t
{
  typedef typename detail::for_impl_t<
    I, C, F
  >::type type;
};

}

#endif
