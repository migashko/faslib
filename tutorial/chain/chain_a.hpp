#ifndef CHAIN_AD_CHAIN_A_HPP
#define CHAIN_AD_CHAIN_A_HPP

#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/alias.hpp>
#include <fas/aop/stub.hpp>
#include <fas/type_list/type_list_n.hpp>
#include "ad_chain.hpp"

namespace chain_a{

struct _input_;
struct _incoming_;
struct _outgoing_;
struct _output_;

struct _chain1_;
struct _chain2_;
struct _chain3_;

struct _chain4_;
struct _chain5_;
struct _chain6_;

struct chain1_advice: fas::advice< _chain1_, ad_chain<'A', 1, _chain2_> > {};
struct chain2_advice: fas::advice< _chain2_, ad_chain<'A', 2, _chain3_> > {};
struct chain3_advice: fas::advice< _chain3_, ad_chain<'A', 3, _incoming_> > {};

struct chain4_advice: fas::advice< _chain4_, ad_chain<'A', 4, _chain5_> > {};
struct chain5_advice: fas::advice< _chain5_, ad_chain<'A', 5, _chain6_> > {};
struct chain6_advice: fas::advice< _chain6_, ad_chain<'A', 6, _output_> > {};

struct advice_list
  : fas::type_list_n<
      fas::alias<_input_, _chain1_>,
      fas::alias<_outgoing_, _chain4_>,
      chain1_advice,
      chain2_advice,
      chain3_advice,
      chain4_advice,
      chain5_advice,
      chain6_advice,
      fas::stub<_incoming_>,
      fas::stub<_output_>
    >::type
{};

struct aspect: fas::aspect<advice_list>{};


/*
typedef fas::advice< _chain1_, ad_chain<'A', 1, _chain2_> > chain1_advice;
typedef fas::advice< _chain2_, ad_chain<'A', 2, _chain3_> > chain2_advice;
typedef fas::advice< _chain3_, ad_chain<'A', 3, _incoming_> > chain3_advice;

typedef fas::advice< _chain4_, ad_chain<'A', 4, _chain5_> > chain4_advice;
typedef fas::advice< _chain5_, ad_chain<'A', 5, _chain6_> > chain5_advice;
typedef fas::advice< _chain6_, ad_chain<'A', 6, _output_> > chain6_advice;

typedef fas::type_list_n<
      fas::alias<_input_, _chain1_>,
      fas::alias<_outgoing_, _chain4_>,
      chain1_advice,
      chain2_advice,
      chain3_advice,
      chain4_advice,
      chain5_advice,
      chain6_advice,
      fas::stub<_incoming_>,
      fas::stub<_output_>
    >::type
advice_list;

typedef fas::aspect<advice_list> aspect;
*/

}

#endif
