#include <iostream>

class dredd
{
  // ...
public:

  void dredd_say()
  {
    this->say();
  }

protected:

  virtual void say()
  {
    this->one();
    this->two();
    this->three();
    this->strike();
  }

  virtual void one()    {  std::cout<<"one, ";   }
  virtual void two()    {  std::cout<<"two, ";   }
  virtual void three()  {  std::cout<<"three, "; }
  virtual void strike() {  std::cout<<"strike!"; }
};

class jon:
  protected virtual dredd
{
  // ...
public:

  void jon_say()
  {
    dredd::say();
  }

protected:

  virtual void one()
  {
    std::cout<<"ONE, ";
  }
};

class bob:
  protected virtual dredd
{
  // ...
public:

  void bob_say()
  {
    this->say();
  }

protected:

  virtual void say()
  {
    dredd::say();
    four();
    five();
    six();
    seven();
  }

  virtual void four()  { std::cout<<"four, "; }
  virtual void five()  { std::cout<<"five, "; }
  virtual void six()   { std::cout<<"six, "; }
  virtual void seven() { std::cout<<"seven!"; }
  virtual void strike(){ }
};

class sam:
  protected virtual jon,
  protected virtual bob
{
  // ...
public:
  void sam_say()
  {
    bob::say();
  }
};

int main()
{
  dredd d;
  std::cout << "Dredd: ";
  d.dredd_say();
  std::cout << std::endl;

  jon j;
  std::cout << "Jon: ";
  j.jon_say();
  std::cout << std::endl;

  bob b;
  std::cout << "Bob: ";
  b.bob_say();
  std::cout << std::endl;

  sam s;
  std::cout << "Sam: ";
  s.sam_say();
  std::cout << std::endl;

  return 0;
}
