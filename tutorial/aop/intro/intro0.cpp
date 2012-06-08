#include <iostream>

class isay
{
public:
  virtual ~isay(){}
  virtual void say() = 0;
};

class judge_dredd
  : public isay
{
public:
  
  virtual ~judge_dredd()
  {
  }
  
  virtual void say()
  {
    one();
    two();
    three();
    strike();
  }
  
protected:
  
  virtual void one()    {  std::cout<<"one, ";   }
  virtual void two()    {  std::cout<<"two, ";   }
  virtual void three()  {  std::cout<<"three, "; }
  virtual void strike() {  std::cout<<"strike!"; }
};

class judge_jon:
  public virtual judge_dredd
{
protected:
  virtual void one()
  {
    std::cout<<"ONE, ";
  }
};

class judge_bob:
  public virtual judge_dredd
{
protected:
  virtual void three()
  {
    std::cout<<"three, ";
    three1();
    three2();
    three3();
  }

  virtual void three1() { std::cout<<"three and 0.5, "; }
  virtual void three2() { std::cout<<"three and 0.75, "; }
  virtual void three3() { std::cout<<"three and 0.99, "; }
};

class judge_sam:
  public virtual judge_jon,
  public virtual judge_bob
{
public:
  
};

int main()
{
  judge_dredd dredd;
  std::cout << "Dredd: ";
  dredd.say();
  std::cout << std::endl;

  judge_jon jon;
  std::cout << "Jon: ";
  jon.say();
  std::cout << std::endl;

  judge_bob bob;
  std::cout << "Bob: ";
  bob.say();
  std::cout << std::endl;

  judge_sam sam;
  std::cout << "Sam: ";
  sam.say();
  std::cout << std::endl;

  return 0;
}
