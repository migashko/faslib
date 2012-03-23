#include "chain.hpp"
#include "chain_b.hpp"
#include "chain_c.hpp"
#include <fas/aop/aspect_merge.hpp>
#include <fas/aop/group.hpp>

struct _group_;

struct aspect: fas::aspect<
  fas::type_list_n<
    fas::alias<chain_a::_incoming_, chain_b::_input_>,
    fas::alias<chain_b::_output_, chain_a::_outgoing_>,
    fas::alias<chain_b::_incoming_, chain_c::_input_>,
    fas::alias<chain_c::_output_, chain_b::_outgoing_>,
    fas::alias<chain_c::_incoming_, chain_c::_outgoing_ >,
    
    fas::group<_group_, fas::type_list_n<chain_c::_chain1_, chain_c::_chain3_>::type >,
    fas::group<_group_, chain_a::_chain6_ >
  >::type
>
{};

int main()
{
  typedef chain< fas::aspect_merge<aspect, fas::aspect_merge<chain_c::aspect, chain_b::aspect>::type >::type > chain_class;
  chain_class c;
  c.doit(0);
  std::cout << "------------------" << std::endl;
  typedef chain_class::aspect::select_group<_group_>::type group_tags;
  c.get_aspect().get< fas::type_at_c<0, group_tags>::type >().show();
  c.get_aspect().get< fas::type_at_c<1, group_tags>::type >().show();
  c.get_aspect().get< fas::type_at_c<2, group_tags>::type >().show();
  std::cout << "-------_group_ getg-------" << std::endl;
  c.get_aspect().getg<_group_>()(c);
  std::cout << "-------_group_ get-------" << std::endl;
  c.get_aspect().get<_group_>()(c);
  //c.get_aspect().get< fas::type_at_c<3, group_tags>::type >().show();
  return 0;
};
