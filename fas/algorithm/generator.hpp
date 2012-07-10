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
  typedef T type;
  typedef typename F<T>::type next_type;
  typedef generator_t< next_type, F > next;
};

template<typename T, typename F>
struct generator
{
  typedef T type;
  typedef generator_t<T, lambda< FAS_T_SIMPLIFY(F)>::template apply > gt;
  typedef typename gt::next_type next_type;
  typedef typename gt::next next;
};


}

#endif
