//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_GENERATOR_HPP
#define FAS_ALGORITHM_GENERATOR_HPP

#include <fas/mp/apply.hpp>
#include <fas/mp/lambda.hpp>
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
  typedef generator_t<T, lambda< FAS_T_SIMPLIFY(F)>::template apply > gt;
  typedef typename gt::type type;
  typedef typename gt::next next;
};


}

#endif
