#include <iostream>

class dredd
{
public:
  
  /* other dredd code */
  
  void dredd_say()
  {
    this->one();
    this->two();
    this->three();
    this->strike();
  }
  
protected:
  
  virtual void one()    {  std::cout<<"one, ";   }
  virtual void two()    {  std::cout<<"two, ";   }
  virtual void three()  {  std::cout<<"three, "; }
  virtual void strike() {  std::cout<<"strike!"; }
};

class jon:
  public virtual dredd
{
public:
  void jon_say()
  {
    dredd::dredd_say();
  }
protected:
  virtual void one()
  {
    std::cout<<"ONE, ";
  }
};

class bob:
  public virtual dredd
{
public:
  void bob_say()
  {
    dredd::dredd_say();
  }

protected:
  virtual void strike()
  {
    std::cout<<"four, ";
    five();
    six();
    seven();
  }

  virtual void five() { std::cout<<"five, "; }
  virtual void six() { std::cout<<"six, "; }
  virtual void seven() { std::cout<<"seven!"; }
};

class sam:
  public virtual jon,
  public virtual bob
{
public:
  void sam_say()
  {
    dredd::dredd_say();
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
