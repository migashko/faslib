#ifndef CHAIN_AD_CHAIN_C_HPP
#define CHAIN_AD_CHAIN_C_HPP

#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/adv/ad_stub.hpp>
#include <fas/type_list.hpp>
#include "ad_chain.hpp"

namespace chain_c{

namespace aa = ::fas::aop;
namespace ap = ::fas::pattern;
namespace ad = ::fas::adv;

struct _input_{};
struct _incoming_{};
struct _outgoing_{};
struct _output_{};

struct _chain1_{};
struct _chain2_{};
struct _chain3_{};

struct _chain4_{};
struct _chain5_{};
struct _chain6_{};

typedef fas::tag_list_n<_chain1_,_chain2_,_chain3_,_chain4_,_chain5_,_chain6_>::type temp_tags;
struct chainTemp_advice: fas::advice< temp_tags, ad_chain<'C', 1, _chain2_> > {};
struct chain1_advice: fas::advice< _chain1_, ad_chain<'C', 1, _chain2_> > {};
struct chain2_advice: fas::advice< _chain2_, ad_chain<'C', 2, _chain3_> > {};
struct chain3_advice: fas::advice< _chain3_, ad_chain<'C', 3, _incoming_> > {};

struct chain4_advice: fas::advice< _chain4_, ad_chain<'C', 4, _chain5_> > {};
struct chain5_advice: fas::advice< _chain5_, ad_chain<'C', 5, _chain6_> > {};
struct chain6_advice: fas::advice< _chain6_, ad_chain<'C', 6, _output_> > {};

struct advice_list
  : fas::type_list_n<
      //chainTemp_advice,
      fas::type_list_n<
      fas::alias<_chain1_, _input_>,
      fas::alias<_chain4_, _outgoing_>,
      chain1_advice,
      chain2_advice,
      chain3_advice,
      chain4_advice,
      chain5_advice,
      chain6_advice,
      fas::advice<_incoming_, ad::ad_stub<> >,
      fas::advice<_output_, ad::ad_stub<> >
      >::type
    >::type
{};

struct aspect: fas::aspect<advice_list>{};

}

#endif
