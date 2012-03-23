#include "chain.hpp"

int main()
{
  chain< fas::aspect< fas::alias< chain_a::_outgoing_, chain_a::_incoming_ > > > c;
  c.doit(0);
  return 0;
};
