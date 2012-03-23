#include <iostream>

class helloworld
{
public:
  virtual void hello()
  {
    std::cout<<"hello";
  }

  virtual void world() 
  {
    std::cout<<" world!"<<std::endl;
  }

  void say()
  {
    hello();
    world();
  }
};

int main()
{
  helloworld hw;
  hw.say();
  // out:
  // hello world!
  return 0;
}