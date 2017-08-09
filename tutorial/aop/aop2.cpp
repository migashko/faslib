#include <iostream>

class dredd
{
  // ...
public:

  void dredd_say() const
  {
    this->say();
  }

protected:

  virtual void say() const
  {
    this->one();
    this->two();
    this->three();
    this->strike();
  }

  virtual void one() const    {  std::cout<<"one, ";   }
  virtual void two() const   {  std::cout<<"two, ";   }
  virtual void three() const  {  std::cout<<"three, "; }
  virtual void strike() const{  std::cout<<"strike!"; }
};

class jon:
  protected virtual dredd
{
  // ...
public:

  void jon_say() const
  {
    dredd::say();
  }

protected:

  virtual void one() const
  {
    std::cout<<"ONE, ";
  }
};

class bob:
  protected virtual dredd
{
  // ...
public:

  void bob_say() const
  {
    this->say();
  }

protected:

  virtual void say() const
  {
    dredd::say();
    four();
    five();
    six();
    seven();
  }

  virtual void four() const  { std::cout<<"four, "; }
  virtual void five() const { std::cout<<"five, "; }
  virtual void six() const  { std::cout<<"six, "; }
  virtual void seven() const{ std::cout<<"seven!"; }
  virtual void strike() const{ }
};

class sam:
  protected virtual jon,
  protected virtual bob
{
  // ...
public:
  void sam_say() const
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
