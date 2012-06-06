#include <iostream>

struct hello
{
  void operator()()
  {
     std::cout<<"hello";
  }
};

struct world
{
  void operator()()
  {
     std::cout<<" world!"<<std::endl;;
  }
};

template<typename H = hello, typename W = world>
class helloworld
{
public:
  void say()
  {
    H()();
    W()();
  }
};

int main()
{
  helloworld<> hw;
  hw.say();
  // out:
  // hello world!
  return 0;
}