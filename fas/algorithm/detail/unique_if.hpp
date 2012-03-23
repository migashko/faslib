//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_DETAIL_UNIQUE_IF_HPP
#define FAS_ALGORITHM_DETAIL_UNIQUE_IF_HPP

#include <fas/mp/apply.hpp>
#include <fas/mp/lambda.hpp>
#include <fas/static_check/verifying.hpp>
#include <fas/type_list/check_list.hpp>
#include <fas/type_list/metalist.hpp>
#include <fas/type_list/type_at_c.hpp>
#include <fas/type_list/merge.hpp>
#include <fas/type_list/split_c.hpp>
#include <fas/type_list/erase_c.hpp>
#include <fas/algorithm/count_if.hpp>

namespace fas{ namespace detail{

template<typename L, typename F, int P, int C>
struct unique_if_impl;
  
template<typename L, typename F, int P, int C, int B>
struct unique_if_impl2;
  
template<typename L, typename F>
struct unique_if_helper
  : unique_if_impl< L, F, 0, length<L>::value  >
{
};

template<typename L, typename F, int P, int C>
struct unique_if_impl
{
  typedef typename type_at_c< P, L>::type current;
  enum { value = count_if<L, typename lambda_r<F,2>::template apply<current, _1> >::value };
  typedef typename unique_if_impl2<L, F, P, C, (value > 1) >::type type;
};

template<typename L, typename F, int C>
struct unique_if_impl<L, F, C, C>
{
  typedef L type;
};

template<typename L, typename F, int P, int C, int B>
struct unique_if_impl2
{
  typedef typename erase_c<P, L>::type erased;
  typedef typename unique_if_impl<erased, F, P, C-1>::type type;
};

template<typename L, typename F, int P, int C>
struct unique_if_impl2<L, F, P, C, false>
{
  typedef typename unique_if_impl<L, F, P+1, C>::type type;
};


/// /////////////////////////////////////////////////

template<typename L, template<typename, typename> class F, int P, int C>
struct unique_if_impl_t;
  
template<typename L, template<typename, typename> class F, int P, int C, int B>
struct unique_if_impl2_t;
  
template<typename L, template<typename, typename> class F>
struct unique_if_helper_t
  : unique_if_impl_t< L, F, 0, length<L>::value  >
{
};

template<typename L, template<typename, typename> class F, int P, int C>
struct unique_if_impl_t
{
  typedef typename type_at_c< P, L>::type current;
  enum { value = count_if_t<L, bind1st<F, current>::template apply >::value };
  typedef typename unique_if_impl2_t<L, F, P, C, (value > 1) >::type type;
};

template<typename L, template<typename, typename> class F, int C>
struct unique_if_impl_t<L, F, C, C>
{
  typedef L type;
};

template<typename L, template<typename, typename> class F, int P, int C, int B>
struct unique_if_impl2_t
{
  typedef typename erase_c<P, L>::type erased;
  typedef typename unique_if_impl_t<erased, F, P, C-1>::type type;
};

template<typename L, template<typename, typename> class F, int P, int C>
struct unique_if_impl2_t<L, F, P, C, false>
{
  typedef typename unique_if_impl_t<L, F, P+1, C>::type type;
};


  /*
template<int P, typename L, typename F>
struct unique_if_impl;

template<typename MT, int P, typename L, typename F>
struct unique_if_impl1;

template<int P, typename L, int, typename F>
struct unique_if_impl2;

#ifdef FASLIB_TYPE_LIST_CHECK

template<typename L, typename F>
struct unique_if_verifying;

template<typename L, typename F>
struct unique_if_helper
  : verifying< unique_if_verifying<L, F>, check_list<L> >::type
{
};

template<typename L, typename F>
struct unique_if_verifying
  : unique_if_impl<typename L::metatype, 0, L, F>
{
};

#else

template<typename L, typename F>
struct unique_if_helper
  : unique_if_impl<typename L::metatype, 0, L, F>
{
};

#endif



template<int P, typename L, typename F>
struct unique_if_impl<metalist::type_list, P, L, F>
{
  typedef typename type_at_c< P, L>::type current;
  //typedef typename unique_if_impl2< P, L, (count_if<L, typename apply<F, current>::type >::value > 1), F >::type type;
  typedef typename unique_if_impl2< P, L, (count_if<L, typename lambda<F>::template apply<current, _1> >::value > 1), F >::type type;
};

template<int P, typename L, typename F>
struct unique_if_impl<metalist::empty_list, P, L, F>
{
  typedef L type;
};

template<int P,typename L, int, typename F>
struct unique_if_impl2
{
  typedef typename erase_c<P, L>::type erased;
  typedef typename type_at_c<P, L>::tail tail;
  typedef typename unique_if_impl<typename tail::metatype, P, erased, F>::type type;
};

template<int P,typename L, typename F>
struct unique_if_impl2<P, L, false, F>
{
  typedef typename type_at_c< P, L>::tail tail;
  typedef typename unique_if_impl<typename tail::metatype, P + 1, L, F>::type type;
};
*/

}}


#endif
