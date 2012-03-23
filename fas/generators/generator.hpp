// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_GENERATORS_GENERATOR_HPP
#define FAS_GENERATORS_GENERATOR_HPP

#include <fas/mp/apply.hpp>
#include <fas/algorithm/algomacro.hpp>

namespace fas{

template<typename T, template<typename> class F>
struct generator_t
{
  typedef T initial;
  typedef typename F<T>::type type;
  typedef generator_t< type, F > next;
};

template<typename T, typename F>
struct generator
{
  typedef T initial;
  //typedef typename simplify<F>::type simplified;
#ifndef FAS_ALGORITHM_LAMBDA_CAST
  typedef typename apply1< FAS_T_SIMPLIFY(F), initial>::type type;
  typedef generator< type, FAS_T_SIMPLIFY(F) > next;
#else
  typedef generator_t<T, lambda< FAS_T_SIMPLIFY(F)>::template apply > gt;
  typedef typename gt::type type;
  typedef typename gt::next next;
  //typedef typename lambda< FAS_T_SIMPLIFY(F)>::apply<initial>::type type;
#endif
  
};


}

#endif
