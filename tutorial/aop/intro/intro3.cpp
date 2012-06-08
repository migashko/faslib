#include <iostream>

class isay
{
public:
  virtual ~isay(){}
  virtual void say() = 0;
};


struct say_one
{
  void one() {  std::cout<<"one, "; };
};

struct say_two
{
  void two() {  std::cout<<"two, "; }
};

struct say_three
{
  void three() {  std::cout<<"three, "; }
};

struct say_strike
{
  void strike() {  std::cout<<"strike!"; }
};


template<
  typename One = say_one,
  typename Two = say_two,
  typename Three = say_three,
  typename Strike  = say_strike>
class judge_dredd
  : public isay
{
public:
  virtual void say()
  {
    _one.one();
    _two.two();
    _three.three();
    _strike.strike();
  }
  
private:
  One _one;
  Two _two;
  Three _three;
  Strike _strike;
};

/// /////////////////////////////////////////////////

struct say_ONE
{
  void one() {  std::cout<<"ONE, "; };
};

/// /////////////////////////////////////////////////

struct say_three1
{
  void three1() {  std::cout<<"three and 0.5, "; }
};

struct say_three2
{
  void three2() {  std::cout<<"three and 0.75, "; }
};

struct say_three3
{
  void three3() {  std::cout<<"three and 0.99, "; }
};

template<
  typename Three1 = say_three1,
  typename Three2 = say_three2,
  typename Three3 = say_three3
>
class say_soft_three
{
public:

  void three()
  {
    std::cout<<"three, ";
    this->say();
  }

  void say()
  {
    _three1.three1();
    _three2.three2();
    _three3.three3();
  }

private:
  Three1 _three1;
  Three2 _three2;
  Three3 _three3;
};

int main()
{
  judge_dredd<> dredd;
  std::cout << "Dredd: ";
  dredd.say();
  std::cout << std::endl;

  judge_dredd<say_ONE> jon;
  std::cout << "Jon: ";
  jon.say();
  std::cout << std::endl;
  
  judge_dredd<say_one, say_two, say_soft_three<> > bob;
  std::cout << "Bob: ";
  bob.say();
  std::cout << std::endl;

  judge_dredd<say_ONE, say_two, say_soft_three<> > sam;
  std::cout << "Sam: ";
  sam.say();
  std::cout << std::endl;

  return 0;
}
