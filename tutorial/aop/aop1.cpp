#include <iostream>

class dredd
{
  // ...
public:
  void dredd_say() const
  {
    this->one();
    this->two();
    this->three();
    this->strike();
  }

private:
  void one() const   {  std::cout<<"one, ";   }
  void two() const   {  std::cout<<"two, ";   }
  void three() const {  std::cout<<"three, "; }
  void strike() const {  std::cout<<"strike!"; }
};

int main()
{
  dredd d;
  std::cout << "Dredd: ";
  d.dredd_say();
  std::cout << std::endl;

  return 0;
}
