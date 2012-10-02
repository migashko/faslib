#include <iostream>

/// interfaces

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

/// concrete strategies

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

/// dredd

class dredd
{
  // ...
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
    : _one   ( jd._one    ? jd._one->clone()    : 0 )
    , _two   ( jd._two    ? jd._two->clone()    : 0 )
    , _three ( jd._three  ? jd._three->clone()  : 0 )
    , _strike( jd._strike ? jd._strike->clone() : 0 )
  {
  }

  dredd& operator = (const dredd& jd)
  {
    this->set_one(    jd._one    ? jd._one->clone()    : 0 );
    this->set_two(    jd._two    ? jd._two->clone()    : 0 );
    this->set_three(  jd._three  ? jd._three->clone()  : 0 );
    this->set_strike( jd._strike ? jd._strike->clone() : 0 );
    return *this;
  }

  void dredd_say()
  {
    if (_one)    _one->one();
    if (_two)    _two->two();
    if (_three)  _three->three();
    if (_strike) _strike->strike();
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

/// concrete strategies for jon

struct say_ONE: ione
{
  virtual ~say_ONE() {};
  virtual void one() {  std::cout<<"ONE, "; };
  virtual ione* clone() { return new say_ONE; };
};

/// strategies intefaces for from5to7

struct ifour
{
  virtual ~ifour() {};
  virtual void four() = 0;
  virtual ifour* clone() = 0;
};

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

/// strategies for say_4567

struct say_four: ifour
{
  virtual ~say_four() {};
  virtual void four() {  std::cout<<"four, "; }
  virtual ifour* clone() { return new say_four; };
};

struct say_five: ifive
{
  virtual ~say_five() {};
  virtual void five() {  std::cout<<"five, "; }
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
  virtual void seven() {  std::cout<<"seven!"; }
  virtual iseven* clone() { return new say_seven; };
};

/// Cтратегий для three

class say_4567
  : public istrike
{
public:

  virtual ~say_4567()
  {
    delete _four;
    delete _five;
    delete _six;
    delete _seven;
  }

  say_4567()
    : _four( new say_four)
    , _five( new say_five)
    , _six(  new say_six)
    , _seven(new say_seven)
  {}

  say_4567(const say_4567& jd)
    : istrike(jd)
    , _four ( jd._four  ? jd._four->clone()  : 0 )
    , _five ( jd._five  ? jd._five->clone()  : 0 )
    , _six  ( jd._six   ? jd._six->clone()   : 0 )
    , _seven( jd._seven ? jd._seven->clone() : 0 )
  {
  }

  say_4567& operator = (const say_4567& jd)
  {
    this->set_four ( jd._four  ? jd._four->clone()  : 0 );
    this->set_five ( jd._five  ? jd._five->clone()  : 0 );
    this->set_six  ( jd._six   ? jd._six->clone()   : 0 );
    this->set_seven( jd._seven ? jd._seven->clone() : 0 );
    return *this;
  }

  istrike* clone()
  {
    return new say_4567(*this);
  }

  virtual void strike()
  {
    this->say();
  }

  virtual void say()
  {
    if (_four) _four->four();
    if (_five) _five->five();
    if (_six)  _six->six();
    if (_seven)  _seven->seven();
  }

  void set_four(ifour* four)
  {
    delete _four;
    _four = four;
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
  ifour* _four;
  ifive* _five;
  isix* _six;
  iseven* _seven;
};

/// TODO:
///   class jon and jon::jon_say
///   class bob and bob::bob_say
///   class sam and sam::sam_say

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
  b.set_strike(new say_4567);
  std::cout << "Bob: ";
  b.dredd_say();
  std::cout << std::endl;

  dredd s;
  s.set_one(new say_ONE);
  s.set_strike(new say_4567);
  std::cout << "Sam: ";
  s.dredd_say();
  std::cout << std::endl;

  return 0;
}
