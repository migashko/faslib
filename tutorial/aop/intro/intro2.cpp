#include <iostream>

/// Интерфейсы стратегий

struct ione
{
  virtual ~ione() {};
  virtual void one() = 0;
  virtual ione* clone() = 0;
};

struct itwo
{
  virtual ~itwo() {};
  virtual void two() = 0;
  virtual itwo* clone() = 0;
};

struct ithree
{
  virtual ~ithree() {};
  virtual void three() = 0;
  virtual ithree* clone() = 0;
};

struct istrike
{
  virtual ~istrike() {};
  virtual void strike() = 0;
  virtual istrike* clone() = 0;
};

/// Реализация стратегий 

struct say_one: ione
{
  virtual ~say_one() {};
  virtual void one() {  std::cout<<"one, "; };
  virtual ione* clone() { return new say_one; };
};

struct say_two: itwo
{
  virtual ~say_two() {};
  virtual void two() {  std::cout<<"two, "; }
  virtual itwo* clone() { return new say_two; };
};

struct say_three: ithree
{
  virtual ~say_three() {};
  virtual void three() {  std::cout<<"three, "; }
  virtual ithree* clone() { return new say_three; };
};

struct say_strike: istrike
{
  virtual ~say_strike() {};
  virtual void strike() {  std::cout<<"strike!"; }
  virtual istrike* clone() { return new say_strike; };
};

/// Собственно класс судьи Дредда

class judge_dredd
{
public:

  virtual ~judge_dredd()
  {
    delete _one;
    delete _two;
    delete _three;
    delete _strike;
  }

  judge_dredd()
    : _one(new say_one)
    , _two(new say_two)
    , _three(new say_three)
    , _strike(new say_strike)
  {}

  judge_dredd(const judge_dredd& jd)
    : _one(0)
    , _two(0)
    , _three(0)
    , _strike(0)
  {
    this->set_one( jd._one->clone() );
    this->set_two( jd._two->clone() );
    this->set_three( jd._three->clone() );
    this->set_strike( jd._strike->clone() );
  }

  judge_dredd& operator = (const judge_dredd& jd)
  {
    this->set_one( jd._one->clone() );
    this->set_two( jd._two->clone() );
    this->set_three( jd._three->clone() );
    this->set_strike( jd._strike->clone() );
    return *this;
  }

  virtual void say()
  {
    _one->one();
    _two->two();
    _three->three();
    _strike->strike();
  }

  void set_one(ione* one)
  {
    delete _one;
    _one = one;
  }

  void set_two(itwo* two)
  {
    delete _two;
    _two = two;
  }
  
  void set_three(ithree* three)
  {
    delete _three;
    _three = three;
  }
  
  void set_strike(istrike* strike)
  {
    delete _strike;
    _strike = strike;
  }
  
private:
  ione* _one;
  itwo* _two;
  ithree* _three;
  istrike* _strike;
};

/// Стратегия для Джона

struct say_ONE: ione
{
  virtual ~say_ONE() {};
  virtual void one() {  std::cout<<"ONE, "; };
  virtual ione* clone() { return new say_ONE; };
};

/// Интерфейсы стратегий для three, three and 0.5, three and 0.75, three and 0.99

struct ithree1
{
  virtual ~ithree1() {};
  virtual void three1() = 0;
  virtual ithree1* clone() = 0;
};

struct ithree2
{
  virtual ~ithree2() {};
  virtual void three2() = 0;
  virtual ithree2* clone() = 0;
};

struct ithree3
{
  virtual ~ithree3() {};
  virtual void three3() = 0;
  virtual ithree3* clone() = 0;
};

struct say_three1: ithree1
{
  virtual ~say_three1() {};
  virtual void three1() {  std::cout<<"three and 0.5, "; }
  virtual ithree1* clone() { return new say_three1; };
};

struct say_three2: ithree2
{
  virtual ~say_three2() {};
  virtual void three2() {  std::cout<<"three and 0.75, "; }
  virtual ithree2* clone() { return new say_three2; };
};

struct say_three3: ithree3
{
  virtual ~say_three3() {};
  virtual void three3() {  std::cout<<"three and 0.99, "; }
  virtual ithree3* clone() { return new say_three3; };
};

/// Cтратегий для three

class say_soft_three
  : public ithree
{
public:

  virtual ~say_soft_three()
  {
    delete _three1;
    delete _three2;
    delete _three3;
  }

  say_soft_three()
    : _three1(new say_three1)
    , _three2(new say_three2)
    , _three3(new say_three3)
  {}

  say_soft_three(const say_soft_three& jd)
    : _three1(0)
    , _three2(0)
    , _three3(0)
  {
    this->set_three1( jd._three1->clone() );
    this->set_three2( jd._three2->clone() );
    this->set_three3( jd._three3->clone() );
  }

  say_soft_three& operator = (const say_soft_three& jd)
  {
    this->set_three1( jd._three1->clone() );
    this->set_three2( jd._three2->clone() );
    this->set_three3( jd._three3->clone() );
    return *this;
  }

  ithree* clone()
  {
    return new say_soft_three(*this);
  }

  virtual void three()
  {
    std::cout<<"three, ";
    this->say();
  }

  virtual void say()
  {
    _three1->three1();
    _three2->three2();
    _three3->three3();
  }

  void set_three1(ithree1* three1)
  {
    delete _three1;
    _three1 = three1;
  }

  void set_three2(ithree2* three2)
  {
    delete _three2;
    _three2 = three2;
  }

  void set_three3(ithree3* three3)
  {
    delete _three3;
    _three3 = three3;
  }

private:
  ithree1* _three1;
  ithree2* _three2;
  ithree3* _three3;
};

int main()
{
  judge_dredd dredd;
  std::cout << "Dredd: ";
  dredd.say();
  std::cout << std::endl;
  
  judge_dredd jon;
  jon.set_one(new say_ONE);
  std::cout << "Jon: ";
  jon.say();
  std::cout << std::endl;

  judge_dredd bob;
  bob.set_three(new say_soft_three);
  std::cout << "Bob: ";
  bob.say();
  std::cout << std::endl;
  
  judge_dredd sam;
  sam.set_one(new say_ONE);
  sam.set_three(new say_soft_three);
  std::cout << "Sam: ";
  sam.say();
  std::cout << std::endl;

  return 0;
}
