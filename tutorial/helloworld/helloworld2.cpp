#include "helloworld.hpp"
#include "helloworld2_aspect.hpp"


int main()
{
  helloworld< helloworld2_aspect > hw;
  hw.say();
  // out:
  // hello World!
  return 0;
}