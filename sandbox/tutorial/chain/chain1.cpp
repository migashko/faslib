#include "chain.hpp"

int main()
{
  chain< fas::aspect< fas::alias< chain_a::_incoming_, chain_a::_outgoing_ > > > c;
  c.doit(0);
  return 0;
};