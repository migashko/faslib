#include <iostream>

class dredd
{
  // ...
public:
  // cppcheck-suppress functionStatic
  void dredd_say() const
  {
    this->one();
    this->two();
    this->three();
    this->strike();
  }

private:
  // cppcheck-suppress functionStatic
  void one() const   {  std::cout<<"one, ";   }
  // cppcheck-suppress functionStatic
  void two() const   {  std::cout<<"two, ";   }
  // cppcheck-suppress functionStatic
  void three() const {  std::cout<<"three, "; }
  // cppcheck-suppress functionStatic
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
