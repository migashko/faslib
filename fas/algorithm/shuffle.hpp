//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_SHUFFLE_HPP
#define FAS_ALGORITHM_SHUFFLE_HPP

#include <fas/mp/placeholders.hpp>
//#include <fas/utility.hpp>
#include <fas/integral/less.hpp>
#include <fas/algorithm/transform.hpp>
#include <fas/algorithm/transform2.hpp>
#include <fas/algorithm/sort.hpp>
#include <fas/typemanip/second.hpp>
#include <fas/typemanip/first.hpp>
#include <fas/typemanip/pair.hpp>

namespace fas{

  /*
#ifndef FAS_ALGORITHM_LAMBDA_CAST

template<typename L, typename RL>
struct shuffle
{
  typedef typename transform2< RL, L, pair<_1, _2> >::type pair_list;
  typedef typename sort< pair_list, less< first<_1>, first<_2> > >::type sorted_list;
  typedef typename transform< sorted_list, second<_1> >::type type;
};

#else*/

namespace detail
{
  template<typename L, typename R>
  struct shuffle_less_first;
  
  template<typename LF, typename RF, typename LS, typename RS>
  struct shuffle_less_first< pair<LF, RF>, pair<LS, RS> >
    : less<LF, LS>
  {};
  
}

template<typename L, typename RL>
struct shuffle
{
  typedef typename transform2_t< RL, L, make_pair >::type pair_list;
  typedef typename sort_t< pair_list, detail::shuffle_less_first >::type sorted_list;
  typedef typename transform_t< sorted_list, second >::type type;
};

//#endif


}


#endif
