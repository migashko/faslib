#include <iostream>

class dredd
{
  // ...
public:
  
  void dredd_say()
  {
    std::cout << "one, two, three, strike!";
  }
};

int main()
{
  dredd d;
  std::cout << "Dredd: ";
  d.dredd_say();
  std::cout << std::endl;

  return 0;
}
