//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011, 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_DETAIL_FOR__HPP
#define FAS_ALGORITHM_DETAIL_FOR__HPP

#include <fas/mp/apply.hpp>

namespace fas{ namespace detail{

template<typename I, template<typename> class C, template<typename> class F, int B >
struct for_impl1_t;

template<typename I, template<typename> class C , template<typename> class F>
struct for_impl_t
{
  typedef typename C<I>::type condition;
  typedef for_impl1_t< I, C, F, condition::value > impl_type;
  typedef typename impl_type::type type;
  enum { value = impl_type::value };
};

template<typename I, template<typename> class C, template<typename> class F, int B >
struct for_impl1_t
{
  typedef typename F< I >::type intermediate_type;
  typedef for_impl_t<intermediate_type, C, F> helper;
  typedef typename helper::type type;
  enum { value = 1 + helper::value };
};


template<typename I, template<typename> class C, template<typename> class F>
struct for_impl1_t<I, C, F, false>
{
  enum { value = 0 };
  typedef I type;
};

}}


#endif
