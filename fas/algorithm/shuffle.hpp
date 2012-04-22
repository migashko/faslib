//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_SHUFFLE_HPP
#define FAS_ALGORITHM_SHUFFLE_HPP

#include <fas/algorithm/transform.hpp>
#include <fas/algorithm/transform2.hpp>
#include <fas/algorithm/sort.hpp>

#include <fas/mp/placeholders.hpp>
#include <fas/mp/lambda.hpp>

#include <fas/typemanip/second.hpp>
#include <fas/typemanip/first.hpp>
#include <fas/typemanip/make_pair.hpp>

#include <fas/integral/less.hpp>

namespace fas{

template<typename L, typename RL>
struct shuffle
{
  typedef typename transform2_t< RL, L, make_pair >::type pair_list;
  
  typedef typename sort_t<
    pair_list, 
    lambda< 
      less<
        first<_1>,
        first<_2> 
      > 
    >::template apply
  >::type sorted_list;
  
  typedef typename transform_t< sorted_list, second >::type type;
};

}


#endif
