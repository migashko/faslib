//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_DETAIL_UNIQUE_IF_HPP
#define FAS_ALGORITHM_DETAIL_UNIQUE_IF_HPP

#include <fas/mp/bind1st.hpp>
#include <fas/static_check/verifying.hpp>
#include <fas/type_list/type_at_c.hpp>
#include <fas/type_list/erase_c.hpp>
#include <fas/algorithm/count_if.hpp>

namespace fas{ namespace detail{

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


}}


#endif
