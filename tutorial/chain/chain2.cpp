#include "chain.hpp"
#include "chain_b.hpp"
#include <fas/aop/aspect_merge.hpp>

struct aspect: fas::aspect<
  fas::type_list_n<
    fas::alias<chain_a::_incoming_, chain_b::_input_>,
    fas::alias<chain_b::_output_, chain_a::_outgoing_>,
    fas::alias<chain_b::_incoming_, chain_b::_outgoing_ >
  >::type
>
{};

int main()
{
  chain< fas::aspect_merge<aspect, chain_b::aspect >::type > c;
  c.doit(0);
  return 0;
};
