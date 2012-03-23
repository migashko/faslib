#include "helloworld.hpp"

#include "helloworld4_aspect.hpp"
#include "helloworld2_aspect.hpp"
//#include "helloworld3_aspect.hpp"


int main()
{
  helloworld< helloworld4_aspect > hw;
  hw.say();

  helloworld< fas::aspect_merge<helloworld4_aspect, helloworld2_aspect>::type > hw2;
  hw2.say();

  //helloworld< fas::aspect_merge<helloworld4_aspect, helloworld3_aspect>::type > hw3;
  //hw3.say();

  // out:
  // Hello Mega Super world!
  // Hello Mega Super World!
  return 0;
}