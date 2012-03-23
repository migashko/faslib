#include "helloworld.hpp"

int main()
{
  helloworld<> hw;
  hw.say();
  // out:
  // hello world!
  return 0;
}