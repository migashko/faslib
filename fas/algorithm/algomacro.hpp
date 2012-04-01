#ifndef FAS_ALGORITHM_ALGOMACRO_HPP
#define FAS_ALGORITHM_ALGOMACRO_HPP


#ifdef FAS_ALGORITHM_LAMBDA_CAST
#include <fas/mp/lambda.hpp>
#endif // FAS_ALGORITHM_LAMBDA_CAST


//#ifdef FAS_ALGORITHM_SIMPLIFY
#include <fas/mp/simplify.hpp>
#define FAS_SIMPLIFY(F) ::fas::simplify<F>::type
#define FAS_T_SIMPLIFY(F) typename ::fas::simplify<F>::type
/*#else
#define FAS_SIMPLIFY(F) F
#define FAS_T_SIMPLIFY(F) F
#endif // FAS_ALGORITHM_SIMPLIFY
*/
#endif

