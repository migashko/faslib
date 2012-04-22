//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_ALGOMACRO_HPP
#define FAS_ALGORITHM_ALGOMACRO_HPP

#ifdef FAS_ALGORITHM_SIMPLIFY
#include <fas/mp/simplify.hpp>
#define FAS_SIMPLIFY(F) ::fas::simplify<F>::type
#define FAS_T_SIMPLIFY(F) typename ::fas::simplify<F>::type
#else
#define FAS_SIMPLIFY(F) F
#define FAS_T_SIMPLIFY(F) F
#endif // FAS_ALGORITHM_SIMPLIFY

#endif

