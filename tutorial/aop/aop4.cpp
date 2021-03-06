#include <iostream>

struct say_one
{
  void operator()() const {  std::cout<<"one, "; }
};

struct say_two
{
  void operator()() const {  std::cout<<"two, "; }
};

struct say_three
{
  void operator()() const {  std::cout<<"three, "; }
};

struct say_strike
{
  void operator()() const {  std::cout<<"strike!"; }
};


template<
  typename One = say_one,
  typename Two = say_two,
  typename Three = say_three,
  typename Strike  = say_strike
>
class dredd
{
  // ...
public:
  void dredd_say() const
  {
    _one();
    _two();
    _three();
    _strike();
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
  void operator()() const {  std::cout<<"ONE, "; }
};

/// /////////////////////////////////////////////////

template<
  typename One = say_ONE,
  typename Two = say_two,
  typename Three = say_three,
  typename Strike  = say_strike
>
class jon
{
  // ...
public:
  void jon_say() const
  {
    _one();
    _two();
    _three();
    _strike();
  }

private:
  One    _one;
  Two    _two;
  Three  _three;
  Strike _strike;
};


/// /////////////////////////////////////////////////

struct say_four
{
  void operator()() const {  std::cout<<"four, "; }
};

struct say_five
{
  void operator()() const {  std::cout<<"five, "; }
};

struct say_six
{
  void operator()() const {  std::cout<<"six, "; }
};

struct say_seven
{
  void operator()() const {  std::cout<<"seven!"; }
};

template<
  typename One    = say_one,
  typename Two    = say_two,
  typename Three  = say_three,
  typename Four   = say_four,
  typename Five   = say_five,
  typename Six    = say_six,
  typename Seven  = say_seven
>
class bob
{
  // ...
public:
  void bob_say() const
  {
    _one();
    _two();
    _three();
    _four();
    _five();
    _six();
    _seven();
  }

private:
  One     _one;
  Two     _two;
  Three   _three;
  Four    _four;
  Five    _five;
  Six     _six;
  Seven   _seven;
};


template<
  typename One    = say_ONE,
  typename Two    = say_two,
  typename Three  = say_three,
  typename Four   = say_four,
  typename Five   = say_five,
  typename Six    = say_six,
  typename Seven  = say_seven
>
class sam
{
  // ...
public:
  void sam_say() const
  {
    _one();
    _two();
    _three();
    _four();
    _five();
    _six();
    _seven();
  }

private:
  One     _one;
  Two     _two;
  Three   _three;
  Four    _four;
  Five    _five;
  Six     _six;
  Seven   _seven;
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
