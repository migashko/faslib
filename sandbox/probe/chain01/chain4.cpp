#include "chain.hpp"
#include "chain_b.hpp"
#include "chain_c.hpp"


struct aspect: fas::aspect<
  fas::type_list_n<
    fas::alias<chain_b::_input_, chain_a::_incoming_>,
    fas::alias<chain_a::_outgoing_, chain_b::_output_ >,

    fas::alias<chain_c::_input_, chain_b::_incoming_>,
    fas::alias<chain_b::_outgoing_, chain_c::_output_>,

    fas::alias<chain_c::_outgoing_, chain_c::_incoming_>
  >::type
>
{};

int main()
{
  chain< 
    fas::aspect_merge<
      fas::aspect_merge<
        chain_b::aspect, 
        chain_c::aspect
      >::type, 
      aspect 
    >::type 
  > c;
  c.doit(0);
  return 0;
};
