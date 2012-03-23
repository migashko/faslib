#include "chain.hpp"
#include "chain_c.hpp"
#include <fas/aop/aspect_merge.hpp>

struct aspect: fas::aspect<
  fas::type_list_n<
    fas::alias<chain_a::_incoming_, chain_c::_input_>,
    fas::alias<chain_c::_output_, chain_a::_outgoing_>,
    fas::alias<chain_c::_incoming_, chain_c::_outgoing_ >
  >::type
>
{};

int main()
{
  chain< fas::aspect_merge<aspect, chain_c::aspect >::type > c;
  c.doit(0);
  return 0;
};
