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

struct _quack_;
struct _fly_;
struct _float_;
struct _display_;

// ----------------------- Quack interface -------------------------

struct ad_quack 
{
  template<typename T>
  void operator()(T&)
  {
    std::cout << "The duck says: Quack!" << std::endl;
  }
};

struct ad_mute_quack
{
  template<typename T>
  void operator()(T&)
  {
    std::cout << "The duck says: <<< Silence >>>" << std::endl;
  }
};

// ----------------------- End of Quack interface -------------------------


// ----------------------- Fly interface -------------------------
struct ad_fly_with_wings
{
  template<typename T>
  void operator()(T&)
  {
    std::cout << "The duck flies into the friendly skies!" << std::endl;
  }
};

struct ad_fly_no_way
{
  template<typename T>
  void operator()(T&)
  {
    std::cout << "I can't fly!" << std::endl;
  }
};

struct ad_fly_with_rocket
{
  template<typename T>
  void operator()(T&)
  {
    std::cout << "The duck flies through the air using a rocket!" << std::endl;
  }
};
// ----------------------- End of Fly interface -------------------------

// ----------------------- Float interface -------------------------
struct ad_float_around
{
  template<typename T>
  void operator()(T&)
  {
    std::cout << "The duck bobs peacefully on the surface of the water." << std::endl;
  }
};

// ----------------------- End of Float interface -------------------------

// ----------------------- Display interface -------------------------

// ----------------------- End of Display interface -------------------------

struct ad_display_mallard
{
  template<typename T>
  void operator()(T&)
  {
    std::cout << "I'm a real mallard duck!" << std::endl;
  }
};

struct ad_display_rubber
{
  template<typename T>
  void operator()(T&)
  {
    std::cout << "I'm a rubber-ducky!" << std::endl;
  }
};

struct ad_display_painted
{
  template<typename T>
  void operator()(T&)
  {
    std::cout << "I'm a painted wooden duck!" << std::endl;
  }
};


typedef fas::aspect< fas::type_list_n<
  fas::advice< _float_, ad_float_around>,
  fas::advice< _quack_, ad_quack>,
  fas::advice< _fly_,   ad_fly_with_wings>,
  fas::advice< _display_,   ad_display_mallard>
>::type > aspect_mallard;

typedef fas::aspect< fas::type_list_n<
  fas::advice< _quack_, ad_mute_quack>,
  fas::advice< _fly_, ad_fly_no_way>,
  fas::advice< _display_,   ad_display_rubber>,
  aspect_mallard
>::type > aspect_rubber;

typedef fas::aspect< fas::type_list_n<
  fas::advice< _display_,   ad_display_painted>,
  aspect_rubber
>::type > aspect_painted;

typedef fas::aspect< fas::type_list_n<
  fas::advice<_fly_, ad_fly_with_rocket>,
  aspect_mallard
>::type > aspect_mallard_rocket;

typedef fas::aspect< fas::type_list_n<
  fas::advice<_fly_, ad_fly_with_rocket>,
  aspect_painted
>::type > aspect_painted_rocket;

// ----------------------- Duck class and subtypes -------------------------

template<typename A>
class duck
  : public fas::aspect_class<A>
{
public:
  void quack()
  {
    this->get_aspect().template get<_quack_>()(*this);
  }

  void fly()
  {
    this->get_aspect().template get<_fly_>()(*this);
  }

  void float_around()
  {
    this->get_aspect().template get<_float_>()(*this);
  }

  void display()
  {
    this->get_aspect().template get<_display_>()(*this);
  }
};

// ----------------------- The main event -------------------------
int main()
{
  duck<aspect_mallard> mallard;
  mallard.display();
  mallard.float_around();
  mallard.fly();
  mallard.quack();
  std::cout << std::endl;

  duck<aspect_rubber> rubber;
  rubber.display();
  rubber.float_around();
  rubber.fly();
  rubber.quack();
  std::cout << std::endl;

  duck<aspect_painted> painted;
  painted.display();
  painted.float_around();
  painted.fly();
  std::cout << std::endl;

  duck<aspect_mallard_rocket> mallard_rocket;
  mallard_rocket.display();
  mallard_rocket.fly();
  mallard_rocket.quack();
  std::cout << std::endl;

  duck<aspect_painted_rocket> painted_rocket;
  painted_rocket.display();
  painted_rocket.fly();
  painted_rocket.quack();
  std::cout << std::endl;
  return 0;
}
