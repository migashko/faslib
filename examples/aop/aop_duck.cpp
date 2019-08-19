/*
 Source: http://r3dux.org/2011/07/an-example-implementation-of-the-strategy-design-pattern-in-c

 Pattern: Strategy
 Definition: The strategy pattern defines a family of algorithms (i.e. functions), encapsulates each one, and
 makes them interchangable. The Strategy pattern lets the algorithm vary independently from clients that use it.
 Example source: Head-First Design Patterns, pages 13-24 [ Converted from Java to C++ | 10/07/2011 | r3dux ]

 Aspect-oriented approach.
 See: tutorial/aop
*/

#include <iostream>
#include <fas/aop.hpp>

using namespace std;

struct _quack_;
struct _fly_;

// ----------------------- Quack interface -------------------------
class QuackBehaviour
{
  public:
    virtual void quack() = 0; // Abstract class because of this pure virtual function
};

class Quack : public QuackBehaviour
{
  public:
    void quack()
    {
      cout << "The duck says: Quack!" << endl;
    }
};

class MuteQuack : public QuackBehaviour
{
  public:
    void quack()
    {
      cout << "The duck says: <<< Silence >>>" << endl;
    }
};
// ----------------------- End of Quack interface -------------------------


// ----------------------- Fly interface -------------------------
class FlyBehaviour
{
  public:
    virtual void fly() = 0; // Abstract class because of this pure virtual function
};

class FlyWithWings : public FlyBehaviour
{
  public:
    void fly()
    {
      cout << "The duck flies into the friendly skies!" << endl;
    }
};

class FlyNoWay : public FlyBehaviour
{
  public:
    void fly()
    {
      cout << "I can't fly!" << endl;
    }
};

class FlyWithRocket : public FlyBehaviour
{
  public:
    void fly()
    {
      cout << "The duck flies through the air using a rocket!" << endl;
    }
};
// ----------------------- End of Fly interface -------------------------

// ----------------------- Duck class and subtypes -------------------------

class DuckInterface
{
public:
  virtual ~DuckInterface() {}
  virtual void performQuack() = 0;
  virtual void performFly() = 0;
  virtual void floatAround() = 0;
  virtual void display() = 0;
};

template<typename A>
class Duck
  : public DuckInterface
  , public fas::aspect_class<A>
{
  public:

    void performQuack()
    {
      //quackBehaviour->quack();
      this->get_aspect().template get<_quack_>().quack();
    }

    void performFly()
    {
      //flyBehaviour->fly();
      this->get_aspect().template get<_fly_>().fly();
    }

    void floatAround()
    {
      cout << "The duck bobs peacefully on the surface of the water." << endl;
    }

    virtual void display() = 0; // Make this an abstract class by having a pure virtual function
};

struct aspect_MallardDuck: fas::aspect< fas::type_list_n<
  fas::advice< _quack_, Quack>,
  fas::advice< _fly_, FlyWithWings>
>::type >{};

template<typename A = fas::aspect<> >
class MallardDuck
  : public Duck< typename fas::merge_aspect<A, aspect_MallardDuck>::type >
{
  public:
    MallardDuck()
    {
    }

    void display()
    {
      cout << "I'm a real mallard duck!" << endl;
    }

};

struct aspect_RubberDuck: fas::aspect< fas::type_list_n<
  fas::advice< _quack_, MuteQuack>,
  fas::advice< _fly_, FlyNoWay>
>::type >{};

template<typename A = fas::aspect<> >
class RubberDuck : public Duck< typename fas::merge_aspect<A, aspect_RubberDuck>::type >
{
  public:
    RubberDuck()
    {
    }

    void display()
    {
      cout << "I'm a rubber-ducky!" << endl;
    }
};

struct aspect_PaintedDuck: fas::aspect< fas::type_list_n<
  fas::advice< _quack_, MuteQuack>,
  fas::advice< _fly_, FlyNoWay>
>::type >{};

template<typename A = fas::aspect<> >
class PaintedDuck : public Duck< typename fas::merge_aspect<A, aspect_PaintedDuck>::type >
{
  public:
    PaintedDuck()
    {
    }

    void display()
    {
      cout << "I'm a painted wooden duck!" << endl;
    }
};
// ----------------------- End of Duck class and subtypes -------------------------

struct Rocket: fas::aspect< fas::advice<_fly_, FlyWithRocket> > {};

struct QuackRocket: fas::aspect< fas::type_list_n<
  fas::advice<_fly_, FlyWithRocket>,
  fas::advice<_quack_, Quack>
>::type > {};

// ----------------------- The main event -------------------------
int main()
{
  DuckInterface *mallard = new MallardDuck<>();
  mallard->display();
  mallard->floatAround();
  mallard->performFly();
  mallard->performQuack();
  delete mallard;
  cout << endl << endl;

  DuckInterface *rubber = new RubberDuck<>();
  rubber->display();
  rubber->floatAround();
  rubber->performFly();
  rubber->performQuack();
  delete rubber;
  cout << endl << endl;

  DuckInterface *painted = new PaintedDuck<>();
  painted->display();
  painted->floatAround();
  painted->performFly();
  delete painted;

  // cout << "Changing compile-time quack behaviour (generate new class)..." << endl;
  painted = new PaintedDuck<Rocket>();
  painted->display();
  painted->performFly();
  painted->performQuack();
  delete painted;
  cout << endl;

  //cout << "Changing compile-time quack behaviour (generate new class)..." << endl;
  painted = new PaintedDuck<QuackRocket>();
  painted->display();
  painted->performFly();
  painted->performQuack();
  delete painted;

  return 0;
}
