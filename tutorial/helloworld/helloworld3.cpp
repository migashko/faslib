#include "helloworld.hpp"
#include "helloworld2_aspect.hpp"
#include "helloworld3_aspect.hpp"


int main()
{
  helloworld< helloworld3_aspect > hw;
  hw.say();

  helloworld< aspect_merge<helloworld3_aspect, helloworld2_aspect>::type > hw2;
  hw2.say();

  // out:
  // Hello Super world!
  // Hello Super World!

  return 0;
}