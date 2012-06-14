#include <iostream>

struct say_one
{
  template<typename T>
  void operator()(T&) {  std::cout<<"one, "; };
};

struct say_two
{
  template<typename T>
  void operator()(T&) {  std::cout<<"two, "; }
};

struct say_three
{
  template<typename T>
  void operator()(T&) {  std::cout<<"three, "; }
};

struct say_strike
{
  template<typename T>
  void operator()(T&) {  std::cout<<"strike!"; }
};

struct say_123s
{
  template<typename T>
  void operator()(T& t)
  {
    t._one(t);
    t._two(t);
    t._three(t);
    t._strike(t);
  }
};

template<
  typename One = say_one,
  typename Two = say_two,
  typename Three = say_three,
  typename Strike  = say_strike,
  typename Say  = say_123s
>
class dredd
{
public:
  void dredd_say()
  {
    _say(*this);
  }
  
  One _one;
  Two _two;
  Three _three;
  Strike _strike;
  Say _say;
};

/// /////////////////////////////////////////////////

struct say_ONE
{
  template<typename T>
  void operator()(T&) {  std::cout<<"ONE, "; };
};

/// /////////////////////////////////////////////////

template<
  typename One = say_ONE,
  typename Two = say_two,
  typename Three = say_three,
  typename Strike  = say_strike,
  typename Say  = say_123s
>
class jon
{
public:
  void jon_say()
  {
    _say(*this);
  }

  One    _one;
  Two    _two;
  Three  _three;
  Strike _strike;
  Say _say;
};


/// /////////////////////////////////////////////////

struct say_four
{
  template<typename T>
  void operator()(T&) {  std::cout<<"four, "; }
};

struct say_five
{
  template<typename T>
  void operator()(T&) {  std::cout<<"five, "; }
};

struct say_six
{
  template<typename T>
  void operator()(T&) {  std::cout<<"six, "; }
};

struct say_seven
{
  template<typename T>
  void operator()(T&) {  std::cout<<"seven!"; }
};

struct say_1234567
{
  template<typename T>
  void operator()(T& t)
  {
    t._one(t);
    t._two(t);
    t._three(t);
    t._four(t);
    t._five(t);
    t._six(t);
    t._seven(t);
  }
};

template<
  typename One    = say_one,
  typename Two    = say_two,
  typename Three  = say_three,
  typename Four   = say_four,
  typename Five   = say_five,
  typename Six    = say_six,
  typename Seven  = say_seven,
  typename Say    = say_1234567
>
class bob
{
public:
  void bob_say()
  {
    _say(*this);
  }

  One     _one;
  Two     _two;
  Three   _three;
  Four    _four;
  Five    _five;
  Six     _six;
  Seven   _seven;
  Say     _say;
};


template<
  typename One    = say_ONE,
  typename Two    = say_two,
  typename Three  = say_three,
  typename Four   = say_four,
  typename Five   = say_five,
  typename Six    = say_six,
  typename Seven  = say_seven,
  typename Say    = say_1234567
>
class sam
{
public:
  void sam_say()
  {
    _say(*this);
  }

  One     _one;
  Two     _two;
  Three   _three;
  Four    _four;
  Five    _five;
  Six     _six;
  Seven   _seven;
  Say     _say;
};


int main()
{
  dredd<> d;
  std::cout << "Dredd: ";
  d.dredd_say();
  std::cout << std::endl;

  jon<> j;
  std::cout << "Jon: ";
  j.jon_say();
  std::cout << std::endl;
  
  bob<> b;
  std::cout << "Bob: ";
  b.bob_say();
  std::cout << std::endl;

  sam<> s;
  std::cout << "Sam: ";
  s.sam_say();
  std::cout << std::endl;

  return 0;
}
