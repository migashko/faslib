//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_DETAIL_DO_WHILE_HPP
#define FAS_ALGORITHM_DETAIL_DO_WHILE_HPP

#include <fas/mp/apply.hpp>

namespace fas{ namespace detail{

template<typename I, template<typename> class F, template<typename> class P, int B >
struct do_while_impl_t;

template<typename I, template<typename> class F, template<typename> class P >
struct do_while_helper_t
{
  typedef typename P<I>::type condition;
  typedef do_while_impl_t< I, F, P, condition::value > impl_type;
  typedef typename impl_type::type type;
  enum { value = impl_type::value };
};

template<typename I, template<typename> class F, template<typename> class P, int B >
struct do_while_impl_t
{
  typedef typename F< I >::type intermediate_type;
  typedef do_while_helper_t<intermediate_type, F, P> helper;
  typedef typename helper::type type;
  enum { value = 1 + helper::value };
};


template<typename I, template<typename> class F, template<typename> class P >
struct do_while_impl_t<I, F, P, false>
{
  enum { value = 0 };
  typedef I type;
};

}}


#endif
