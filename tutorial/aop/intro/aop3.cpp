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

class dredd
{
public:

  virtual ~dredd()
  {
    delete _one;
    delete _two;
    delete _three;
    delete _strike;
  }

  dredd()
    : _one(new say_one)
    , _two(new say_two)
    , _three(new say_three)
    , _strike(new say_strike)
  {}

  dredd(const dredd& jd)
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

  dredd& operator = (const dredd& jd)
  {
    this->set_one( jd._one->clone() );
    this->set_two( jd._two->clone() );
    this->set_three( jd._three->clone() );
    this->set_strike( jd._strike->clone() );
    return *this;
  }

  virtual void dredd_say()
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

struct ifive
{
  virtual ~ifive() {};
  virtual void five() = 0;
  virtual ifive* clone() = 0;
};

struct isix
{
  virtual ~isix() {};
  virtual void six() = 0;
  virtual isix* clone() = 0;
};

struct iseven
{
  virtual ~iseven() {};
  virtual void seven() = 0;
  virtual iseven* clone() = 0;
};

struct say_five: ifive
{
  virtual ~say_five() {};
  virtual void five() {  std::cout<<"five"; }
  virtual ifive* clone() { return new say_five; };
};

struct say_six: isix
{
  virtual ~say_six() {};
  virtual void six() {  std::cout<<"six, "; }
  virtual isix* clone() { return new say_six; };
};

struct say_seven: iseven
{
  virtual ~say_seven() {};
  virtual void seven() {  std::cout<<"seven, "; }
  virtual iseven* clone() { return new say_seven; };
};

/// Cтратегий для three

class from4to7
  : public istrike
{
public:

  virtual ~from4to7()
  {
    delete _five;
    delete _six;
    delete _seven;
  }

  from4to7()
    : _five(new say_five)
    , _six(new say_six)
    , _seven(new say_seven)
  {}

  from4to7(const from4to7& jd)
    : _five(0)
    , _six(0)
    , _seven(0)
  {
    this->set_five( jd._five->clone() );
    this->set_six( jd._six->clone() );
    this->set_seven( jd._seven->clone() );
  }

  from4to7& operator = (const from4to7& jd)
  {
    this->set_five( jd._five->clone() );
    this->set_six( jd._six->clone() );
    this->set_seven( jd._seven->clone() );
    return *this;
  }

  istrike* clone()
  {
    return new from4to7(*this);
  }

  virtual void strike()
  {
    std::cout<<"four, ";
    this->say();
  }

  virtual void say()
  {
    _five->five();
    _six->six();
    _seven->seven();
  }

  void set_five(ifive* five)
  {
    delete _five;
    _five = five;
  }

  void set_six(isix* six)
  {
    delete _six;
    _six = six;
  }

  void set_seven(iseven* seven)
  {
    delete _seven;
    _seven = seven;
  }

private:
  ifive* _five;
  isix* _six;
  iseven* _seven;
};

int main()
{
  dredd d;
  std::cout << "Dredd: ";
  d.dredd_say();
  std::cout << std::endl;
  
  dredd j;
  j.set_one(new say_ONE);
  std::cout << "Jon: ";
  j.dredd_say();
  std::cout << std::endl;

  dredd b;
  b.set_strike(new from4to7);
  std::cout << "Bob: ";
  b.dredd_say();
  std::cout << std::endl;
  
  dredd s;
  s.set_one(new say_ONE);
  s.set_strike(new from4to7);
  std::cout << "Sam: ";
  s.dredd_say();
  std::cout << std::endl;

  return 0;
}
