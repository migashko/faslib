/*
 Source: http://r3dux.org/2011/07/an-example-implementation-of-the-strategy-design-pattern-in-c
*/

/*
Pattern: Strategy
Definition: The strategy pattern defines a family of algorithms (i.e. functions), encapsulates each one, and
makes them interchangable. The Strategy pattern lets the algorithm vary independently from clients that use it.
Example source: Head-First Design Patterns, pages 13-24 [ Converted from Java to C++ | 10/07/2011 | r3dux ]
*/

#include <iostream>

using namespace std;

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
class Duck
{
  public:
    QuackBehaviour *quackBehaviour;
    FlyBehaviour   *flyBehaviour;

    void performQuack()
    {
      quackBehaviour->quack();
    }

    void setQuackBehaviour(QuackBehaviour *qb)
    {
      cout << "Changing quack behaviour..." << endl;
      quackBehaviour = qb;
    }

    void performFly()
    {
      flyBehaviour->fly();
    }

    void setFlyBehaviour(FlyBehaviour *fb)
    {
      cout << "Changing fly behaviour..." << endl;
      flyBehaviour = fb;
    }

    void floatAround()
    {
      cout << "The duck bobs peacefully on the surface of the water." << endl;
    }

    virtual void display() = 0; // Make this an abstract class by having a pure virtual function


};

class MallardDuck : public Duck
{
  public:
    MallardDuck()
    {
      quackBehaviour = new Quack();
      flyBehaviour   = new FlyWithWings();
    }

    void display()
    {
      cout << "I'm a real mallard duck!" << endl;
    }

};

class RubberDuck : public Duck
{
  public:
    RubberDuck()
    {
      quackBehaviour = new MuteQuack();
      flyBehaviour   = new FlyNoWay();
    }

    void display()
    {
      cout << "I'm a rubber-ducky!" << endl;
    }
};

class PaintedDuck : public Duck
{
  public:
    PaintedDuck()
    {
      quackBehaviour = new MuteQuack();
      flyBehaviour   = new FlyNoWay();
    }

    void display()
    {
      cout << "I'm a painted wooden duck!" << endl;
    }
};
// ----------------------- End of Duck class and subtypes -------------------------

// ----------------------- The main event -------------------------
int main()
{
  Duck *mallard = new MallardDuck();
  mallard->display();
  mallard->floatAround();
  mallard->performFly();
  mallard->performQuack();

  cout << endl << endl;

  Duck *rubber = new RubberDuck();
  rubber->display();
  rubber->floatAround();
  rubber->performFly();
  rubber->performQuack();

  cout << endl << endl;

  Duck *painted = new PaintedDuck();
  painted->display();
  painted->floatAround();
  painted->performFly();
  painted->setFlyBehaviour(new FlyWithRocket);
  painted->performFly();
  painted->performQuack();
  painted->setQuackBehaviour(new Quack);
  painted->performQuack();

  return 0;
}
