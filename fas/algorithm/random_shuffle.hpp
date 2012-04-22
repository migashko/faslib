//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_RANDOM_SHUFFLE_HPP
#define FAS_ALGORITHM_RANDOM_SHUFFLE_HPP

#include <fas/algorithm/generate_c.hpp>
#include <fas/algorithm/shuffle.hpp>
#include <fas/algorithm/algomacro.hpp>

#include <fas/mp/placeholders.hpp>

#include <fas/type_list/length.hpp>
#include <fas/type_list/type_list.hpp>
#include <fas/type_list/empty_list.hpp>

#include <fas/generators/generator.hpp>

#include <fas/integral/rand.hpp>

namespace fas{

template<typename R, typename L>
struct random_shuffle
{
  typedef typename generate_c< 
    length<L>::value,
    generator_t< FAS_T_SIMPLIFY(R), rand >
  >::type rand_list;

  typedef typename shuffle< L, rand_list>::type type;
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename R, typename LL, typename RR>
struct random_shuffle<R, type_list<LL, RR> >
{
  typedef typename generate_c< 
    length< RR >::value + 1,
    generator_t< FAS_T_SIMPLIFY(R), rand >
  >::type rand_list;

  typedef typename shuffle< type_list<LL, RR>, rand_list>::type type;
};

template<typename R, typename LL>
struct random_shuffle<R, type_list<LL, empty_list> >
{
  typedef type_list<LL, empty_list> type;
};

template<typename R>
struct random_shuffle<R, empty_list >
{
  typedef empty_list type;
};

#endif
}

#endif
